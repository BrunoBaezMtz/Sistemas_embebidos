/* 
 * File:   COUNTER.c
 * Author: BZ
 *
 * Created on 20 de noviembre de 2025, 12:45 AM
 */

#include <xc.h>
#define __XTAL_FREQ 4000000


/*
 * 
 */
unsigned char TBL[10]{
0x3F,
0x06,
0x5B,
0x4F,
0x66,
0x6D,
0x7D,
0x07,
0x7F,
0x6F
}

void main(void){
    TRISA = 0x00;
    TRISB = 0x01;
    
    unsigned char contador = 0;
    PORTA = TBL[contador];
    
}
