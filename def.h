#ifndef DEF_H_
#define DEF_H_
#define __DELAY_BACKWARD_COMPATIBLE__
//#define F_CPU 1000000
#include <util/delay.h>
#include <avr/io.h>
#include <math.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern uint8_t sensors[4];


/* a = register, b = bit number */
#define BIT_SET(a,b) ((a) |= (1<<b))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<b))
#define BIT_FLIP(a,b) ((a) ^= (1<<b))
#define BIT_CHECK(a,b) ((a) & (1<<b))

/* a = register, b = mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))

#define BITMASK(x) (1<<x)

#define PWM_L   PB1
#define PWM_R   PB2
#define BR		PB0
#define FR		PB3
#define FL		PB5
#define BL		PB4
#define BUTTON	PD2
#define YLED	PB6
#define GLED	PB7
#define LEFT -1
#define RIGHT 1

//#define K 1.3
#define MAX_SPEED 70
#define MIN_SPEED 0
#define FOLLOW_SENSITIVITY 0.5
#define LL sensors[3]
#define LM sensors[2]
#define RM sensors[1]
#define RR sensors[0]

#endif /* DEF_H_ */
