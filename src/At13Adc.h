/*
    Controla el conversor analogico

    Datasheet:
        https://ww1.microchip.com/downloads/en/devicedoc/doc2535.pdf

    Permite leer una entrada:
        ADC0 (PB5), ADC1 (PB2), ADC2 (PB4) o ADC3 (PB3)

    Si el clock del sistema es de 9.6 MHz y el prescaler es de /8, el ADC correrá a 75 kHz.
    El prescaler se puede cambiar con: la tabla 14.4 página 93.

    ** Hay 2 versiones de funciones, para 8 o para 10 bits de resolucion **

    -Solo usa 60 bytes.

    Javier.
*/

#ifndef attiny13_adc_h
#define attiny13_adc_h

#include <Arduino.h>
#include <avr/io.h>

void adc_setup_10(uint8_t bit)
{
    // Para cambiar la Vref = Internal
    //ADMUX |= (1 << REFS0);

    // Set the ADC input
    switch (bit)
    {
    case PINB3:
        ADMUX |= (1 << MUX0);
    case PINB4:
        ADMUX |= (1 << MUX1);
        break;
    case PINB2:
        ADMUX |= (1 << MUX0);
    }
    // case PINB5: "00"

    // Set the prescaler to clock/128 & enable ADC
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

void adc_setup_8(uint8_t bit)
{
    ADMUX |= (1 << ADLAR); // left adjust result
    adc_setup_10(bit);
}

void start_adc_read()
{
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for it to finish
    while (ADCSRA & (1 << ADSC))
        ;
}

uint8_t adc_read_8()
{
    start_adc_read();
    return ADCH;
}

uint16_t adc_read_10()
{
    start_adc_read();
    return ADC;
}

#endif