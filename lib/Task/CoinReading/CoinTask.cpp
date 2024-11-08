#include <CoinReading/CoinTask.h>

CoinTask::CoinTask(Coin &coin): _coin(coin), _taskHandle(NULL)
{
}

CoinTask::~CoinTask()
{
}

void CoinTask::startTask() {
    if (_taskHandle != NULL)
    {
        // xTaskCreate()
    }
    
}

void CoinTask::coinAcceptorTask(void *_parameters){
    CoinTask *self = static_cast<CoinTask *>(_parameters);
    bool oldValue;
    while (true)
    {
        bool coinSignal = self->_coin.getSignal();
        if (coinSignal != oldValue )
        {
            if (coinSignal == LOW)
            {
                // Tambah waktu 5 menit setiap koin masuk
            }
            
        }
        
    }
    
}