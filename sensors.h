#ifndef SENSORS_H_
#define SENSORS_H_
#include "def.h"

uint8_t sensors[4];

void initSensors();
//ISR(ADC_vect);
void scanSensors();

#endif /* SENSORS_H_ */
