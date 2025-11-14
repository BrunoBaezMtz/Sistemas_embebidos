#define _XTAL_FREQ 80000000   //CORAZON CLOCK
#include <xc.h>

void main(void) {
    TRISB = 0b00000000;   //Establece B como salida  
   
 while(1) {
/*encender leds
 * uno por uno
 */
    PORTB = 0b00000001; //led 0
    __delay_ms(500);
    
    PORTB = 0b00000010; // led 1
    __delay_ms(500);
    
     PORTB = 0b00000100; // led 2
    __delay_ms(500);
    
    PORTB = 0b00001000; // led 3
    __delay_ms(500);
    
     PORTB = 0b00010000; // led 4
    __delay_ms(500);
    
    PORTB = 0b00100000; // led 5
    __delay_ms(500);
    
     PORTB = 0b01000000; // led 6
    __delay_ms(500);
    
    PORTB = 0b10000000; // led 7
    __delay_ms(500);
    
    PORTB = 0b00000000; // apagar leds
    __delay_ms(500);
    }
    return;
    
}
