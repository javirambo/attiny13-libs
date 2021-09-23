/*
    PWM control para ATtiny13, por ejemplo LED Brightness.

    Datasheet:
        https://ww1.microchip.com/downloads/en/devicedoc/doc2535.pdf

    OC0A and OC0B:
    This AVR microcontroller has two channels with 8-bit PWM capability
    PB0/OC0A (pin 5) and PB1/OC0B (pin 6)
    both running from Timer 0.

    ** Usar un juego de funciones _0 o _1 **

    -solo usa 68 bytes de Flash por canal.
    
    Javier.
*/

#ifndef attiny13_pwm_h
#define attiny13_pwm_h

#include <Arduino.h>
#include <avr/io.h>

void pwm_setup_0()
{
    DDRB |= 1; // bit 0 as an output

    // Set Timer 0 prescaler to clock/8.
    // At 9.6 MHz this is 1.2 MHz.
    // See ATtiny13 datasheet, Table 11.9.
    TCCR0B |= (1 << CS01);

    // Set to 'Fast PWM' mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);

    // Clear OC0A output on compare match, upwards counting.
    TCCR0A |= (1 << COM0A1);
}

void pwm_setup_1()
{
    DDRB |= 2; // bit 1 as an output

    // Set Timer 0 prescaler to clock/8.
    // At 9.6 MHz this is 1.2 MHz.
    // See ATtiny13 datasheet, Table 11.9.
    TCCR0B |= (1 << CS01);

    // Set to 'Fast PWM' mode
    TCCR0A |= (1 << WGM01) | (1 << WGM00);

    // Clear OC0B output on compare match, upwards counting.
    TCCR0A |= (1 << COM0B1);
}

void pwm_write_0(uint8_t val)
{
    OCR0A = val;
}

void pwm_write_1(uint8_t val)
{
    OCR0B = val;
}

#endif
