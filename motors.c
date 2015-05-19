#include "motors.h"
#include "sensors.h"
#include "delay.h"
#include "serial.h" // for debugging

void initMotors()
{
	BIT_SET(DDRB, PWM_L);
	BIT_SET(DDRB, PWM_R);
	BIT_SET(DDRB, FL);
	BIT_SET(DDRB, FR);
	BIT_SET(DDRB, BL);
	BIT_SET(DDRB, BR);
	
	// PWM setup
	TCCR1A |= (1<<WGM10);						// Fast PWM 8bit
	TCCR1B |= (1<<WGM12);
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1);
	//Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM, (non-inverting mode)
	TCCR1B |= (1<<CS10)|(1<<CS11);				// Prescaler = 64  fpwm = 60 Hz
												// fpwm = F_CPU / (prescaler * 256)
}

void motors(int16_t left, int16_t right) 
{
	OCR1A = abs(left);
	OCR1B = abs(right);
	
	PORTB &= 0b11000110;
	
	if( left > 0 )
		BIT_SET(PORTB, FL);
	else if (left < 0)
		BIT_SET(PORTB, BL);
	
	if( right > 0 )
		BIT_SET(PORTB, FR);
	else if (right < 0)
		BIT_SET(PORTB, BR);
}

void motors_time(int16_t left, int16_t right, int16_t time)
{
	motors(left, right);
	delay(time);
	motors(0, 0);
}

void waitForLine()
{
	do
	{
		delay(10);
		scanSensors();
	}
	while(LM + RM < 150);
}

void turn(int direction) 
{
	motors_time(MAX_SPEED, MAX_SPEED, 250);
	motors(direction * MAX_SPEED, -direction * MAX_SPEED);
	delay(300);
	waitForLine();
	motors(-direction * (MAX_SPEED>>1), direction * (MAX_SPEED>>1));
	waitForLine();

	motors(0,0);
}

void turn_back() 
{
	motors_time(MAX_SPEED, MAX_SPEED, 250);
	motors(MAX_SPEED, -MAX_SPEED);
	delay(500);
	waitForLine();
	motors(-MAX_SPEED>>1, MAX_SPEED>>1);
	waitForLine();

	motors(0,0);
}

uint8_t calc_speed(int sensor) 
{
	return MIN_SPEED + (MAX_SPEED-MIN_SPEED) * sensor / 100;
	//return (MAX_SPEED * sensor * 10) >> 10;
}

void follow() 
{
	uint8_t speed, dir;
	speed = MIN_SPEED + (unsigned int)((MAX_SPEED - MIN_SPEED) * (LM + RM)) / 200;
	dir = (RM - LM) * FOLLOW_SENSITIVITY;
	motors((uint8_t)(speed + dir), (uint8_t)(speed - dir));
	/*
	uint8_t speedL, speedR;
	speedL = calc_speed(RM);
	speedR = calc_speed(LM);
	motors(speedL, speedR);
	*/
	//motors(calc_speed(RM), calc_speed(LM));
}
