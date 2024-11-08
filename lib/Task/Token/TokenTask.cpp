#include <Token/TokenTask.h>
#include <Display/DisplayTask.h>  // Tambahkan ini untuk akses ke DisplayTask

TokenTask::TokenTask(int initialTime)
    : _remainingTime(initialTime), _timerHandle(NULL), _displayTask(nullptr)
{
}

TokenTask::~TokenTask() {
    if (_timerHandle != NULL) {
        xTimerDelete(_timerHandle, 0); // Hapus timer saat objek dihancurkan
    }
}

void TokenTask::startTask() {
    if (_timerHandle == NULL) {
        _timerHandle = xTimerCreate(
            "CountdownTimer",
            pdMS_TO_TICKS(1000), // Interval 1 detik
            pdTRUE,              // Timer berulang
            this,                // ID timer adalah pointer ke objek ini
            runTask              // Callback yang dipanggil
        );

        if (_timerHandle != NULL) {
            xTimerStart(_timerHandle, 0); // Mulai timer
            Serial.println("Countdown timer started.");
        }
    }
}

void TokenTask::stopTask() {
    if (_timerHandle != NULL) {
        xTimerStop(_timerHandle, 0); // Hentikan timer
        Serial.println("Countdown completed!");

        // Kirim pesan ke DisplayTask untuk menampilkan pesan "Masukkan Koin"
        if (_displayTask != nullptr) {
            _displayTask->sendMessage(DisplayTask::SHOW_MESSAGE, "Masukkan Koin");
        }
    }
}

void TokenTask::runTask(TimerHandle_t xTimer) {
    TokenTask *self = static_cast<TokenTask *>(pvTimerGetTimerID(xTimer));

    if (self->_remainingTime > 0) {
        self->_remainingTime--;

        Serial.print("Countdown: ");
        Serial.println(self->_remainingTime);

        // Jika DisplayTask di-set, kirim pesan UPDATE_TIME untuk memperbarui tampilan
        if (self->_displayTask != nullptr) {
            self->_displayTask->sendMessage(DisplayTask::UPDATE_TIME);
        }

        // Jika countdown selesai, hentikan timer
        if (self->_remainingTime == 0) {
            self->stopTask();
        }
    }
}

void TokenTask::addTime(int timeToAdd) {
    _remainingTime += timeToAdd;
    Serial.print("Time added, new countdown: ");
    Serial.println(_remainingTime);

    // Kirim pesan ke DisplayTask untuk memperbarui tampilan waktu yang tersisa
    if (_displayTask != nullptr) {
        _displayTask->sendMessage(DisplayTask::UPDATE_TIME);
    }
}

uint16_t TokenTask::getRemainingTime() {
    return _remainingTime;
}

void TokenTask::setDisplayTask(DisplayTask* display) {
    _displayTask = display;
}
