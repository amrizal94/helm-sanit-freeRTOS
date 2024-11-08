#if !defined(COIN_H)
#define COIN_H
#include <Arduino.h>
class Coin
{
private:
    const uint8_t _pin;
public:
    Coin(uint8_t pin);

    void begin();

    bool getSignal();
};

#endif // COIN_H
