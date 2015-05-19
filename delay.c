#include "def.h"
#include "delay.h"

void delay(unsigned int ms)
{
	while(ms > 100)
	{
		_delay_ms(100);
		ms -= 100;
	}
	_delay_ms(ms);
}
