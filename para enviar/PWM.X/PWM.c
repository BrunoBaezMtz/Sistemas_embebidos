/* 
 * File:   PWM.c
 * Author: BZ
 *
 * Created on 10 de noviembre de 2025, 08:30 AM
 */

#define _XTAL_FREQ 4000000
#include <xc.h>

/*
 *
 */
void main() {
    while(1){
    TRISC = 0b00000000; //0--> pin como salida
    TRISB = 0b00001111; // 0,1,2, y , 3 como entrada
    T2CON = 0b00000101; //prescaler de 4
    PR2 = 249;          // frecuencia de 1KHZ
    
    if (PORTBbits.RB1 == 1);{    // DUTY CYCLE 100%
        CCPR1L = 0b1111101000;
        CCP1CON = 0b00001100;
}
    
    if (PORTBbits.RB1 == 1);{    // DUTY CYCLE 75%
        CCPR1L = 0b1011101110;
        CCP1CON = 0b00001100;
    }
        
    if (PORTBbits.RB1 == 1);{    // DUTY CYCLE 50%
        CCPR1L = 0b0111110100;
        CCP1CON = 0b00001100;    
    }
        
        
    if (PORTBbits.RB1 == 0);{    // DUTY CYCLE 25%
        CCPR1L = 0b0011111010;
        CCP1CON = 0b00001100;
    }
    }
}

