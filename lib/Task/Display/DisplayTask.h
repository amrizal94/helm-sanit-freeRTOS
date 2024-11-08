#ifndef DISPLAYTASK_H
#define DISPLAYTASK_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Token/TokenTask.h>

class DisplayTask {
public:
    enum MessageType { UPDATE_TIME, SHOW_MESSAGE }; // Tipe pesan

    DisplayTask(TokenTask &tokenTask);
    ~DisplayTask();

    void initDisplay();           // Menginisialisasi LCD
    void startDisplayTask();      // Membuat task untuk pembaruan tampilan
    void sendMessage(MessageType type, const char* message = nullptr); // Mengirim pesan ke task display

private:
    TokenTask &_tokenTask;        // Referensi ke TokenTask
    LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 16, 2); // Sesuaikan alamat LCD jika perlu
    QueueHandle_t _queueHandle;   // Queue untuk pesan antar task

    static void displayTaskFunc(void *pvParameters); // Task pembaruan tampilan
    void updateDisplay();         // Memperbarui tampilan countdown
    void showMessage(const char *message); // Menampilkan pesan khusus di LCD
};

#endif // DISPLAYTASK_H
