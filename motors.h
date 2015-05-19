#ifndef MOTORS_H_
#define MOTORS_H_

#include "def.h"

void initMotors();
void motors(int16_t left, int16_t right);
void motors_time(int16_t left, int16_t right, int16_t time);
void turn(int direction);
void turn_back();
void follow();

#endif /* MOTORS_H_ */
