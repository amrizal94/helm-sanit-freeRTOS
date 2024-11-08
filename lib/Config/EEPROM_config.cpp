#include <EEPROM_config.h>

uint8_t EEPROM_config::remainingTime = 0

EEPROM_config::EEPROM_config(){}

EEPROM_config::~EEPROM_config(){}

void EEPROM_config::loadSettings(){
    if (EEPROM.read(_MAGIC_MEM_ADDR) != _MAGIC_MEM_NUM)
    {
        EEPROM.write(1, remainingTime);
        EEPROM.write(_MAGIC_MEM_ADDR, _MAGIC_MEM_NUM);
        EEPROM.commit();
        Serial.println("EEPROM set!");
    }else{
        remainingTime = getMemInt(1) * 60;
        Serial.println("EEPROM get latest data!");
    }
    Serial.println("EEPROM setup success.");
}

void EEPROM_config::setMemInt(int addr, uint8_t newMemInt){
    EEPROM.write(addr, newMemInt);
    EEPROM.commit();
}

void EEPROM_config::getMemInt(int addr){
    return EEPROM.read(addr); 
}