#include "At13WS2812B.h"
#include <inttypes.h>
#include <stdbool.h>

#define F_CPU 9600000
#define WS2812_PIN PINB3

uint8_t r = 0, g = 85, b = 170;

void setup() {}

void loop()
{
  ws2812b_set_color(_BV(WS2812_PIN), r, g, b);

  r++;
  g++;
  b++;

  _delay_ms(10);
}
