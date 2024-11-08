#if !defined(DISPLAY_H)
#define DISPLAY_H
#include <Token/TokenTask.h>
class DisplayTask
{
private:
    const uint32_t _taskStackSize = 3072; // word -> 12288 Byte -> 12KB
    const UBaseType_t _taskPriority = 6;

    TokenTask _tokenTask;
    TaskHandle_t _taskHandle;
public:
    DisplayTask(TokenTask &tokenTask);
    ~DisplayTask();
};




#endif // DISPLAY_H
