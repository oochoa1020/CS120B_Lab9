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
enum speakers {wait, A, B, C} speaker;
unsigned char tmpB = 0x00;

void set_PWM(double frequency) {
	static double current_frequency;
	if (frequency != current_frequency) {
		if (!frequency) { TCCR3B &= 0x08; }
		else { TCCR3B |= 0x03; }
		if (frequency < 0.954) { OCR3A = 0xFFFF; }
		else if (frequency > 31250) { OCR3A = 0x0000; }
		else { OCR3A = (short)(8000000/(128 * frequency)) - 1; }
		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
        TCCR3B = 0x00;
}

void tick() {
        switch(speaker) {

		case wait:
		{
			if ((~PINA & 0x07) == 0x01) {
				speaker = A;
				set_PWM(arr[0]);
				PORTB = 0x40;
				break;
			}
			else if ((~PINA & 0x07) == 0x02) {
                                speaker = B;
				set_PWM(arr[1]);
                                PORTB = 0x40;
                                break;
                        }
			else if ((~PINA & 0x07) == 0x04) {
                                speaker = C;
				set_PWM(arr[2]);
                                PORTB = 0x40;
                                break;
                        }
			else {
				speaker = wait;
				PORTB = 0x00;
				break;
			}
		}
		case A:
		{
			if ((~PINA & 0x07) == 0x01) {
				speaker = A;
				PORTB = 0x40;
				break;
			}
			else if ((~PINA & 0x07) == 0x02) {
                                speaker = B;
				set_PWM(arr[1]);
                                PORTB = 0x40;
                                break;
                        }
			else if ((~PINA & 0x07) == 0x04) {
                                speaker = C;
				set_PWM(arr[2]);
                                PORTB = 0x40;
                                break;
                        }
			else {
				speaker = wait;
				PORTB = 0x00;
				break;
			}
		}
		case B:
		{
			if ((~PINA & 0x07) == 0x01) {
				speaker = A;
				set_PWM(arr[0]);
				PORTB = 0x40;
				break;
			}
			else if ((~PINA & 0x07) == 0x02) {
                                speaker = B;
                                PORTB = 0x40;
                                break;
                        }
			else if ((~PINA & 0x07) == 0x04) {
                                speaker = C;
				set_PWM(arr[2]);
                                PORTB = 0x40;
                                break;
                        }
			else {
				speaker = wait;
				PORTB = 0x00;
				break;
			}
		}
		case C:
		{
			if ((~PINA & 0x07) == 0x01) {
				speaker = A;
				set_PWM(arr[0]);
				PORTB = 0x40;
				break;
			}
			else if ((~PINA & 0x07) == 0x02) {
                                speaker = B;
				set_PWM(arr[1]);
                                PORTB = 0x40;
                                break;
                        }
			else if ((~PINA & 0x07) == 0x04) {
                                speaker = C;
                                PORTB = 0x40;
                                break;
                        }
			else {
				speaker = wait;
				PORTB = 0x00;
				break;
			}
		}


		default:
		{
			speaker = wait;
			break;
		}
	}
	switch(speaker) {

                case wait:
                {
			break;
		}
		case A:
		{
			break;
		}
		case B:
                {
                        break;
                }
		case C:
                {
                        break;
                }
	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	speaker = wait;
	PWM_ON();
//	unsigned char A0 = 0x00;
	while(1) {
//		A0 = PINA & 0x01;
		tick();
	}
    return 1;
}
