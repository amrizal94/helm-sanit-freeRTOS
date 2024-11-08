#include <Coin/CoinAcceptorTask.h>

CoinAcceptorTask::CoinAcceptorTask(TokenTask &tokenTask) 
    : _tokenTask(tokenTask) {
}

void CoinAcceptorTask::begin() {
    pinMode(_coinPin, INPUT_PULLUP); // Set pin sebagai input dengan pull-up
    xTaskCreate(
        runTask,            // Fungsi task
        "CoinAcceptorTask", // Nama task
        1024,               // Ukuran stack
        this,               // Parameter task (pointer ke objek ini)
        1,                  // Prioritas task
        NULL                // Handle task (tidak perlu disimpan)
    );
}

void CoinAcceptorTask::runTask(void *pvParameters) {
    CoinAcceptorTask *self = static_cast<CoinAcceptorTask *>(pvParameters);
    const int debounceDelay = 200; // Debounce delay 200 ms
    int lastState = HIGH; // Inisialisasi sebagai HIGH (tidak ada input)
    unsigned long lastDebounceTime = 0;

    for (;;) {
        int currentState = digitalRead(self->_coinPin);

        if (currentState == LOW && lastState == HIGH) {
            // Jika mendeteksi transisi dari HIGH ke LOW
            unsigned long currentTime = millis();
            if (currentTime - lastDebounceTime > debounceDelay) {
                // Jika melewati debounce, tambahkan waktu
                self->_tokenTask.addTime(self->_timePerCoin);
                Serial.println("Coin detected! Time added.");
                lastDebounceTime = currentTime;
            }
        }

        lastState = currentState;
        vTaskDelay(pdMS_TO_TICKS(50)); // Cek setiap 50 ms
    }
}
