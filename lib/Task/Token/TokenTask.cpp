#include <Token/TokenTask.h>


TokenTask::TokenTask(/* args */): _taskHandle(NULL)
{
}

TokenTask::~TokenTask()
{
}

void TokenTask::startTask() {
    if (_taskHandle == NULL) {
        xTaskCreate(runTask, "runTaskToken", _taskStackSize, this, _taskPriority, &_taskHandle);
    }
}

void TokenTask::runTask(void *pvParameters)
{
    TokenTask *self = static_cast<TokenTask *>(pvParameters);
    while (self->_remainingTime > 0)
    {
      _remainingTime--;
    }
}

void TokenTask::addTime(){
    _remainingTime += _timeIncrement;
}

void