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

// aprox. 13.84 grados = 14 posiciones
// (esta calibrado para el AtTiny13 y el micro-servo azul)
const int servo_positions[] = {600, 763, 926, 1089, 1252, 1415, 1578,
                               1741, 1904, 2067, 2230, 2393, 2556, 2730};

void servo_setup(uint8_t pin)
{
    pinMode(pin, OUTPUT);
}

// posiciona el servo en una de las 14 posiciones
// Flash:214 bytes, Ram:30 bytes
void servo_move_table(uint8_t pin, uint8_t index)
{
    if (index < 0)
        index = 0;
    if (index > 13)
        index = 13;
    volatile int z = servo_positions[index];
    for (uint8_t i = 0; i < 30; i++)
    {
        digitalWrite(pin, HIGH);
        delayMicroseconds(z);
        digitalWrite(pin, LOW);
        delay(20);
    }
}

// posiciona el servo en grados de 0 a 180
// Flash:364 bytes, Ram:2 bytes
void servo_move(uint8_t pin, uint8_t grados)
{
    if (grados < 0)
        grados = 0;
    if (grados > 180)
        grados = 180;
    volatile int z = map(grados, 0, 180, 600, 2730);
    for (uint8_t i = 0; i < 30; i++)
    {
        digitalWrite(pin, HIGH);
        delayMicroseconds(z);
        digitalWrite(pin, LOW);
        delay(20);
    }
}

// Flash:594 bytes, Ram:32 bytes
class Servo
{
public:
    uint8_t _pin = -1;

    void setup(uint8_t pin)
    {
        _pin = pin;
        pinMode(_pin, OUTPUT);
    }

    // ** index va de 0 a 13 !! **
    void move_table(uint8_t index)
    {
        if (index < 0)
            index = 0;
        if (index > 13)
            index = 13;
        // (esta calibrado para el AtTiny13 y el micro-servo azul)
        volatile int z = servo_positions[index];
        for (uint8_t i = 0; i < 30; i++)
        {
            digitalWrite(_pin, HIGH);
            delayMicroseconds(z);
            digitalWrite(_pin, LOW);
            delay(20);
        }
    }

    void move(uint8_t grados)
    {
        if (grados < 0)
            grados = 0;
        if (grados > 180)
            grados = 180;
        volatile int z = map(grados, 0, 180, 600, 2730);
        for (uint8_t i = 0; i < 30; i++)
        {
            digitalWrite(_pin, HIGH);
            delayMicroseconds(z);
            digitalWrite(_pin, LOW);
            delay(20);
        }
    }
};

#endif
