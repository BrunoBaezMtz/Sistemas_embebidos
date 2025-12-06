
// Definiciones de pines de control LCD
#define RS_PIN 0  // PB0
#define E_PIN  1  // PB1

// Variables globales
volatile uint16_t adcValue = 0;
volatile bool adcReady = false;

void setup() {
  // Configurar puertos para LCD
  DDRD = 0xFF;  // PORTD como salida (datos LCD D0-D7)
  DDRB |= (1 << RS_PIN) | (1 << E_PIN);  // PB0 y PB1 como salida
  
  // Inicializar LCD
  delay(50);
  lcdInit();
  
  // Configurar ADC
  // ADMUX: Referencia AVCC, alineación derecha, canal ADC0
  ADMUX = (1 << REFS0);  // AVCC como referencia
  
  // ADCSRA: Habilitar ADC, interrupciones, prescaler 128 (16MHz/128 = 125kHz)
  ADCSRA = (1 << ADEN) |   // Habilitar ADC
           (1 << ADIE) |   // Habilitar interrupción
           (1 << ADPS2) |  // Prescaler 128
           (1 << ADPS1) | 
           (1 << ADPS0);
  
  // Habilitar interrupciones globales
  sei();
  
  // Iniciar primera conversión
  ADCSRA |= (1 << ADSC);
}

void loop() {
  if (adcReady) {
    adcReady = false;
    
    // Calcular voltaje en milivolts (Vref = 5000mV, ADC = 10 bits)
    uint32_t millivolts = ((uint32_t)adcValue * 5000UL) / 1023UL;
    
    // Limpiar LCD y mostrar datos
    lcdClear();
    
    // Primera línea: Valor RAW
    lcdSetCursor(0, 0);
    lcdPrint("RAW: ");
    lcdPrintNumber(adcValue);
    
    // Segunda línea: Voltaje en mV
    lcdSetCursor(0, 1);
    lcdPrint("mV: ");
    lcdPrintNumber(millivolts);
    
    // Pequeña pausa antes de siguiente conversión
    delay(200);
    
    // Iniciar nueva conversión
    ADCSRA |= (1 << ADSC);
  }
}

// ISR del ADC
ISR(ADC_vect) {
  adcValue = ADC;  // Leer valor (ADCL y ADCH)
  adcReady = true;
}

// ========== Funciones LCD ==========

void lcdPulseEnable() {
  PORTB |= (1 << E_PIN);   // E = 1
  delayMicroseconds(1);
  PORTB &= ~(1 << E_PIN);  // E = 0
  delayMicroseconds(50);
}

void lcdSendCommand(uint8_t cmd) {
  PORTB &= ~(1 << RS_PIN);  // RS = 0 (comando)
  PORTD = cmd;              // Enviar comando
  lcdPulseEnable();
  delayMicroseconds(2000);
}

void lcdSendData(uint8_t data) {
  PORTB |= (1 << RS_PIN);   // RS = 1 (dato)
  PORTD = data;             // Enviar dato
  lcdPulseEnable();
  delayMicroseconds(50);
}

void lcdInit() {
  // Secuencia de inicialización LCD 16x2 (8 bits)
  delay(15);
  lcdSendCommand(0x38);  // Function set: 8 bits, 2 líneas, 5x8
  delay(5);
  lcdSendCommand(0x38);
  delay(1);
  lcdSendCommand(0x38);
  
  lcdSendCommand(0x0C);  // Display ON, cursor OFF
  lcdSendCommand(0x01);  // Clear display
  delay(2);
  lcdSendCommand(0x06);  // Entry mode: incrementar, no shift
}

void lcdClear() {
  lcdSendCommand(0x01);
  delay(2);
}

void lcdSetCursor(uint8_t col, uint8_t row) {
  uint8_t address = (row == 0) ? 0x00 : 0x40;
  address += col;
  lcdSendCommand(0x80 | address);
}

void lcdPrint(const char* str) {
  while (*str) {
    lcdSendData(*str++);
  }
}

void lcdPrintNumber(uint32_t num) {
  char buffer[11];
  ultoa(num, buffer, 10);
  lcdPrint(buffer);
}
