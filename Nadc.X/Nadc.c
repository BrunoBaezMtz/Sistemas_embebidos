
#pragma config FOSC = XT        // Oscilador de cristal XT (4 MHz)
#pragma config WDTE = OFF       // Watchdog Timer deshabilitado
#pragma config PWRTE = OFF       // Power-up Timer habilitado
#pragma config BOREN = ON       // Brown-out Reset habilitado
#pragma config LVP = OFF        // Low Voltage Programming deshabilitado
#pragma config CPD = OFF        // Protecci?n de EEPROM deshabilitada
#pragma config WRT = OFF        // Escritura de Flash deshabilitada
#pragma config CP = OFF   
#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000      // Frecuencia del oscilador (4 MHz)

// ==================== DEFINICIONES PARA LCD ====================
#define RS PORTAbits.RA0        // Pin RS del LCD (Registro Select)
#define EN PORTAbits.RA1        // Pin Enable del LCD
#define LCD_DATA PORTB          // Puerto de datos del LCD (B0-B7)

// ==================== FUNCIONES ====================
void LCD_Init(void);
void LCD_Cmd(unsigned char cmd);
void LCD_Data(unsigned char data);
void LCD_String(const char *str);
void LCD_Clear(void);
void LCD_Goto(unsigned char row, unsigned char col);
void ADC_Init(void);
unsigned int ADC_Read(unsigned char channel);

// ==================== FUNCION PRINCIPAL ====================
void main(void) {
    unsigned int adc_value;     // Valor RAW del ADC (0-1023)
    unsigned int millivolts;    // Valor en milivolts (0-5000)
    char buffer[16];            // Buffer para conversi?n de n?meros a texto
    
    // Configuracion de puertos
    TRISB = 0x00;               // Puerto B como salida (LCD datos)
    TRISA = 0x00;               // Puerto A como salida (LCD control)
    TRISA = 0b00000100;         // RA2 como entrada, RA0 y RA1 como salidas
    TRISC = 0x00;               // Puerto C como entrada (AN0)
    
    // Inicializacion de perifericos
    LCD_Init();                 // Inicializar LCD
    ADC_Init();                 // Inicializar ADC
    
    // Mensaje inicial
    LCD_Clear();
    LCD_String("  ADC PIC16F877A");
    LCD_Goto(2, 1);
    LCD_String("Inicializando...");
    __delay_ms(2000);
    
    LCD_Clear();
    LCD_String("RAW:");
    LCD_Goto(2, 1);
    LCD_String("mV:");
    
    // Bucle principal infinito
    while(1) {
        // Leer valor del ADC en el canal AN0
        adc_value = ADC_Read(0);
        
        // Convertir valor RAW a milivolts
        // Formula: mV = (adc_value * 5000) / 1023
        millivolts = (unsigned int)((unsigned long)adc_value * 5000 / 1023);
        
        // Mostrar valor RAW en la primera linea
        LCD_Goto(1, 6);
        sprintf(buffer, "%4u   ", adc_value);  // 4 digitos + espacios
        LCD_String(buffer);
        
        // Mostrar valor en milivolts en la segunda l?nea
        LCD_Goto(2, 5);
        sprintf(buffer, "%4u mV ", millivolts);
        LCD_String(buffer);
        
        __delay_ms(100);        // Actualizacion cada 100 ms
    }
}


void ADC_Init(void) {
    /*
     * ADCON0: Configuraci?n del modulo ADC
     * Bit 7-6 (ADCS1:ADCS0): 01 = Fosc/8 (tiempo de conversi?n adecuado a 4MHz)
     * Bit 5-3 (CHS2:CHS0): 000 = Canal AN0 seleccionado
     * Bit 2 (GO/DONE): 0 = No iniciar conversi?n a?n
     * Bit 0 (ADON): 1 = Modulo ADC encendido
     */
    ADCON0 = 0b01000001;
    
    /*
     * ADCON1: Configuracion de pines y referencias
     * Bit 7 (ADFM): 1 = Resultado justificado a la derecha
     * Bit 3-0 (PCFG3:PCFG0): 1110 = Solo AN0 como anal?gico, resto digital
     *                         Vref+ = VDD (5V), Vref- = VSS (0V)
     */
    ADCON1 = 0b10001110;
    
    __delay_ms(20);             // Tiempo de estabilizacion del ADC
}


unsigned int ADC_Read(unsigned char channel) {
    unsigned int result;
    
    // Seleccionar el canal (bits CHS2:CHS0 en ADCON0)
    // Limpiar bits 5-3 y establecer nuevo canal
    ADCON0 &= 0b11000111;       // Limpiar CHS2:CHS0
    ADCON0 |= (channel << 3);   // Establecer nuevo canal
    
    __delay_us(20);             // Tiempo de adquisici?n (Tacq m?nimo)
    
    // Iniciar conversi?n
    GO_nDONE = 1;               // Poner bit GO/DONE en 1
    
    // Esperar a que termine la conversi?n
    while(GO_nDONE);            // Esperar mientras GO/DONE = 1
    
    // Leer resultado (10 bits: ADRESH + ADRESL)
    result = (ADRESH << 8) | ADRESL;
    
    return result;              // Retornar valor de 0 a 1023
}


void LCD_Init(void) {
    __delay_ms(50);             // Esperar estabilizaci?n de LCD
    
    LCD_Cmd(0x38);              // Modo 8 bits, 2 l?neas, 5x7 puntos
    LCD_Cmd(0x0C);              // Display ON, cursor OFF
    LCD_Cmd(0x06);              // Incrementar cursor autom?ticamente
    LCD_Cmd(0x01);              // Limpiar pantalla
    __delay_ms(2);
}


void LCD_Cmd(unsigned char cmd) {
    RS = 0;                     // RS = 0 para comando
    LCD_DATA = cmd;             // Enviar comando al puerto de datos
    EN = 1;                     // Pulso de habilitaci?n
    __delay_us(1);
    EN = 0;
    __delay_ms(2);              // Tiempo de procesamiento
}


void LCD_Data(unsigned char data) {
    RS = 1;                     // RS = 1 para dato
    LCD_DATA = data;            // Enviar dato al puerto de datos
    EN = 1;                     // Pulso de habilitaci?n
    __delay_us(1);
    EN = 0;
    __delay_ms(2);
}


void LCD_String(const char *str) {
    while(*str) {               // Mientras no sea fin de cadena
        LCD_Data(*str++);       // Enviar car?cter y avanzar puntero
    }
}

void LCD_Clear(void) {
    LCD_Cmd(0x01);              // Comando para limpiar display
    __delay_ms(2);
}


void LCD_Goto(unsigned char row, unsigned char col) {
    unsigned char address;
    
    // Calcular direcci?n DDRAM seg?n fila
    if(row == 1)
        address = 0x80 + (col - 1);     // Primera fila: 0x80 - 0x8F
    else
        address = 0xC0 + (col - 1);     // Segunda fila: 0xC0 - 0xCF
    
    LCD_Cmd(address);                    // Enviar comando de posici?n
}
