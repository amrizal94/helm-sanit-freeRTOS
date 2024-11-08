#include <Display/DisplayTask.h>

DisplayTask::DisplayTask(TokenTask &tokenTask) : _tokenTask(tokenTask) {
    _queueHandle = xQueueCreate(5, sizeof(MessageType) + sizeof(char*)); // Queue untuk pesan
}

DisplayTask::~DisplayTask() {
    vQueueDelete(_queueHandle);
}

void DisplayTask::initDisplay() {
    _lcd.init();
    _lcd.backlight();
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print("Helm Sanitize");
}

void DisplayTask::startDisplayTask() {
    xTaskCreate(displayTaskFunc, "DisplayTask", 1024, this, 1, NULL);
}

void DisplayTask::sendMessage(MessageType type, const char* message) {
    struct {
        MessageType type;
        const char* message;
    } msg = {type, message};

    xQueueSend(_queueHandle, &msg, portMAX_DELAY); // Kirim pesan ke queue
}

void DisplayTask::displayTaskFunc(void *pvParameters) {
    DisplayTask *self = static_cast<DisplayTask *>(pvParameters);
    self->initDisplay();

    while (true) {
        // Buffer untuk pesan dari queue
        struct {
            MessageType type;
            const char* message;
        } msg;

        // Tunggu sampai ada pesan di queue
        if (xQueueReceive(self->_queueHandle, &msg, pdMS_TO_TICKS(100))) {
            switch (msg.type) {
                case UPDATE_TIME:
                    self->updateDisplay();
                    break;
                case SHOW_MESSAGE:
                    self->showMessage(msg.message);
                    break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Update tampilan setiap detik
    }
}

void DisplayTask::updateDisplay() {
    _lcd.setCursor(0, 1); // Baris kedua untuk waktu yang tersisa
    _lcd.print("Time: ");
    _lcd.print(_tokenTask.getRemainingTime());
    _lcd.print("s   "); // Menghapus karakter yang tersisa
}

void DisplayTask::showMessage(const char *message) {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(message);
    vTaskDelay(pdMS_TO_TICKS(2000)); // Tampilkan pesan selama 2 detik
    initDisplay(); // Kembali ke tampilan countdown
}
