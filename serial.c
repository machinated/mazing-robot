#include "serial.h"
#include "def.h"

void initSerial(unsigned int ubrr)
{
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char) ubrr;

	UCSRB |= (1 << TXEN);
	// Enable transmiter
	// UCSRB |= (1 << RXCIE);                   
	// Enable the receiver interrupt
	UCSRC |= (1 << URSEL) |(1 << UCSZ1) | (1 << UCSZ0);    
	// Set frame: 8data, 1 stp
	// sei()
}

void serialSendChar(char data)
{
	while( ! BIT_CHECK(UCSRA, UDRE));		// USART Data Register Empty

	UDR = data;
}

void serialSendStr(char* str)
{
	while(*str != '\0')
	{
		serialSendChar(*str);
		str++;
	}
}

void serialSendInt(int reg, int8_t last)
{
	char out[5];
	int k = 4, i;

	for (i = 0; i < 5; i++) 
	{
		
		out[k] = '0' + (reg % 10);
		reg /= 10;
		k--;
	}

	for (i = 0; i < 5; i++) 
	{
		serialSendChar(out[i]);
	}

	if (last) {
		serialSendChar('\n');
	}
	else {
		serialSendChar(' ');
	}
}

void sendSensors()
{
	serialSendInt(LL, 0);
	serialSendInt(LM, 0);
	serialSendInt(RM, 0);
	serialSendInt(RR, 0);

	serialSendInt(OCR1A, 0);
	serialSendInt(OCR1B, 1);
}

/*
ISR (USART_RXC_vect)
{
	static char SerialBuffer[20];
	static int i;
	char data = UDR;
	
	if (data == '\n')
	{
		i = 0;
	}
	else
	{
		SerialBuffer[i++] = data;
	}
}
*/
