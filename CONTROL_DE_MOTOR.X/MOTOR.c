/* 
 * File:   MOTOR.c
 * Author: BZ
 *
 * Created on 13 de noviembre de 2025, 07:35 AM
 */
#define __XTAL_FREQ 4000000
#include <xc.h>
/*
 * 
 */
void pwm_init(void){
        while(1){
    TRISC = 0b00000000; //0--> pin como salida
    CCP1CON = 0b00000111; //configuracion modo pwm
                          // se limpian 2 bits
    CCPR1L = 0b00000000; //se limpian 8 bits
    PR2 = 249;          // frecuencia de 1KHZ
    T2CON = 0b00000101; //Encendido TM2 y prescales 4
}
}
void set_percent(unsigned char percent){
    if (percent>100){
        percent = 100;
        
    }
    unsigned int max_counts = (unsigned int)(4U*(PR2+1));
    unsigned int dc = (unsigned int)((unsigned long)percent*max_counts/100UL);
    CCPR1L = (unsigned char)(dc>>2);
    CCP1CONbits.CCP1X = (dc>>1)&1;
    CCP1CONbits.CCP1Y = dc&1;
    }

void main(){
    pwm_init();
    
    set_percent(50); //establece el duty cycle al 50%
    
    while(1){
        
    }
}
