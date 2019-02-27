#include "adc128_registers.h"

ADC128::ADC128(uint8_t address) {
    addr = address;
}

void ADC128::begin() {
    // I2C Setup
    Wire.begin();

    // reset defaults
    // shutdown
    disableStart(false);

    // conversion rate -> continious
    // startup
    reg_write(reg::config, 0b00000001);
    // external vref
    // mode 1
}


int ADC128::enableStart(bool immediate) {
    config_data |= config::start;
    if (immediate)
        return writeConfig();
    else
        return 0;
}


int ADC128::disableStart(bool immediate) {
    config_data &= ~config::start;
    if (immediate)
        return writeConfig();
    else
        return 0;
}

int enableInterrupt(bool immediate) {
    config_data |= config::int_enable;
    if (immediate)
        return writeConfig();
    else
        return 0;
}

int disableInterrupt(bool immediate) {
    config_data &= ~config::int_enable;
    if (immediate)
        return writeConfig();
    else
        return 0;
}

int reset(bool immediate) {
    config_data |= config::restore_defaults;
    if (immediate)
        return writeConfig();
    else
        return 0;
}

int enableContiniousConversion(bool immediate) {
    reg_write(reg::conversion_rate, conversion_rate::continious);
}

int disableContiniousConversion(bool immediate) {
    reg_write(reg::conversion_rate, 0);
}

inline int ADC128::reg_write(uint8_t reg, uint8_t data) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission();
}


inline int ADC128::writeConfig() {
    return reg_write(reg::config, config_data);
}

// inline void bit_set(uint8_t *data, uint8_t bit) {
//     *data |= bit;
// }
// inline void bit_unset(uint8_t *data, uint8_t bit) {
//     *data &= ~bit;
// }

