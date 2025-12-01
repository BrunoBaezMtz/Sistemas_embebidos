# BRUNO EDUARDO BAEZ MARTINEZ 

## pregunta 1
un sistema embebido sirve para controlar tareas especificas las cuales no necesitan una gran capacidad de almacenamiento o de procesamiento, normalmente se utilizan en la industria para cotrlar cosas simples

## pregunta 4
un convertidor analogico-digital, como su nombre lo indica, nos ayuda a convertir senals analogicas en digitales, lo cual nos sirve en un sistema de control ya que podemos tener entradas analogicas las cuales pueden ser un potenciometro y tener salidas digitales como pueden ser motores de corriente directa, led, etc. gracias a las salidas digitales tenemos una onda cuadratica lo cual hace que el control sea mas estable

## pregunta 5
El registro TRIS nos sirve para declarar pines como entradas o salidas, configuramos 1 cuando queremos que sea salida y 0 cuando queremos que sea entrada.

## pregunta 7
/* 
 * File:   PREGUNTA_7.c
 * Author: BZ
 *
 * Created on 1 de diciembre de 2025, 07:51 AM
 */

#define _XTAL_FREQ 20000000
#include <stdio.h>
#include <xc.h>


/*
 * 
 */
void main(void){
    TRISB = 0b00000010;
    
    while(1){
        if (PORTBbits.RB1 == 1){
            PORTBbits.RB0 = 1;
        }
        else {
            PORTBbits.RB0 = 0;
        }
    }
}

## pregunta 9
elegiria un embebido de gama baja ya que si solo tenemos que controlar un ventilador con un termometro se puede emplear un driver para controlar el ventilador.

## pregunta de rescate A
ATmega328p
ESP32

## pregunta de rescate B
una entrada digital solo lee senales digitales como sensores

## pregunta de rescate C
TRIS sirve para configurar los pines como entradas y salidad y el PORT sirve para mandar senales o recivir senales

## pregunta de rescate D
es el ciclo de trabajo de un microcontrolador, nos sirve para saber que tan rapido hace el porceso y poder elegir el oscilador correcto

## pregunta de rescate E
sirve para rectificar la senal de entrada analogica

## pregunta de rescate F
__XTAL_FREQ sirve para confirgurar la velocidad, si o escribimos como _XTAL_FREQ no se configura correctamente la frecuencia

## pregunta de rescate G
no pasa nada, siempre y cuando tengan vcc y gnd no importa donde

## pregunta de rescate H
PORTCbits.RC0 == 0;