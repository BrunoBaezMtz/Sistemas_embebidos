/* 
 * File:   MOTOR.c
 * Author: BZ
 *
 * Created on 13 de noviembre de 2025, 07:35 AM
 */
#pragma config FOSC = XT        // Oscilador de cristal XT (4 MHz)
#pragma config WDTE = OFF       // Watchdog Timer deshabilitado
#pragma config PWRTE = OFF       // Power-up Timer habilitado
#pragma config BOREN = ON       // Brown-out Reset habilitado
#pragma config LVP = OFF        // Low Voltage Programming deshabilitado
#pragma config CPD = OFF        // Protecci?n de EEPROM deshabilitada
#pragma config WRT = OFF        // Escritura de Flash deshabilitada
#pragma config CP = OFF   

#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
#include<string.h>
/*
 * 
 */
void adc_init(void){
    ADCON1 = 0b00000010;
    ADCON0 = 0b01000000;
    
}

unsigned int adc_read(unsigned char channel){
    ADCON0 &= 0b11000111;
    ADCON0 |= (channel <<3);
    ADCON0bits.ADON = 1;
    __delay_ms(20);
        
    ADCON0bits.GO = 1;
    
    while(ADCON0bits.GO_nDONE);
    return((ADRESH << 8) + ADRESL);
    
}


void pwm_init(void){

    TRISCbits.TRISC2 = 0; 
    CCP1CON = 0b00001100; 
                          
    CCPR1L = 0; 
    PR2 = 249;          
    T2CON = 0b00000101; 
}

// Función simplificada para mapear ADC a Porcentaje
void set_pwm_from_adc(unsigned int adc_value){
    // El ADC va de 0 a 1023.
    // El PWM (PR2=249) tiene una resolución de 1000 pasos (aprox).
    // Podemos pasar el valor casi directo.
    
    // Mapeo simple: (ADC * 100) / 1023 para obtener porcentaje
    unsigned long temp = (unsigned long)adc_value * 100;
    unsigned char percent = (unsigned char)(temp / 1023);
    
    // Usamos tu lógica anterior para setear el PWM
    unsigned int max_counts = (unsigned int)(4 * (PR2 + 1));
    unsigned int dc = (unsigned int)((unsigned long)percent * max_counts / 100UL);
    
    CCPR1L = (unsigned char)(dc >> 2);
    CCP1CONbits.CCP1Y = dc & 1;       // Bit menos significativo
    CCP1CONbits.CCP1X = (dc >> 1) & 1; // Segundo bit menos significativo
}

void main(){
    TRISB = 0xFF; 
    TRISA = 0x00; // RA0 y RA1 salidas para el motor
    
    // IMPORTANTE: RA2 debe ser entrada para el potenciómetro
    TRISAbits.TRISA2 = 1; 

    pwm_init();
    adc_init(); // Inicializamos el módulo ADC
    
    unsigned int pot_value = 0;
    
    while(1){
        // 1. CONTROL DE GIRO (Botones RB0 y RB1)
        if(PORTBbits.RB0 == 1){
            PORTA = 0b00000001; // Giro Derecha
        }    
        else if(PORTBbits.RB1 == 1){
            PORTA = 0b00000010; // Giro Izquierda
        }
        else {
            // Opcional: Si no aprietas nada, ¿quieres que se detenga o siga?
            // Si quieres que pare al soltar botones, descomenta esto:
            // PORTA = 0x00; 
        }

        // 2. CONTROL DE VELOCIDAD (Potenciómetro)
        // Leemos el canal 2 (RA2)
        pot_value = adc_read(2); 
        
        // Actualizamos la velocidad del motor
        set_pwm_from_adc(pot_value);
        
        __delay_ms(10); // Pequeña pausa para estabilidad
    }
}