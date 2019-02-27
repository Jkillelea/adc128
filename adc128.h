#include <Arduino.h>
#include <Wire.h>

#include <stdint.h>

#include "adc128_registers.h"

class ADC128 {
public:
    ADC128(uint8_t address);

    void begin();

    int enableStart(bool immediate = true);
    int disableStart(bool immediate = true);

    int enableInterrupt(bool immediate = true);
    int disableInterrupt(bool immediate = true);

    int reset(bool immediate = true);

    int enableContiniousConversion(bool immediate = true);
    int disableContiniousConversion(bool immediate = true);

private:
    int reg_write(uint8_t reg, uint8_t data);
    int writeConfig();

    uint8_t addr = 0x00;
    uint8_t config_data =  config::start 
                         | config::int_clear 
                         | config::restore_defaults; // configuration register defaults
}
