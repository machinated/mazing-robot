#include "def.h"
#include "delay.h"
#include "motors.h"
#include "serial.h"
#include "sensors.h"

void initIO()
{
	BIT_CLEAR(DDRB, BUTTON);	// button as input
	BIT_CLEAR(PORTD, BUTTON);	// no pull-up
	// LEDs
	BIT_SET(DDRB, YLED);
	BIT_SET(DDRB, GLED);
}

void check_start_pos() 
{
	while( BIT_CHECK(PIND, BUTTON) )
	{
		scanSensors();
		if( LM > 70 )
			BIT_SET(PORTB, GLED);
		else
			BIT_CLEAR(PORTB, GLED);
		if( RM > 70 )
			BIT_SET(PORTB, YLED);
		else
			BIT_CLEAR(PORTB, YLED);
	}
	BIT_CLEAR(PORTB, GLED);
	BIT_CLEAR(PORTB, YLED);
}

int8_t make_decision() 
{
	if (LM > 60 && RM > 60 && (LL > 80 || RR > 80))
	{
		motors_time(MAX_SPEED, MAX_SPEED, 30);
		delay(300);
		scanSensors();
		if(RR > 80)					// path to the right
		{
			BIT_SET(PORTB, YLED);
			motors_time(MAX_SPEED, MAX_SPEED, 200);
			delay(300);
			turn(RIGHT);
			delay(300);
			return 1;
		}
		else if(LL > 80)			// path to the left
		{
			BIT_SET(PORTB, YLED);
			motors_time(MAX_SPEED, MAX_SPEED, 200);
			delay(300);
			scanSensors();
			if (LM + RM < 50)		// no path in front
			{
				turn(LEFT);
				delay(300);
				return 1;
			}
		}
	}
	else if(LM + RM < 50)		// no path in front
	{
		BIT_SET(PORTB, YLED);
		motors_time(MAX_SPEED, MAX_SPEED, 200);
		delay(300);
		scanSensors();
		if (LM + RM > 140)		// finish marker
		{
			motors(0, 0);
			BIT_SET(PORTB, GLED);	// turn on green LED
			BIT_CLEAR(PORTB, YLED);
			while (666) {}
		}
		else 
		{
			turn_back();
			delay(300);
			return 1;
		}
	}

	BIT_CLEAR(PORTB, YLED);
	return 0;
}

void flashGLED()
{
	if (BIT_CHECK(PORTB, GLED))
	{
		BIT_CLEAR(PORTB, GLED);
	}
	else
	{
		BIT_SET(PORTB, GLED);
	}
}

int main(void)
{
	initIO();
	initSensors();
	initMotors();
	initSerial(USART_UBRR);
		
	motors(0,0);
	check_start_pos();

	uint8_t ignoreIntersection = 20;
	
	while( 666 )
	{
		scanSensors();

		if (!ignoreIntersection)
		{
			int8_t decision = make_decision();
			if(decision)
			{
				ignoreIntersection = 20;
			}
		}
		else
		{
			flashGLED();
			ignoreIntersection--;
		}

		follow();
		//sendSensors();
		delay(20);
	}
}
