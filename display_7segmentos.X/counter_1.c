
#define _XTAL_FREQ 20000000  // Frecuencia del cristal (ajústala a tu caso real)
#include <xc.h>

//Array con los codigos de 7 segmentos para los numeros 0 a 9
unsigned char NUMBERS[10] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x07, //7
    0x7F, //8
    0x6F  //9
    
};

void main(void) {
    TRISA = 0x01;   // RA0 como entrada
    TRISB = 0x00;   // Puerto B como salida
    PORTB = NUMBERS[0];   // Mostrar "0" inicialmente usando array
    
    unsigned char counter = 0; // Se inicializa aqui
    
    while(1) {
        //1. deteccion de pulsacion
        if(PORTAbits.RA0 == 1){
            /*2. antirrebote inicial
             * retardo de 50ms
            */
            __delay_ms(50);
            
            //3.verificar que el boton sigue presionado despues del antirebote
            if(PORTAbits.RA0 == 1){
                //logica de conteo:
                counter++;
                if(counter >= 10){
                    counter = 0;
                }
                
                //4. actualizar el display
                //el valor de 'counter' se usa como indice para el array NUMBERS
                PORTB = NUMBERS[counter];
                
                //5. esperar a que se suelte el boton
                //aqui se asegura que solo s cuente una vez
                while(PORTAbits.RA0 == 1);
            }
        }
    }
}
