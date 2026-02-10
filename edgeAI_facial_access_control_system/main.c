/******************************************************************************
 * MAX78000 Feather Facial Recognition Demo - BARE METAL EDITION
 ******************************************************************************/

#define S_MODULE_NAME "main"

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "mxc.h"
#include "mxc_device.h"
#include "mxc_delay.h"
#include "camera.h"
#include "icc.h"
#include "rtc.h"
#include "cnn_1.h"
#ifdef BOARD_FTHR_REVA
#include "tft_ili9341.h"
#endif
#include "MAXCAM_Debug.h"
#include "facedetection.h"
#include "post_process.h"
#include "embeddings.h"
#include "faceID.h"
#include "utils.h"

#define CONSOLE_BAUD 115200

// ============================================================================
// BARE METAL GLOBALS AND DEFINITIONS
// ============================================================================

// MOVED TO PORT 1.6 (Header J8, Pin 5) to ensure 3.3V Logic
#define PIN_SERVO   (1 << 6)   // P1.6
#define PIN_BUTTON  (1 << 19)  // P0.19 (Stays same)

// Volatile flag for Interrupt Service Routine (ISR)
volatile uint8_t start_face_scan = 0;

// Forward Declaration
void GPIO0_IRQHandler(void);

// ============================================================================
// EXTERNAL DECLARATIONS
// ============================================================================

extern void SD_Init(void);
extern volatile uint8_t face_detected;
volatile char names[1024][7];
mxc_uart_regs_t *CommUart;

// ============================================================================
// INITIALIZATION FUNCTIONS
// ============================================================================

void init_names(void)
{
    char default_names[DEFAULT_EMBS_NUM][7] = DEFAULT_NAMES;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
    for (int i = 0; i < DEFAULT_EMBS_NUM; i++) {
        strncpy((char *)names[i], default_names[i], 7);
    }
#pragma GCC diagnostic pop
}

#ifdef TFT_ENABLE
area_t area = { 50, 290, 180, 30 };
#endif

// ============================================================================
// BARE METAL GPIO AND SERVO CONTROL
// ============================================================================

void Setup_BareMetal_IO(void)
{
    // 1. Enable Clocks for Port 0 (Button) and Port 1/2 (Servo)
    MXC_GCR->pclkdis0 &= ~(1 << 0);		 // Enable Port 0 Clock
    MXC_GCR->pclkdis0 &= ~((1 << 1) | (1 << 2)); // Enable Port 1/2 Clock

    // --- Button Setup (P0.19) ---
    MXC_GPIO0->en0_set = PIN_BUTTON;		// enable P0.19
    MXC_GPIO0->outen_clr = PIN_BUTTON;		// set as input
    MXC_GPIO0->inten_clr = PIN_BUTTON;		// clear any pending interrupts
    MXC_GPIO0->intfl_clr = PIN_BUTTON;		// clear any interrupt flag
    MXC_GPIO0->intmode |= PIN_BUTTON;		// sets edge-triggered interrupt
    MXC_GPIO0->intpol |= PIN_BUTTON;        	// setting bit 19 t0 1; interrupt triggers on rising edge
    MXC_GPIO0->padctrl0 |= PIN_BUTTON;      	// enable internal pull resistor
    MXC_GPIO0->ps &= ~PIN_BUTTON;           	// ps = 0 = pull-down; ensure no pull-up resistor
    MXC_GPIO0->padctrl1 |= PIN_BUTTON;      	// sets drive strength (for the pull circuit to engage properly)
    MXC_GPIO0->inten_set = PIN_BUTTON;		// enable interrupt for this pin; "when P0.19 has a rising edge, fire an interrupt"

    // --- Servo Setup (P1.6) --- 
    MXC_GPIO1->en0_set = PIN_SERVO;
    MXC_GPIO1->outen_set = PIN_SERVO;

    // CRITICAL: Force VDDIOH (3.3V) operation
    MXC_GPIO1->vssel |= PIN_SERVO;  		// bit 6 = 1: use VDDIOH (3.3V logic), servo need 3.3-5V to reliably detect the signal

    // Set maximum drive strength for clean PWM signal
    MXC_GPIO1->ds0 |= PIN_SERVO;	
    MXC_GPIO1->ds1 |= PIN_SERVO;  		// ds0 = 1, ds1 = 1: set both bits for maximum drive

    // Disable pull-up/pull-down
    MXC_GPIO1->ps &= ~PIN_SERVO;		// clear pull select
    MXC_GPIO1->padctrl0 &= ~PIN_SERVO;		// disable resistor
    MXC_GPIO1->padctrl1 &= ~PIN_SERVO;		// clear config

    MXC_GPIO1->out_clr = PIN_SERVO;
}

// ============================================================================
// INTERRUPT SERVICE ROUTINES
// ============================================================================

void GPIO0_IRQHandler(void)
{
    // Check if P0.19 caused the interrupt
    if (MXC_GPIO0->intfl & PIN_BUTTON) {
        MXC_GPIO0->intfl_clr = PIN_BUTTON; 	// Clear flag
        start_face_scan = 1;               	// Set logic flag
    }
}

// ============================================================================
// SERVO CONTROL FUNCTION
// ============================================================================

void Servo_Move(int open)
{
    int high_time_us;

    if (open) {
        high_time_us = 2000;
    } else {
        high_time_us = 1000;
    }

    PR_INFO("Moving servo to %s position...\n", open ? "OPEN" : "CLOSED");

    // Send 150 pulses (~7 seconds) for reliable movement
    for(int i = 0; i < 150; i++) {
        MXC_GPIO1->out_set = PIN_SERVO;		// high
        MXC_Delay(high_time_us);		// hold high
        MXC_GPIO1->out_clr = PIN_SERVO;		// low
        MXC_Delay(20000 - high_time_us);
    }

    PR_INFO("Servo movement complete.\n");
}

void Servo_GPIO_Test(void)
{
    PR_INFO("\n=== GPIO DIAGNOSTIC TEST ===\n");

    // Test 1: Rapid toggling (should be visible with LED/oscilloscope)
    PR_INFO("Test 1: Rapid toggle (10Hz for 2 seconds)...\n");
    for(int i = 0; i < 20; i++) {
        MXC_GPIO1->out_set = PIN_SERVO;
        MXC_Delay(50000);
        MXC_GPIO1->out_clr = PIN_SERVO;
        MXC_Delay(50000);
    }

    // Test 2: Hold high
    PR_INFO("Test 2: Hold HIGH for 2 seconds...\n");
    MXC_GPIO1->out_set = PIN_SERVO;
    MXC_Delay(MXC_DELAY_SEC(2));

    // Test 3: Hold low
    PR_INFO("Test 3: Hold LOW for 2 seconds...\n");
    MXC_GPIO1->out_clr = PIN_SERVO;
    MXC_Delay(MXC_DELAY_SEC(2));

    PR_INFO("=== GPIO TEST COMPLETE ===\n");
    PR_INFO("If you saw voltage changes on P1.6, GPIO is working.\n");
    PR_INFO("If not, check VDDIOH power supply or pin configuration.\n\n");
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main(void)
{
    int error = 0;
    int id;
    int dma_channel;
    mxc_uart_regs_t *ConsoleUart;

    MXC_Delay(MXC_DELAY_SEC(2)); 		// Allow debugger/power to settle

#ifdef BOARD_FTHR_REVA
    MXC_Delay(200000);
    Camera_Power(POWER_ON);
#endif

    MXC_ICC_Enable(MXC_ICC0);			// instruction cache controller; cache copies frequently used instructions into fast RAM
    MXC_SYS_Clock_Select(MXC_SYS_CLOCK_IPO);	// internal precision controller; the system's heartbeat required to run the CNN acceleratpr
    SystemCoreClockUpdate();

    ConsoleUart = MXC_UART_GET_UART(CONSOLE_UART);
    if ((error = MXC_UART_Init(ConsoleUart, CONSOLE_BAUD, MXC_UART_IBRO_CLK)) != E_NO_ERROR) {
        return error;
    }

    PR_INFO("\n\nMAX78000 Bare Metal Access Control (Servo on P1.6)\n");

    // ========================================================================
    // SYSTEM INITIALIZATION
    // ========================================================================

    // 1. Setup Bare Metal IO
    Setup_BareMetal_IO();

    // 2. Diagnostic Block
    PR_INFO("\n=== Running GPIO Diagnostic ===\n");
    Servo_GPIO_Test();

    PR_INFO("=== Running Servo Test Sequence ===\n");
    PR_INFO("Test 1: Moving to OPEN (should move to ~90 deg)...\n");
    Servo_Move(1);
    MXC_Delay(MXC_DELAY_SEC(2));

    PR_INFO("Test 2: Moving to CLOSED (should move to 0 deg)...\n");
    Servo_Move(0);
    MXC_Delay(MXC_DELAY_SEC(2));
    PR_INFO("=== Servo Test Complete ===\n\n");

    // 3. Initialize remaining systems
    init_names();
    MXC_RTC_Init(0, 0);
    MXC_RTC_Start();
    MXC_DMA_Init();
    dma_channel = MXC_DMA_AcquireChannel();

    PR_INFO("[DEBUG] Initializing Camera...\n");
    error = camera_init(CAMERA_FREQ);
    if (error) { PR_ERR("Camera init error"); return error; }

    camera_get_product_id(&id);
    camera_setup(IMAGE_XRES, IMAGE_YRES, PIXFORMAT_RGB565, FIFO_FOUR_BYTE, USE_DMA, dma_channel);
    camera_write_reg(0x11, 0x80);

#ifdef TFT_ENABLE
#ifdef BOARD_FTHR_REVA
    MXC_TFT_Init(MXC_SPI0, 1, NULL, NULL);
#ifdef ROTATE_FEATHER_BOARD
    MXC_TFT_SetRotation(ROTATE_270);
#else
    MXC_TFT_SetRotation(ROTATE_180);
#endif
    MXC_TFT_SetBackGroundColor(4);
    MXC_TFT_SetForeGroundColor(WHITE);
#endif
#endif

    // ========================================================================
    // MAIN LOOP - SLEEP/WAKE CYCLE
    // ========================================================================

    PR_INFO("System Ready. Entering Sleep Mode (WFI).\n");
    PR_INFO("Press Button (Connect 3V3) to Wake and Scan.\n");

    // 4. Enable Interrupts
    MXC_GPIO0->intfl_clr = PIN_BUTTON;
    NVIC_EnableIRQ(GPIO0_IRQn);
    __enable_irq();

    while (1) {
        // POWER SAVING STEP: Wait for interrupt
        while (start_face_scan == 0) {
            __WFI();
        }

        // ====================================================================
        // WAKE UP AND SCAN SEQUENCE
        // ====================================================================

        PR_INFO("Wake Up Triggered! Starting 5-Second Scan Window...\n");
        LED_On(0); // Red LED ON indicates "Scanning Active"

        // Face detection attempts loop
        int attempts = 0;
        while (attempts < 50) {
            face_detection();

            if (face_detected) {
                PR_INFO("Face Found on Attempt %d!\n", attempts + 1);
                break;
            }
            attempts++;
            MXC_Delay(10000);
        }

        LED_Off(0); // Scan Complete

        // ====================================================================
        // ACCESS CONTROL DECISION
        // ====================================================================

        if (face_detected) {
            PR_INFO("Access Granted. Opening Door...\n");
            LED_On(1); 				// Green LED
            Servo_Move(1); 			// Open
            MXC_Delay(MXC_DELAY_SEC(3));
            PR_INFO("Closing Door...\n");
            Servo_Move(0); 			// Close
            LED_Off(1);
            face_detected = 0;
        } else {
            PR_INFO("Access Denied (Timed Out).\n");
            for(int i=0; i<3; i++) {
                LED_On(0); MXC_Delay(50000); LED_Off(0); MXC_Delay(50000);
            }
        }

        // ====================================================================
        // RESET AND RETURN TO SLEEP
        // ====================================================================

        PR_INFO("Release Button to Reset System to Sleep...\n");

        // Wait for button release to prevent immediate re-trigger
        while((MXC_GPIO0->in & PIN_BUTTON)) {
            MXC_Delay(10000);
        }

        // Clear flags
        start_face_scan = 0;
        MXC_GPIO0->intfl_clr = PIN_BUTTON;

        PR_INFO("Returning to Low Power Sleep Mode...\n");
    }

    return 0;
}
