#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	
    // ----------- Set columns (D2–D10) as OUTPUT
    DDRD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
    DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
    
    // ----------- Set layers (D11–D13) as OUTPUT
    DDRB |= (1 << PB3) | (1 << PB4) | (1 << PB5);




    while (1) {

///////////////////////////////////// P A T T E R N   1 ///////////////////////////////////////////////////////////
	uint8_t k;
	for(k = 0; k < 1; k++) {
////// LAYER ONE -----------------------------------
	PORTB &= ~((1 << PB4) | (1 << PB5));
	PORTB |= (1 << PB3);			// enable layer 1

	PORTD |= (1 << PD2);									//// turn on column 1
	_delay_ms(250);
	PORTD &= ~(1 << PD2);									//// turn off column 1


	PORTD |= (1 << PD3);									//// turn on column 2
	_delay_ms(250);
	PORTD &= ~(1 << PD3);									//// turn off column 2


	PORTD |= (1 << PD4);									//// turn on column 3
	_delay_ms(250);
	PORTD &= ~(1 << PD4);									//// turn off column 3


	PORTD |= (1 << PD7);									//// turn on column 6
	_delay_ms(250);
	PORTD &= ~(1 << PD7);									//// turn off column 6


	PORTD |= (1 << PD6);									//// turn on column 5
	_delay_ms(250);
	PORTD &= ~(1 << PD6);									//// turn off column 5


	PORTD |= (1 << PD5);									//// turn on column 4
	_delay_ms(250);
	PORTD &= ~(1 << PD5);									//// turn off column 4


	PORTB |= (1 << PB0);									//// turn on column 7
	_delay_ms(250);
	PORTB &= ~(1 << PB0);									//// turn off column 7


	PORTB |= (1 << PB1);									//// turn on column 8
	_delay_ms(250);
	PORTB &= ~(1 << PB1);									//// turn off column 8


	PORTB |= (1 << PB2);									//// turn on column 9
	_delay_ms(250);
	PORTB &= ~(1 << PB2);									//// turn off column 9




	////// LAYER TWO -----------------------------------
	PORTB &= ~(1 << PB3);			// disable layer 1
	PORTB |= (1 << PB4);			// enable layer 2

	PORTB |= (1 << PB2);									//// turn on column 9
	_delay_ms(250);
	PORTB &= ~(1 << PB2);									//// turn off column 9


	PORTD |= (1 << PD7);									//// turn on column 6
	_delay_ms(250);
	PORTD &= ~(1 << PD7);									//// turn off column 6


	PORTD |= (1 << PD4);									//// turn on column 3
	_delay_ms(250);
	PORTD &= ~(1 << PD4);									//// turn off column 3


	PORTD |= (1 << PD3);									//// turn on column 2
	_delay_ms(250);
	PORTD &= ~(1 << PD3);									//// turn off column 2


	PORTD |= (1 << PD6);									//// turn on column 5
	_delay_ms(250);
	PORTD &= ~(1 << PD6);									//// turn off column 5


	PORTB |= (1 << PB1);									//// turn on column 8
	_delay_ms(250);
	PORTB &= ~(1 << PB1);									//// turn off column 8


	PORTB |= (1 << PB0);									//// turn on column 7
	_delay_ms(250);
	PORTB &= ~(1 << PB0);									//// turn off column 7


	PORTD |= (1 << PD5);									//// turn on column 4
	_delay_ms(250);
	PORTD &= ~(1 << PD5);									//// turn off column 4


	PORTD |= (1 << PD2);									//// turn on column 1
	_delay_ms(250);
	PORTD &= ~(1 << PD2);									//// turn off column 1

	


	////// LAYER THREE -----------------------------------
	PORTB &= ~(1 << PB4);			// disable layer 1
	PORTB |= (1 << PB5);			// enable layer 1

	PORTD |= (1 << PD2);									//// turn on column 1
	_delay_ms(250);
	PORTD &= ~(1 << PD2);									//// turn off column 1


	PORTD |= (1 << PD3);									//// turn on column 2
	_delay_ms(250);
	PORTD &= ~(1 << PD3);									//// turn off column 2


	PORTD |= (1 << PD4);									//// turn on column 3
	_delay_ms(250);
	PORTD &= ~(1 << PD4);									//// turn off column 3


	PORTD |= (1 << PD7);									//// turn on column 6
	_delay_ms(250);
	PORTD &= ~(1 << PD7);									//// turn off column 6


	PORTD |= (1 << PD6);									//// turn on column 5
	_delay_ms(250);
	PORTD &= ~(1 << PD6);									//// turn off column 5


	PORTD |= (1 << PD5);									//// turn on column 4
	_delay_ms(250);
	PORTD &= ~(1 << PD5);									//// turn off column 4


	PORTB |= (1 << PB0);									//// turn on column 7
	_delay_ms(250);
	PORTB &= ~(1 << PB0);									//// turn off column 7


	PORTB |= (1 << PB1);									//// turn on column 8
	_delay_ms(250);
	PORTB &= ~(1 << PB1);									//// turn off column 8


	PORTB |= (1 << PB2);									//// turn on column 9
	_delay_ms(250);
	PORTB &= ~(1 << PB2);									//// turn off column 9



///////////////////////////////////// P A T T E R N   1.1 /////////////////////////////////////////////////////////
	////// ANOTHER PATTERN  -----------------------------------
	uint8_t i = 0;
	while (i < 1) {



		PORTB |= (1 << PB3) | (1 << PB4);			// enable layer 1 and 2
	
		PORTD |= (1 << PD4) | (1 << PD7);
		PORTB |= (1 << PB2);
		_delay_ms(500);
		PORTD &= ~((1 << PD4) | (1 << PD7));
		PORTB &= ~(1 << PB2);

	
		PORTD |= ((1 << PD2) | (1 << PD6));
		PORTB |= ((1 << PB2));
		_delay_ms(500);
		PORTD &= ~((1 << PD2) | (1 << PD6));
		PORTB &= ~((1 << PB2));


		PORTB |= ((1 << PB0) | (1 << PB1) | (1 << PB2));
		_delay_ms(500);
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));




		PORTD |= ((1 << PD4) | (1 << PD6));
		PORTB |= ((1 << PB0));
		_delay_ms(500);
		PORTD &= ~((1 << PD4) | (1 << PD6));
		PORTB &= ~((1 << PB0));


		PORTD |= ((1 << PD2) | (1 << PD5));
		PORTB |= ((1 << PB0));
		_delay_ms(500);
		PORTD &= ~((1 << PD2) | (1 << PD5));
		PORTB &= ~((1 << PB0));




		PORTD |= ((1 << PD2) | (1 << PD6));
		PORTB |= (1 << PB2);
		_delay_ms(500);
		PORTD &= ~((1 << PD2) | (1 << PD6));
		PORTB &= ~(1 << PB2);


		PORTD |= ((1 << PD2) | (1 << PD3) | (1 << PD4));
		_delay_ms(500);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4));


		PORTD |= ((1 << PD4) | (1 << PD6));
		PORTB |= (1 << PB0);
		_delay_ms(500);
		PORTD &= ~((1 << PD4) | (1 << PD6));
		PORTB &= ~(1 << PB0);

		i++;
	}
	
	PORTD |= (1 << PD4) | (1 << PD7);
	PORTB |= (1 << PB2);
	_delay_ms(500);
	PORTD &= ~((1 << PD4) | (1 << PD7));
	PORTB &= ~(1 << PB2);

	
	PORTD |= ((1 << PD2) | (1 << PD6));
	PORTB |= ((1 << PB2));
	_delay_ms(500);
	PORTD &= ~((1 << PD2) | (1 << PD6));
	PORTB &= ~((1 << PB2));


	PORTB |= ((1 << PB0) | (1 << PB1) | (1 << PB2));
	_delay_ms(500);
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));



	PORTD |= ((1 << PD4) | (1 << PD6));
	PORTB |= ((1 << PB0));
	_delay_ms(500);
	PORTD &= ~((1 << PD4) | (1 << PD6));
	PORTB &= ~((1 << PB0));


	PORTD |= ((1 << PD2) | (1 << PD5));
	PORTB |= ((1 << PB0));
	_delay_ms(500);
	PORTD &= ~((1 << PD2) | (1 << PD5));
	PORTB &= ~((1 << PB0));




	PORTD |= ((1 << PD2) | (1 << PD6));
	PORTB |= (1 << PB2);
	_delay_ms(500);
	PORTD &= ~((1 << PD2) | (1 << PD6));
	PORTB &= ~(1 << PB2);


	PORTD |= ((1 << PD2) | (1 << PD3) | (1 << PD4));
	_delay_ms(500);
	PORTD &= ~(1 << PD4);
	_delay_ms(500);
	PORTD &= ~(1 << PD3);
	_delay_ms(500);
	PORTB &= ~((1 << PB5));
	_delay_ms(500);
	PORTB &= ~(1 << PB4);
	
	k++;
	_delay_ms(250);
    }




///////////////////////////////////// P A T T E R N   2 ///////////////////////////////////////////////////////////


	uint8_t j;
	for(j = 0; j < 1; j++) {

	uint8_t i;
////////////////////////// layer 3 ON ///////////////////////////
	for (i = 0; i < 2; i++) { 
	PORTB |= (1 << PB5);	// set layer 3 to "1"
	PORTB &= ~((1 << PB3));
	PORTB &= ~((1 << PB4));

    
	PORTD |= (1 << PD6);	// set column 1 to "1"

	PORTD |= (1 << PD5) | (1 << PD7);
	PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB1) | (1 << PB2));
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	PORTD &= ~((1 << PD2) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB2));
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	PORTD &= ~((1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1));
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}


////////////////////////// layer 3 & 2 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB |= (1 << PB4);	// set layer 2 to "1"
    
	PORTD |= (1 << PD6);	// set column 1 to "1"

	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}


////////////////////////// layer 3, 2, & 1 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB |= (1 << PB3);	// set layer 1 to "1"
    
	PORTD |= (1 << PD6);	// set column 1 to "1"

	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}



////////////////////////// layer 2 & 1 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB |= (1 << PB3);	// set layer 1 to "1"
	PORTB &= ~(1 << PB5);	// turn off layer 3, set to "0"

    
	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}	



////////////////////////// layer 1 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB |= (1 << PB3);	// set layer 1 to "1"
	PORTB &= ~(1 << PB4);	// turn off layer 2, set to "0"
	PORTB &= ~(1 << PB5);	// turn off layer 3, set to "0"

    
	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}	


////////////////////////// layer 1 & 2 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB |= (1 << PB3);	// set layer 1 to "1"
	PORTB |= (1 << PB4);	// turn on layer 2, set to "1"
	PORTB &= ~(1 << PB5);	// turn off layer 3, set to "0"

    
	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}


////////////////////////// layer 1, 2, & 3 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB |= (1 << PB3);	// set layer 1 to "1"
	PORTB |= (1 << PB4);	// turn on layer 2, set to "1"
	PORTB |= (1 << PB5);	// turn on layer 3, set to "1"

    
	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	}



////////////////////////// layer 2, & 3 ON ///////////////////////////
	for (i = 0; i < 2; i++) {
	PORTB &= ~(1 << PB3);	// turn off later 1, set to "0"
	PORTB |= (1 << PB4);	// turn on layer 2, set to "1"
	PORTB |= (1 << PB5);	// turn on layer 3, set to "1"

    
	PORTD |= (1 << PD5) | (1 << PD7);
	_delay_ms(150);
	PORTD &= ~((1 << PD5) | (1 << PD7));
	//_delay_ms(50);

	PORTD |= (1 << PD4); PORTB |= (1 << PB0);
	_delay_ms(150);
	PORTD &= ~((1 << PD4)); PORTB &= ~((1 << PB0));
	//_delay_ms(50);

	PORTD |= (1 << PD3); PORTB |= (1 << PB1);
	_delay_ms(150);
	PORTD &= ~((1 << PD3)); PORTB &= ~((1 << PB1));
	//_delay_ms(50);

	PORTD |= (1 << PD2); PORTB |= (1 << PB2);
	_delay_ms(150);
	PORTD &= ~((1 << PD2)); PORTB &= ~((1 << PB2));
	//_delay_ms(50);

	i++;
	}
	}




///////////////////////////////////// P A T T E R N   3 ///////////////////////////////////////////////////////////
	PORTB &= ~((1 << PB5));
	PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

	PORTB |= (1 << PB6);
	_delay_ms(500);


	for(j = 0; j < 10; j++) {
	uint8_t i = 0;
	////// FIRST DIAGONAL -----------------------------------
	while (i < 25) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD2);
		PORTB |= (1 << PB5);			// enable layer 3
        	_delay_ms(2);
		PORTD &= ~(1 << PD2);
		PORTB &= ~(1 << PB5);			// disable layer 3


		PORTB |= (1 << PB2);
		PORTB |= (1 << PB3);			// enable layer 1
        	_delay_ms(2);
		PORTB &= ~(1 << PB2);
		PORTB &= ~(1 << PB3);			// disable layer 1
		
		i++;
	}
	
	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// SECOND DIAGONAL -----------------------------------
	i = 0;
	while (i < 25) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD3);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD3);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTB |= (1 << PB1);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTB &= ~(1 << PB1);
		PORTB &= ~(1 << PB4);			// disable layer 2
		
		i++;
	}

	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// THIRD DIAGONAL -----------------------------------
	i = 0;
	while (i < 40) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD4);
		PORTB |= (1 << PB3);			// enable layer 1
        	_delay_ms(2);
		PORTD &= ~(1 << PD4);
		PORTB &= ~(1 << PB3);			// disable layer 1


		PORTB |= (1 << PB0);
		PORTB |= (1 << PB5);			// enable layer 3
        	_delay_ms(2);
		PORTB &= ~(1 << PB0);
		PORTB &= ~(1 << PB5);			// disable layer 3
		
		i++;
	}

	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// FOURTH DIAGONAL -----------------------------------
	i = 0;
	while (i < 40) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD7);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD7);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD5);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD5);
		PORTB &= ~(1 << PB4);			// disable layer 2
		
		i++;
	}

	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// FIFTH DIAGONAL -----------------------------------
	i = 0;
	while (i < 40) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTB |= (1 << PB2);
		PORTB |= (1 << PB5);			// enable layer 3
        	_delay_ms(2);
		PORTB &= ~(1 << PB2);
		PORTB &= ~(1 << PB5);			// disable layer 3


		PORTD |= (1 << PD2);
		PORTB |= (1 << PB3);			// enable layer 1
        	_delay_ms(2);
		PORTD &= ~(1 << PD2);
		PORTB &= ~(1 << PB3);			// disable layer 1
		
		i++;
	}
	
	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// SIXTH DIAGONAL -----------------------------------
	i = 0;
	while (i < 40) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTB |= (1 << PB1);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTB &= ~(1 << PB1);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD3);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD3);
		PORTB &= ~(1 << PB4);			// disable layer 2
		
		i++;
	}

	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// SEVENTH DIAGONAL -----------------------------------
	i = 0;
	while (i < 40) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTB |= (1 << PB0);
		PORTB |= (1 << PB3);			// enable layer 1
        	_delay_ms(2);
		PORTB &= ~(1 << PB0);
		PORTB &= ~(1 << PB3);			// disable layer 1


		PORTD |= (1 << PD4);
		PORTB |= (1 << PB5);			// enable layer 3
        	_delay_ms(2);
		PORTD &= ~(1 << PD4);
		PORTB &= ~(1 << PB5);			// disable layer 3
		
		i++;
	}

	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	PORTD |= (1 << PD6);
	PORTB |= (1 << PB4);
	//_delay_ms(40);




	////// EIGTH DIAGONAL -----------------------------------
	i = 0;
	while (i < 40) {
		
		PORTD |= (1 << PD6);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD6);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD5);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD5);
		PORTB &= ~(1 << PB4);			// disable layer 2


		PORTD |= (1 << PD7);
		PORTB |= (1 << PB4);			// enable layer 2
        	_delay_ms(2);
		PORTD &= ~(1 << PD7);
		PORTB &= ~(1 << PB4);			// disable layer 2
		
		i++;
	}

	PORTB &= ~((1 << PB2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7));
	PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
	
	//PORTD |= (1 << PD6);
	//PORTB |= (1 << PB4);
	//_delay_ms(40);
	
	j++;
    }




///////////////////////////////////// P A T T E R N   4 ///////////////////////////////////////////////////////////
	uint8_t h;
	for(h = 0; h < 5; h++) {

		uint8_t i = 0;
		while (i < 35) {
			PORTB |= (1 << PB0);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB0);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTD |= (1 << PD5);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD5);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTD |= (1 << PD2);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD2);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));



		i = 0;
		while (i < 35) {
			PORTD |= (1 << PD5);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD5);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTD |= (1 << PD2);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD2);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTD |= (1 << PD3);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD3);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));



		
		i = 0;
		while (i < 35) {
			PORTD |= (1 << PD2);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD2);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTD |= (1 << PD3);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD3);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTD |= (1 << PD4);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD4);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));



		i = 0;
		while (i < 35) {
			PORTD |= (1 << PD3);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD3);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTD |= (1 << PD4);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD4);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTD |= (1 << PD7);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD7);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));

		

		i = 0;
		while (i < 35) {
			PORTD |= (1 << PD4);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD4);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTD |= (1 << PD7);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD7);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTB |= (1 << PB2);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB2);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));



		i = 0;
		while (i < 35) {
			PORTD |= (1 << PD7);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD7);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTB |= (1 << PB2);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB2);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTB |= (1 << PB1);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB1);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));



		i = 0;
		while (i < 35) {
			PORTB |= (1 << PB2);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB2);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTB |= (1 << PB1);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB1);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTB |= (1 << PB0);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB0);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));



		i = 0;
		while (i < 35) {
			PORTB |= (1 << PB1);
			PORTB |= (1 << PB5);			// layer 3 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB1);
			PORTB &= ~(1 << PB5);			// layer 3 disable

			PORTB |= (1 << PB0);
			PORTB |= (1 << PB4);			// layer 2 enable
			_delay_ms(2);
			PORTB &= ~(1 << PB0);
			PORTB &= ~(1 << PB4);			// layer 2 enable

			PORTD |= (1 << PD5);
			PORTB |= (1 << PB3);			// layer 1 enable
			_delay_ms(2);
			PORTD &= ~(1 << PD5);
			PORTB &= ~(1 << PB3);			// layer 1 enable

			i++;
		}
		//_delay_ms(25);
		PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
		PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));

		h++;
	}



///////////////////////////////////// P A T T E R N   5 ///////////////////////////////////////////////////////////
		uint8_t g;
		for(g = 0; g < 2; g++) {
			PORTB |= (1 << PB3) | (1 << PB4) | (1 << PB5);			// enable all layers

			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(150);
			PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));			// disable all layers


			

			uint8_t i = 0;
			for(i = 0; i < 50; i++) {
				PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4);
				PORTB |= (1 << PB5);						// enable layer 3
				_delay_ms(2);
				PORTB &= ~(1 << PB5);						// disable layer 3
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4));

				PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
				PORTB |= (1 << PB4);						// enable layer 2
				_delay_ms(2);
				PORTB &= ~(1 << PB4);						// disable layer 2
				PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));		

				PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
				PORTB |= (1 << PB3);						// enable layer 1
				_delay_ms(2);
				PORTB &= ~(1 << PB3);						// disable layer 1
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));		
			}


			PORTB |= (1 << PB3);
			PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(150);
			PORTB &= ~(1 << PB0);
			PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
			PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));



			i = 0;
			for(i = 0; i < 75; i++) {
				PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4);
				PORTB |= (1 << PB3);						// enable layer 3
				_delay_ms(2);
				PORTB &= ~(1 << PB3);						// disable layer 3
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4));

				PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
				PORTB |= (1 << PB4);						// enable layer 2
				_delay_ms(2);
				PORTB &= ~(1 << PB4);						// disable layer 2
				PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));		

				PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
				PORTB |= (1 << PB5);						// enable layer 1
				_delay_ms(2);
				PORTB &= ~(1 << PB5);						// disable layer 1
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));		
				i++;
			}


			PORTB |= (1 << PB5);
			PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(150);
			PORTB &= ~(1 << PB5);
			PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
			PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));


			i = 0;
			for(i = 0; i < 50; i++) {
				PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4);
				PORTB |= (1 << PB5);						// enable layer 3
				_delay_ms(2);
				PORTB &= ~(1 << PB5);						// disable layer 3
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4));

				PORTD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
				PORTB |= (1 << PB4);						// enable layer 2
				_delay_ms(2);
				PORTB &= ~(1 << PB4);						// disable layer 2
				PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));		

				PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
				PORTB |= (1 << PB3);						// enable layer 1
				_delay_ms(2);
				PORTB &= ~(1 << PB3);						// disable layer 1
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));		
			}


			PORTB |= (1 << PB3);
			PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(150);
			PORTB &= ~(1 << PB0);
			PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
			PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
		}


///////////////////////////////////// P A T T E R N   5.1 ///////////////////////////////////////////////////////////
				uint8_t f;
		for(f = 0; f < 3; f++) {

			PORTB |= (1 << PB3);

			PORTB |= (1 << PB2);
			_delay_ms(75);
			PORTB |= (1 << PB1);
			_delay_ms(75);
			PORTB |= (1 << PB0);
			_delay_ms(75);
			PORTD |= (1 << PD5);
			_delay_ms(75);
			PORTD |= (1 << PD2);
			_delay_ms(75);
			PORTD |= (1 << PD3);
			_delay_ms(75);
			PORTD |= (1 << PD4);
			_delay_ms(75);
			PORTD |= (1 << PD7);
			_delay_ms(75);
			PORTD |= (1 << PD6);
			_delay_ms(75);


				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));


			////////////// Layer 2
			uint8_t i = 0;
			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}

			

			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}



			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}



			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD7);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}


			for(i = 0; i < 30; i++) {				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD6) | (1 << PD7);
				_delay_ms(2);
				PORTB &= ~(1 << PB4);

				
				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}




////////////// Layer 3
			i = 0;
			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}

			

			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD7);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}


			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD7) | (1 << PD6);
				_delay_ms(2);
				PORTB &= ~(1 << PB5);

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB3));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			}






			////// turn off layer 1
			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD7);
				PORTD &= ~(1 << PD6);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}


			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3) | (1 << PD4);
				PORTD &= ~(1 << PD6) | (1 << PD7);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}


			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2) | (1 << PD3);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}


			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5) | (1 << PD2);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD |= (1 << PD5);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1) | (1 << PB0);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}




			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2) | (1 << PB1);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5);
				PORTB &= ~(1 << PB0);
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}


			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTB |= (1 << PB2);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5);
				PORTB &= ~((1 << PB0) | (1 << PB1));
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}



			for(i = 0; i < 25; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB4));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));

				PORTB |= (1 << PB3);
				PORTD &= ~(1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5);
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				_delay_ms(2);
				PORTB &= ~(1 << PB3);

			}




			////// turn off layer 2
			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				PORTD &= ~((1 << PD6));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}


			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				PORTD &= ~((1 << PD6) | (1 << PD7));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}



			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5);
				PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}



			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5);
				PORTD |= (1 << PD2);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}



			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}


			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}



			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB1); PORTB |= (1 << PB2);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5));
				PORTB &= ~((1 << PB0));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}



			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTB |= (1 << PB2);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5));
				PORTB &= ~((1 << PB0) | (1 << PB1));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}


			for(i = 0; i < 35; i++) {				
				PORTB |= (1 << PB5);
				PORTB |= (1 << PB2); PORTB |= (1 << PB1); PORTB |= (1 << PB0);
				PORTD |= (1 << PD5); PORTD |= (1 << PD6); PORTD |= (1 << PD7);
				PORTD |= (1 << PD4); PORTD |= (1 << PD3); PORTD |= (1 << PD2);
				_delay_ms(1);
				PORTB &= ~((1 << PB5));
				PORTD &= ~((1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7));
				PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
				
				PORTB |= (1 << PB4);
				PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5));
				PORTB &= ~((1 << PB2) | (1 << PB1) | (1 << PB0));
				_delay_ms(1);
				PORTB &= ~((1 << PB4));

			}




			////// turn off layer 3
			PORTD |= ((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5));
			PORTB |= ((1 << PB2) | (1 << PB1) | (1 << PB0));
			PORTB |= (1 << PB5);
			_delay_ms(75);			


			PORTD &= ~(1 << PD6);
			PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5) | (1 << PD7);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7));
			PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4));
			PORTD |= (1 << PD2) | (1 << PD3) | (1 << PD5);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3));
			PORTD |= (1 << PD2) | (1 << PD5);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2));
			PORTD |= (1 << PD5);
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD5));
			PORTB |= (1 << PB0) | (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD4));
			PORTB &= ~((1 << PB0));
			PORTB |= (1 << PB1) | (1 << PB2);
			_delay_ms(75);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD4));
			PORTB &= ~((1 << PB0) | (1 << PB1));
			PORTB |= (1 << PB2);
			_delay_ms(50);

			PORTD &= ~((1 << PD6) | (1 << PD7) | (1 << PD4) | (1 << PD3) | (1 << PD2) | (1 << PD4));
			PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
			_delay_ms(75);
			
		
		PORTB &= ~((1 << PB3) | (1 << PB4) | (1 << PB5));


		}

	
    }
}
