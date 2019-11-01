/*	Author: oocho002
 *  Partner(s) Name: Gurparam
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//#define A0 ~PINA & 0x01
double arr[] = { 261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};
enum states {wait, press0, press1, both} state;
enum speakers {on, off} speaker;
unsigned char tmpB = 0x00;
void tick() {
	switch(state) {
		
		case wait:
		{
			if ((~PINA & 0x03) == 0x00) {
				set_PWM(arr[tmpB]);
                                state = wait;
                                break;
                        }
			else if ((~PINA & 0x03) == 0x03) {
                                state = both;
                                tmpB = 0;
                                set_PWM(arr[tmpB]);
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x01) {
                                state = press0;
				if (tmpB < 7) {
					tmpB = tmpB + 1;
				}
                                set_PWM(arr[tmpB]);
                                break;
                        }
			else if ((~PINA & 0x03) == 0x02) {
                                state = press1;
                                if (tmpB > 0) {
                                        tmpB = tmpB - 1;
                                }
                                set_PWM(arr[tmpB]);
                                break;
                        }
		}
		case press0:
		{		
			if ((~PINA & 0x03) == 0x00) {
                                state = wait;
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x03) {
                                state = both;
                                tmpB = 0;
                                set_PWM(arr[tmpB]);
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x01) {
				set_PWM(arr[tmpB]);
                                state = press0;
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x02) {
                                state = press1;
                                if (tmpB > 0) {
                                        tmpB = tmpB - 1;
                                }
                                set_PWM(arr[tmpB]);
                                break;
                        }	
		}
		case press1:
		{	
		        if ((~PINA & 0x03) == 0x00) {
                                set_PWM(arr[tmpB]);
				state = wait;
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x03) {
                                state = both;
                                tmpB = 0;
                                set_PWM(arr[tmpB]);
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x01) {
                                state = press0;
                                if (tmpB < 9) {
                                        tmpB = tmpB + 1;
                                }
                                set_PWM(arr[tmpB]);
                                break;
                        }
          		else if ((~PINA & 0x03) == 0x02) {
				set_PWM(arr[tmpB]);
                                state = press1;
                                break;
                        }
		}
		case both:
		{	
		        if ((~PINA & 0x03) == 0x00) {
				set_PWM(arr[tmpB]);
                                state = wait;
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x03) {
				set_PWM(arr[tmpB]);
                                state = both;
                                break;
                        }
                        else if ((~PINA & 0x03) == 0x01) {
                                set_PWM(arr[tmpB]);
                                state = both;
                                break;
                        }
          		else if ((~PINA & 0x03) == 0x02) {
                                set_PWM(arr[tmpB]);
                                state = both;
                                break;
                        }
		}	
		default:
		{
			state = press0;
			break;
		}
	}
	switch(state) {
		case wait:
		{
                        break;
		}
                case press0:
		{
                        break;
		}
                
                case press1:
		{
                        break;
		}
                case both:
		{
                        break;
		}
        }
}
void tick2() {
        switch(speaker) {

                case off:
                {
                        if ((~PINA & 0x03) == 0x00) {

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	state = wait;
	PWM_ON();
//	unsigned char A0 = 0x00;
	while(1) {
//		A0 = PINA & 0x01;
		tick();
		tick2();
	}
    return 1;
}
