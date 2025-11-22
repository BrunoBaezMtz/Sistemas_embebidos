#include <xc.h>
#define _XTAL_FREQ 4000000


void main(void){

unsigned char NUMBER[10]= {
0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F
};

    TRISC = 0x00;
    TRISB = 0x11;
    unsigned char contador = 0;
    PORTC = NUMBER[contador];

    while(1){
        if(PORTBbits.RB0 == 0)
            __delay_ms(20);
    
            if(PORTCbits.RC0 == 0)
                contador++;
                if(contador>9)contador = 0;
                    PORTB = NUMBER[contador];
                while(PORTBbits.RB0 == 0);
                    __delay_ms(20);
            
    
    }
    
}
