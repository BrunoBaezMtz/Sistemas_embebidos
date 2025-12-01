/* 
 * File:   PREGUNTA_7.c
 * Author: BZ
 *
 * Created on 1 de diciembre de 2025, 07:51 AM
 */

#define _XTAL_FREQ 20000000
#include <stdio.h>
#include <xc.h>


/*
 * 
 */
void main(void){
    TRISB = 0b00000010;
    
    while(1){
        if (PORTBbits.RB1 == 1){
            PORTBbits.RB0 = 1;
        }
        else {
            PORTBbits.RB0 = 0;
        }
    }
}