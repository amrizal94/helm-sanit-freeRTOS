#include <Coin/Coin.h>
#include <Arduino.h>

Coin::Coin(uint8_t pin): _pin(pin)
{
}

void Coin::begin(){
    pinMode(_pin, INPUT);
}

bool Coin::getSignal(){
    return digitalRead(_pin);
}