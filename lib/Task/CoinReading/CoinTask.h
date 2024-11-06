#if !defined(COINTASK_H)
#define COINTASK_H

#include <Arduino.h>
#include <Coin/Coin.h>

class CoinTask
{
private:
    const uint32_t _taskStackSize = 4096;
    const UBaseType_t _taskPriority = 5;

    Coin &_coin;
    static void coinAcceptorTask(void *_parameters);
    TaskHandle_t _taskHandle;
public:
    CoinTask(Coin &coin);
    ~CoinTask();

    void startTask();
    void stopTask();
    TaskHandle_t getTaskHandle();
};
#endif // COINTASK_H
