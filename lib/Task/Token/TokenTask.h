#if !defined(TOKENTASK_H)
#define TOKENTASK_H
#include <LiquidCrystal_I2C.h>

class TokenTask
{
private:
    static void runTask(void *pvParameters);
    const uint32_t _taskStackSize = 4096;
    const UBaseType_t _taskPriority = 5;
    TaskHandle_t _taskHandle;

    const uint16_t _timeIncrement = 5 * 60;
    uint16_t _remainingTime;
public:
    TokenTask(/* args */);
    ~TokenTask();

    void startTask();
    void stopTask();
    void addTime();
    uint16_t getRemainingTime();
};

#endif // TOKENTASK_H
