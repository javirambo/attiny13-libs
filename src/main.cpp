#include "At13WS2812B.h"
#include "At13Servo.h"
#include <util/delay.h>

#define F_CPU 9600000
#define SERVO _BV(PINB3)
#define LED _BV(PINB2)
#define RELE _BV(PINB4)
#define BOTON _BV(PINB0)

uint8_t r = 0, g = 85, b = 170;
long ms = 0;
uint16_t grados = 0;

void setup()
{
  DDRB |= RELE;
  
 // DDRB &= ~BOTON; // Set pin as input
 // PORTB |= BOTON; // pull up
}

bool boton_pulsado()
{
  //el boton comparte el pin con el led rgb!
  DDRB &= ~BOTON; // Set pin as input
  PORTB |= BOTON; // Enable pullup resistors
  
  if (!(PINB & BOTON))
  {
    // si esta pulsado, espero que se suelte:
    while (!(PINB & BOTON))
      ;
    return true;
  }
  else
    return false;
}

void loop()
{
  // test de leds
  //ws2812b_set_color(LED, r++, g++, b++);
  //_delay_ms(40);

  // test de servo
  /* if (millis() - ms > 1000)
  {
    ms = millis();

    if (++r % 2 == 0)
      ws2812b_set_color(LED, 0, 0, 255);
    else
      ws2812b_set_color(LED, 0, 255, 0);

    servo_move(SERVO, grados);

    grados += 30;
    if (grados > 180)
      grados = 0;
  }*/

  if (boton_pulsado())
  {
    PORTB ^= RELE;
    _delay_ms(100);
  }
}
