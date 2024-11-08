#ifndef TOKENTASK_H
#define TOKENTASK_H

#include <Arduino.h>

class DisplayTask; // Forward declaration

class TokenTask {
public:
    TokenTask(int initialTime = 0);
    ~TokenTask();

    void startTask();              // Memulai countdown timer
    void stopTask();               // Menghentikan countdown timer
    void addTime(int timeToAdd);   // Menambahkan waktu ke countdown
    uint16_t getRemainingTime();   // Mendapatkan waktu yang tersisa

    void setDisplayTask(DisplayTask* display); // Set DisplayTask untuk komunikasi

private:
    static void runTask(TimerHandle_t xTimer); // Callback untuk countdown

    TimerHandle_t _timerHandle;
    uint16_t _remainingTime;
    DisplayTask* _displayTask;     // Pointer ke DisplayTask untuk menampilkan pesan
};

#endif // TOKENTASK_H
