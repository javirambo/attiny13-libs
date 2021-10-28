/*
    Mueve un servo a una posición prefijada o en grados de 0 a 180.

    Datasheet:
        https://ww1.microchip.com/downloads/en/devicedoc/doc2535.pdf

    Dependiendo de cual funcion usar (o la clase) se pueden ahorrar bytes...

    Javier.
*/

#ifndef attiny13_servo_h
#define attiny13_servo_h
#include <Arduino.h>
#include <avr/io.h>
#include <util/delay.h>

// aprox. 13.84 grados = 14 posiciones
// (esta calibrado para el AtTiny13 y el micro-servo azul)
const int servo_positions[] = {600, 763, 926, 1089, 1252, 1415, 1578,
                               1741, 1904, 2067, 2230, 2393, 2556, 2730};

// posiciona el servo en una de las 14 posiciones
// Flash:214 bytes, Ram:30 bytes
void servo_move_table(uint8_t pin_data, uint8_t index)
{
    DDRB |= pin_data;
    volatile int z = servo_positions[index];
    for (uint8_t i = 0; i < 30; i++)
    {
        PORTB |= pin_data;
        delayMicroseconds(z);
        PORTB &= ~pin_data;
        _delay_ms(20);
    }
}

#define map(in, in_min, in_max, out_min, out_max) ((in - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

// posiciona el servo en grados de 0 a 180
// Flash:364 bytes, Ram:2 bytes
void servo_move(uint8_t pin_data, uint8_t grados)
{
    DDRB |= pin_data;
    volatile int z = map(grados, 0, 180, 600, 2730);
    for (uint8_t i = 0; i < 30; i++)
    {
        PORTB |= pin_data;
        delayMicroseconds(z);
        PORTB &= ~pin_data;
        _delay_ms(20);
    }
}

#endif
