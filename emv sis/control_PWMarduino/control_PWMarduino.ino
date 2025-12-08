 /*
 * Control de Motor DC con ATmega328 usando solo registros
 * - PWM para control de velocidad mediante potenciómetro
 * - Cambio de giro con 2 botones
 * 
 * Conexiones:
 * - Potenciómetro: Pin A0 (ADC0)
 * - Botón Giro Horario: Pin D2 (PD2)
 * - Botón Giro Antihorario: Pin D3 (PD3)
 * - Motor IN1 (dirección): Pin D4 (PD4)
 * - Motor IN2 (dirección): Pin D5 (PD5)
 * - Motor PWM (velocidad): Pin D6 (PD6) - OC0A
 */

// Variables globales
volatile uint16_t adcValue = 512;  // Valor inicial medio
volatile bool adcReady = false;

void setup() {
  // Configurar pines de dirección del motor como salidas (PD4 y PD5)
  DDRD |= (1 << PD4) | (1 << PD5);
  
  // Configurar pin PWM como salida (PD6 - OC0A)
  DDRD |= (1 << PD6);
  
  // Configurar botones como entradas (PD2 y PD3)
  DDRD &= ~((1 << PD2) | (1 << PD3));
  
  // Habilitar pull-ups internos para los botones
  PORTD |= (1 << PD2) | (1 << PD3);
  
  // Configurar ADC
  // Referencia AVCC, canal ADC0 (A0)
  ADMUX = (1 << REFS0);  // AVCC como referencia, canal ADC0
  
  // Habilitar ADC, habilitar interrupción, modo auto-trigger, prescaler 128
  // ADEN: habilita ADC
  // ADATE: habilita Auto Trigger (conversión continua)
  // ADIE: habilita interrupción de ADC
  // ADPS[2:0] = 111: prescaler 128 (16MHz/128 = 125kHz)
  ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADIE) | 
           (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  
  // Configurar modo Free Running para ADC (conversión continua)
  // ADTS[2:0] = 000 en ADCSRB = Free Running mode
  ADCSRB = 0;
  
  // Configurar Timer0 para PWM en modo Fast PWM
  // COM0A1:0 = 10 (Clear OC0A on Compare Match, set at BOTTOM - Non-inverting mode)
  // WGM02:0 = 011 (Fast PWM, TOP = 0xFF)
  TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  
  // Prescaler 64 (PWM frequency ~976 Hz con reloj de 16MHz)
  // CS02:0 = 011
  TCCR0B = (1 << CS01) | (1 << CS00);
  
  // Iniciar con duty cycle medio para prueba
  OCR0A = 128;
  
  // Configurar dirección inicial (horario)
  PORTD |= (1 << PD4);   // IN1 = HIGH
  PORTD &= ~(1 << PD5);  // IN2 = LOW
  
  // Habilitar interrupciones globales
  sei();
  
  // Iniciar primera conversión ADC (inicia el modo free-running)
  ADCSRA |= (1 << ADSC);
}

void loop() {
  // Leer botón de giro horario (PD2) - Activo en BAJO
  if (!(PIND & (1 << PD2))) {  // Botón presionado
    delay(50);  // Debounce
    if (!(PIND & (1 << PD2))) {
      // Giro horario
      PORTD |= (1 << PD4);   // IN1 = HIGH
      PORTD &= ~(1 << PD5);  // IN2 = LOW
      
      // Esperar a que se suelte el botón
      while (!(PIND & (1 << PD2)));
      delay(50);
    }
  }
  
  // Leer botón de giro antihorario (PD3) - Activo en BAJO
  if (!(PIND & (1 << PD3))) {  // Botón presionado
    delay(50);  // Debounce
    if (!(PIND & (1 << PD3))) {
      // Giro antihorario
      PORTD &= ~(1 << PD4);  // IN1 = LOW
      PORTD |= (1 << PD5);   // IN2 = HIGH
      
      // Esperar a que se suelte el botón
      while (!(PIND & (1 << PD3)));
      delay(50);
    }
  }
  
  // Actualizar PWM cuando hay nueva lectura ADC
  if (adcReady) {
    adcReady = false;
    
    // Convertir valor ADC (0-1023) a PWM (0-255)
    uint8_t pwmValue = adcValue >> 2;  // Dividir entre 4
    
    // Actualizar duty cycle del PWM
    OCR0A = pwmValue;
  }
  
  // Pequeño delay para estabilidad
  delay(10);
}

// Interrupción del ADC - se ejecuta automáticamente en modo free-running
ISR(ADC_vect) {
  // Leer valor del ADC (10 bits)
  adcValue = ADC;
  adcReady = true;
}
