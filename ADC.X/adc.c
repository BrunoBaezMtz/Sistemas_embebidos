
//file: adc
// autor: BRuno

#include <xc.h>
#define _XTAL_FREQ 20000000 //20MHz

void lcdCommand(unsigned char cmd){
    RS = 0;
    PORTD = cmd;
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(1);
    
}

void lcdCommand(unsigned char data){
    RS = 0;
    PORTD = data;
    EN = 1;
    __delay_ms(1);
    EN = 0;
    __delay_ms(1);
    
}

void adc_init(void){
    TRISA = 0b00000001; //pin AN0
    
    ADCON1 = 0b11001110;
    
    /*
     bit 0 ADCON = 1 - enciende el ADC
     bit 2 godone = 0
     bit 3-5  canal 0
     bit 6-7 110
     */
    ADCON0 = 0b10000001;
    
    __delay_us(20);
}

unsigned int adc_read_an0(void){
    __delay_us(20);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((unsigned int)ADRESH<<8|ADRESL);
    
}

void main(void){
    adc_init();
    
    while (1){
        uint16_t
    }
}