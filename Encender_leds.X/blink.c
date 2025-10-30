#define _XTAL_FREQ 80000000   //CORAZON CLOCK
#include <xc.h>

void main(void) {
    TRISB = 0b00000000;   //Establece B como salida  
   
 while(1) {

    PORTB = 0b00000110;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b01011011;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b01001111;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b11100110;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b11101101;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b11111101;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b10000111;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b11111111;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    
     PORTB = 0b10111111;
    __delay_ms(1000);
    PORTB = 0b00000000;
    __delay_ms(1000);
    }
    return;

}

void main(void){
    TRISA = 0b11111111;
        TRISB = 0x00;   //B como salida
        TRISA = 0xFF;   //A como entrada
        if (PORTAbits.RA0 == 1){
        }
    return;
        
}

