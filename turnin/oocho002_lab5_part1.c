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

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	unsigned int tmpC = 0;
	unsigned char tmpA = 0x00;
	unsigned char curA = 0x00;
	unsigned char curC = 0x00;
	while(1) {
		tmpA = PINA & 0xFF;
		curA = tmpA & 0x01;
		tmpC = 0;
		if (curA == 0x01) {
			tmpC = tmpC + 1;
		}
		curA = tmpA & 0x02;
                if (curA == 0x02) {
			tmpC = tmpC + 2;
		}
		curA = tmpA & 0x04;
                if (curA == 0x04) {
			tmpC = tmpC + 4;
		}
		curA = tmpA & 0x08;
                if (curA == 0x08) {
			tmpC = tmpC + 8;
		}
		if (tmpC == 0) {
                        curC = 0x40;
                }
		else if (tmpC <= 2) {
			curC = 0x60;
		}
		else if (tmpC <= 4) {
                        curC = 0x70;
                }
		else if (tmpC <= 6) {
                        curC = 0x38;
                }
		else if (tmpC <= 9) {
                        curC = 0x3C;
                }
		else if (tmpC <= 12) {
                        curC = 0x3E;
                }
		else if (tmpC <= 15) {
                        curC = 0x3F;
                }
		PORTC = curC;
	}
    return 1;
}
