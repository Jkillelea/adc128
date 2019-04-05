#pragma once

#include <stdint.h>
#include "adc128_registers.h"

#ifdef ARDUINO
#include <Arduino.h>
#include <Wire.h>
#endif // ARDUINO

#ifdef __linux__
#include <i2cdevice.h>
#include <memory>
#endif // __linux__


class ADC128 {
public:
    ADC128(uint8_t address);

    void begin();

    int enableStart(bool immediate = true);
    int disableStart(bool immediate = true);

    int enableInterrupts(bool immediate = true);
    int disableInterrupts(bool immediate = true);
    int clearInterruptPin(bool immediate = true);
    int enableInterruptPin(bool immediate = true);

    int reset(bool immediate = true);
    bool is_busy();

    int enableContiniousConversion();
    int disableContiniousConversion();

    int oneshot();
    int setMode1(bool immediate = true);

    int enableExternalVref(bool immediate = true);
    int disableExternalVref(bool immediate = true);

    uint16_t analogRead(uint8_t chan);

private:
    uint8_t addr = 0x00;

    void i2c_bus_init();
    int reg_write(uint8_t reg, uint8_t data);
    uint8_t reg_read(uint8_t reg);
    int writeConfig();
    int writeAdvConfig();

    // configuration register defaults
    uint8_t config_data =  config::start 
                         | config::int_clear 
                         | config::restore_defaults;

    uint8_t adv_config_data = adv_config::external_vref
                            | adv_config::mode_bit0;

#ifdef __linux__
    std::unique_ptr<I2CDevice> i2c; // Linux i2c backend
#endif // __linux__
};
