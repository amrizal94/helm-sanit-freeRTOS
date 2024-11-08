#ifndef COINACCEPTORTASK_H
#define COINACCEPTORTASK_H

#include <Arduino.h>
#include <Token/TokenTask.h>

class CoinAcceptorTask {
public:
    CoinAcceptorTask(TokenTask &tokenTask);
    void begin(); // Memulai task coin acceptor

private:
    static void runTask(void *pvParameters);
    TokenTask &_tokenTask;
    const uint8_t _coinPin = 19; // Pin untuk coin acceptor
    const int _timePerCoin = 5 * 60; // Waktu yang ditambahkan per coin (5 menit)
};

#endif // COINACCEPTORTASK_H