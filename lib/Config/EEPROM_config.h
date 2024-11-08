#if !defined(EEPROMCONFIG_H)
#define EEPROMCONFIG_H

#include <EEPROM.h>

class EEPROM_config
{
private:
    /* data */
public:
    EEPROM_config(/* args */);
    ~EEPROM_config();

    static const uint8_t _MAGIC_MEM_NUM = 0xA5;
    static const uint8_t _MAGIC_MEM_ADDR = 0;

    static void loadSettings();
    static void setMemInt(int addr, uint8_t newMemInt);
    static uint8_t getMemInt(int addr);

    static uint16_t remainingTime;
};



#endif // EEPROMCONFIG_H
