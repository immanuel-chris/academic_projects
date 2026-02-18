#include "Adafruit_TCS34725.h"
#include "Arduino_FreeRTOS.h"
#include "Servo.h"
#include "semphr.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
Servo pathServo;
Servo doorServo;

volatile int pathServoAngle = 90;

SemaphoreHandle_t xColorReadMutex;

void readColor(void *pvParameters);
void movePathServo(void *pvParameters);
void moveDoorServo(void *pvParameters);

void setup() {
  Serial.begin(9600);

  if (!tcs.begin()) {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  Serial.println("TCS34725 Found");

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pathServo.attach(9);
  doorServo.attach(10);

  xColorReadMutex = xSemaphoreCreateMutex();

  xTaskCreate(readColor, "Read Color", 100, NULL, 2, NULL);
  xTaskCreate(movePathServo, "Move Path Servo", 100, NULL, 1, NULL);
  xTaskCreate(moveDoorServo, "Move Door Servo", 100, NULL, 1, NULL);
}

void loop() {
}

void readColor(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(xColorReadMutex, portMAX_DELAY) == pdTRUE) {
      float red, green, blue;

      tcs.setInterrupt(false);
      delay(1);
      tcs.getRGB(&red, &green, &blue);
      tcs.setInterrupt(true);

      Serial.print("R: "); Serial.print(red);
      Serial.print(" G: "); Serial.print(green);
      Serial.print(" B: "); Serial.println(blue);

      if (red > green && red > blue && red > 100) {
        pathServoAngle = 40;
        xSemaphoreGive(xColorReadMutex);
      } else if (green > red && green > blue && green > 100) {
        pathServoAngle = 90;
        xSemaphoreGive(xColorReadMutex);
      } else if (blue > red && blue > green && blue > 100) {
        pathServoAngle = 140;
        xSemaphoreGive(xColorReadMutex);
      }
    }

    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void movePathServo(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(xColorReadMutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("path");
      pathServo.write(pathServoAngle);
      xSemaphoreGive(xColorReadMutex);
      vTaskDelay(1 / portTICK_PERIOD_MS);
    }
  }
}

void moveDoorServo(void *pvParameters) {
  while (1) {
    if (xSemaphoreTake(xColorReadMutex, portMAX_DELAY) == pdTRUE) {
      Serial.println("door");
      doorServo.write(0);
      vTaskDelay(300 / portTICK_PERIOD_MS);
      doorServo.write(90);
      vTaskDelay(300 / portTICK_PERIOD_MS);
      xSemaphoreGive(xColorReadMutex);
      vTaskDelay(1 / portTICK_PERIOD_MS);
    }
  }
}

//Arduino Implementation

// #include <Arduino.h>
// #include "Adafruit_TCS34725.h"
// #include "Servo.h"

// // Sensors and Servos
// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
// Servo pathServo;
// Servo doorServo;

// // Shared angles
// int pathServoAngle = 90;

// void setup() {
//   Serial.begin(9600);

//   if (!tcs.begin()) {
//     Serial.println("No TCS34725 found ... check your connections");
//     while (1);
//   }

//   Serial.println("TCS34725 Found");

//   pinMode(9, OUTPUT);
//   pinMode(10, OUTPUT);
//   pathServo.attach(9);
//   doorServo.attach(10);

//   pathServo.write(90); // default position
//   doorServo.write(90); // default closed position
// }

// void loop() {
//   float red, green, blue;

//   tcs.setInterrupt(false);
//   delay(1); // brief pause for reading
//   tcs.getRGB(&red, &green, &blue);
//   tcs.setInterrupt(true);

//   Serial.print("R:\t"); Serial.print(int(red));
//   Serial.print("\tG:\t"); Serial.print(int(green));
//   Serial.print("\tB:\t"); Serial.println(int(blue));

//   // Detect dominant color and set angle
//   if (red > green && red > blue && red > 100) {
//     pathServoAngle = 40;
//   } else if (green > red && green > blue && green > 100) {
//     pathServoAngle = 90;
//   } else if (blue > red && blue > green && blue > 100) {
//     pathServoAngle = 140;
//   } 
//     // Move path servo
//     pathServo.write(pathServoAngle);
//     delay(100); // wait for movement

//     // Open and close door servo
//     doorServo.write(0);
//     delay(300);
//     doorServo.write(90);
//     delay(1000);
 
// }


