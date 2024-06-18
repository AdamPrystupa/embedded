#include <avr/io.h>
#include <util/delay.h>

/*
// Blink na diodzie PB4
int main(void) {

  // Ustawienie PB4 jako wyjście
  DDRB |= (1 << DDB4);
  // DDRB = DDRB | (1 << DDB4);
  // 00010000

  while (1) {
    // włączenie diody
    PORTB |= (1 << PORTB4);
    _delay_ms(1000);
    // wyłączenie diody
    PORTB &= ~(1 << PORTB4);
  // 00010000
    // 11101111
    _delay_ms(2000);
  }

  return 0;
}
*/

// Wstęp do PWM
/*
int main(void) {
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);

  // Z datasheet PWM
  TCCR2A &= ~(1 << WGM22);
  TCCR2A |= (1 << WGM21) | (1 << WGM20); // Fast PWM
  // Clear OC2A on compare match, set OC2A at BOTTOM, (non-inverting mode).
  TCCR2A |= (1 << COM2A1);
  TCCR2A &= ~(1 << COM2A0);

  // Częstotliwość
  TCCR2B |= (1 << CS22); // Prescaler = 64
  TCCR2B &= ~((1 << CS21) | (1 << CS20));

  // Wartość Compare
  OCR2A = 10;

  while (1) {
    // Stary blink, PWM nie wymaga pracy procesora
    PORTB |= (1 << PORTB4);
    _delay_ms(1000);
    PORTB &= ~(1 << PORTB4);
    _delay_ms(1000);
  }

  return 0;
}
*/

/*
#include <avr/pgmspace.h>

const uint8_t sine_wave[256] PROGMEM = {
    128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171,
    174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211,
    213, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 239, 240,
    242, 243, 244, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254,
    254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 252, 251,
    250, 249, 248, 247, 246, 245, 244, 242, 241, 239, 238, 236, 235, 233, 231,
    229, 227, 225, 223, 221, 219, 217, 215, 212, 210, 207, 205, 202, 200, 197,
    195, 192, 189, 186, 184, 181, 178, 175, 172, 169, 166, 163, 160, 157, 154,
    151, 148, 145, 142, 138, 135, 132, 129, 126, 123, 120, 117, 113, 110, 107,
    104, 101, 98,  95,  92,  89,  86,  83,  80,  77,  74,  71,  69,  66,  63,
    60,  58,  55,  53,  50,  48,  45,  43,  40,  38,  36,  34,  32,  30,  28,
    26,  24,  22,  20,  19,  17,  16,  14,  13,  11,  10,  9,   8,   7,   6,
    5,   4,   3,   3,   2,   2,   1,   1,   0,   0,   0,   0,   0,   0,   0,
    1,   1,   1,   2,   2,   3,   4,   4,   5,   6,   7,   8,   9,   11,  12,
    13,  15,  16,  18,  20,  21,  23,  25,  27,  29,  31,  33,  35,  37,  39,
    42,  44,  46,  49,  51,  54,  56,  59,  62,  64,  67,  70,  73,  76,  79,
    81,  84,  87,  90,  93,  96,  99,  103, 106, 109, 112, 115, 118, 121, 124,
    127};

int main(void) {
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);

  // Z datasheet PWM
  TCCR2A &= ~(1 << WGM22);
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  TCCR2A |= (1 << COM2A1);
  TCCR2A &= ~(1 << COM2A0);

  // Częstotliwość
  TCCR2B |= (1 << CS22);
  TCCR2B &= ~((1 << CS21) | (1 << CS20));

  // Wartość Compare
  OCR2A = 0;

  uint8_t sine_index = 0;

  while (1) {
    // Stary blink, PWM nie wymaga pracy procesora
    PORTB |= (1 << PORTB4);
    _delay_ms(2);
    PORTB &= ~(1 << PORTB4);
    _delay_ms(2);

    OCR2A = pgm_read_byte(&sine_wave[sine_index]);
    sine_index++;
  }

  return 0;
}
*/
/*
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

const uint8_t sine_wave[256] PROGMEM = {
    128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171,
    174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211,
    213, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 239, 240,
    242, 243, 244, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254,
    254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 252, 251,
    250, 249, 248, 247, 246, 245, 244, 242, 241, 239, 238, 236, 235, 233, 231,
    229, 227, 225, 223, 221, 219, 217, 215, 212, 210, 207, 205, 202, 200, 197,
    195, 192, 189, 186, 184, 181, 178, 175, 172, 169, 166, 163, 160, 157, 154,
    151, 148, 145, 142, 138, 135, 132, 129, 126, 123, 120, 117, 113, 110, 107,
    104, 101, 98,  95,  92,  89,  86,  83,  80,  77,  74,  71,  69,  66,  63,
    60,  58,  55,  53,  50,  48,  45,  43,  40,  38,  36,  34,  32,  30,  28,
    26,  24,  22,  20,  19,  17,  16,  14,  13,  11,  10,  9,   8,   7,   6,
    5,   4,   3,   3,   2,   2,   1,   1,   0,   0,   0,   0,   0,   0,   0,
    1,   1,   1,   2,   2,   3,   4,   4,   5,   6,   7,   8,   9,   11,  12,
    13,  15,  16,  18,  20,  21,  23,  25,  27,  29,  31,  33,  35,  37,  39,
    42,  44,  46,  49,  51,  54,  56,  59,  62,  64,  67,  70,  73,  76,  79,
    81,  84,  87,  90,  93,  96,  99,  103, 106, 109, 112, 115, 118, 121, 124,
    127};

volatile uint8_t sine_index = 0;

ISR(TIMER1_COMPA_vect) {
  OCR2A = pgm_read_byte(&sine_wave[sine_index]);
  sine_index++;
}

int main(void) {
  // Wyłączenie Interruptów
  cli();

  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);

  TCCR2A &= ~(1 << WGM22);
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  TCCR2A |= (1 << COM2A1);
  TCCR2A &= ~(1 << COM2A0);

  TCCR2B |= (1 << CS22);
  TCCR2B &= ~((1 << CS21) | (1 << CS20));

  OCR2A = 0;

  // Drugi timer jako źródło interruptów
  TCCR1B |= (1 << WGM12);
  // Częstotliwość interruptów
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TCCR1B &= ~(1 << CS11);
  OCR1A = 255;

  // Włączenie interruptu timera
  TIMSK1 |= (1 << OCIE1A);

  // Włączenie Interruptów
  sei();

  while (1) {
    PORTB |= (1 << PORTB4);
    _delay_ms(1000);
    PORTB &= ~(1 << PORTB4);
    _delay_ms(1000);
  }

  return 0;
}
int main(void) {

  DDRB |= (1 << DDB4);

  DDRB &= ~(1 << DDD2);
  PORTB &= ~(1 << PORTD2);

  while (1) {
    // Odczytaj stan PB1 i ustaw go na PB4
    if (PIND & (1 << PIND2))
      PORTB |= (1 << PORTB4);
    else
      PORTB &= ~(1 << PORTB4);
  }

  return 0;
}
*/
/*
#include <avr/interrupt.h>

ISR(INT0_vect) {
  if (PIND & (1 << PIND2)) {
    PORTB |= (1 << PORTB4);
  } else {
    PORTB &= ~(1 << PORTB4);
  }
}

int main(void) {
  cli();

  DDRB |= (1 << DDB4);

  // PD2 jako input
  DDRD &= ~(1 << DDD2);
  PORTD &= (1 << PORTD2);

  // Konfiguracja logiti Interrupta
  EICRA &= ~(1 << ISC01);
  EICRA |= (1 << ISC00);
  // Włączenie interrupta
  EIMSK |= (1 << INT0);

  sei();

  while (1) {
  }

  return 0;
}
*/

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// Tablica sinusoidalna
const uint8_t sine_wave[256] PROGMEM = {
    128, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171,
    174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211,
    213, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 235, 237, 239, 240,
    242, 243, 244, 246, 247, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254,
    254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253, 252, 252, 251,
    250, 249, 248, 247, 246, 245, 244, 242, 241, 239, 238, 236, 235, 233, 231,
    229, 227, 225, 223, 221, 219, 217, 215, 212, 210, 207, 205, 202, 200, 197,
    195, 192, 189, 186, 184, 181, 178, 175, 172, 169, 166, 163, 160, 157, 154,
    151, 148, 145, 142, 138, 135, 132, 129, 126, 123, 120, 117, 113, 110, 107,
    104, 101, 98,  95,  92,  89,  86,  83,  80,  77,  74,  71,  69,  66,  63,
    60,  58,  55,  53,  50,  48,  45,  43,  40,  38,  36,  34,  32,  30,  28,
    26,  24,  22,  20,  19,  17,  16,  14,  13,  11,  10,  9,   8,   7,   6,
    5,   4,   3,   3,   2,   2,   1,   1,   0,   0,   0,   0,   0,   0,   0,
    1,   1,   1,   2,   2,   3,   4,   4,   5,   6,   7,   8,   9,   11,  12,
    13,  15,  16,  18,  20,  21,  23,  25,  27,  29,  31,  33,  35,  37,  39,
    42,  44,  46,  49,  51,  54,  56,  59,  62,  64,  67,  70,  73,  76,  79,
    81,  84,  87,  90,  93,  96,  99,  103, 106, 109, 112, 115, 118, 121, 124,
    127};

volatile uint8_t sine_index = 0;

// ISR dla przerwania zewnętrznego INT0
ISR(INT0_vect) {
  if (PIND & (1 << PIND2)) {
    PORTB |= (1 << PORTB4);
  } else {
    PORTB &= ~(1 << PORTB4);
  }
}

// ISR dla Timer1
ISR(TIMER1_COMPA_vect) {
  OCR2A = pgm_read_byte(&sine_wave[sine_index]);
  sine_index++;
}

int main(void) {
  // Wyłączenie przerwań
  cli();

  // Konfiguracja pinów jako wyjścia
  DDRB |= (1 << DDB3); // PB3 jako wyjście (PWM)
  DDRB |= (1 << DDB4); // PB4 jako wyjście (LED)

  // Konfiguracja PD2 jako wejście
  DDRD &= ~(1 << DDD2);
  PORTD &= ~(1 << PORTD2); // Wyłączenie podciągania na PD2

  // Konfiguracja przerwania zewnętrznego na INT0 (zmiana stanu)
  EICRA &= ~(1 << ISC01);
  EICRA |= (1 << ISC00);
  EIMSK |= (1 << INT0);

  // Konfiguracja Timer2 dla PWM
  TCCR2A &= ~(1 << WGM22);
  TCCR2A |= (1 << WGM21) | (1 << WGM20); // Fast PWM
  TCCR2A |= (1 << COM2A1);
  TCCR2A &= ~(1 << COM2A0);
  TCCR2B |= (1 << CS22); // Prescaler = 64
  TCCR2B &= ~((1 << CS21) | (1 << CS20));
  OCR2A = 0;

  // Konfiguracja Timer1 dla generowania przerwań
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler = 1024
  TCCR1B &= ~(1 << CS11);
  OCR1A = 255;
  TIMSK1 |= (1 << OCIE1A); // Włączenie przerwania Compare Match A

  // Włączenie przerwań
  sei();

  while (1) {

  }

  return 0;
}