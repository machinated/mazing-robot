#include "sensors.h"
#include "motors.h"

void initSensors()
{
	ADMUX = 0x01;
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	// sei();
}

void scanSensors()
{	
	int i;
	for (i = 1; i < 5; i++)
	{	
		ADMUX = i;
		BIT_SET(ADCSRA, ADSC);				// single conversion
		while(BIT_CHECK(ADCSRA, ADSC)) ;	// wait for conversion
		
		sensors[i - 1] = ADC/10;
	}
}

//int current_sensor = 1;
//
//ISR(ADC_vect) {
	//
	//sensors[current_sensor-1] = ADC/10;
	//
	//if (current_sensor < 4) {
		//current_sensor++;
	//}
	//else {
		//current_sensor = 1;
	//}
	//
	//ADMUX = current_sensor;
//}
