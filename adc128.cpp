#include "adc128.h"
#include "adc128_registers.h"

ADC128::ADC128(uint8_t address) {
    addr = address;
}

void ADC128::begin() {
    // I2C Setup
    i2c_bus_init();

#ifdef __linux__
    while(reg_read(reg::busy) > 0) {
       sleep(1); 
    }
#endif // __linux__

    // reset defaults
    reset();
    // shutdown
    disableStart(true);
    // mode 1
    setMode1();
    // conversion rate -> continious
    enableContiniousConversion();
    // startup
    enableStart(true);
    // external vref
    enableExternalVref();
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


int ADC128::enableInterrupt(bool immediate) {
    config_data |= config::int_enable;
    if (immediate)
        return writeConfig();
    else
        return 0;
}


int ADC128::disableInterrupt(bool immediate) {
    config_data &= ~config::int_enable;
    if (immediate)
        return writeConfig();
    else
        return 0;
}


int ADC128::reset(bool immediate) {
    config_data |= config::restore_defaults;
    if (immediate)
        return writeConfig();
    else
        return 0;
}


int ADC128::enableContiniousConversion() {
    return reg_write(reg::conversion_rate, conversion_rate::continious);
}


int ADC128::disableContiniousConversion() {
    return reg_write(reg::conversion_rate, 0);
}


int ADC128::oneshot() {
    return reg_write(reg::oneshot, oneshot::enable);
}

int ADC128::setMode1(bool immediate) {
    adv_config_data |= adv_config::mode1;
    if (immediate)
        return writeAdvConfig();
    else
        return 0;
}

int ADC128::enableExternalVref(bool immediate) {
    adv_config_data |= adv_config::external_vref;
    if (immediate)
        return reg_write(reg::adv_config, adv_config_data);
    else
        return 0;
}

int ADC128::disableExternalVref(bool immediate) {
    adv_config_data &= ~adv_config::external_vref;
    if (immediate)
        return reg_write(reg::adv_config, adv_config_data);
    else
        return 0;
}

uint16_t ADC128::analogRead(uint8_t chan) {
    uint8_t channel_reg = reg::chan0 + chan;

#ifdef ARDUINO
    Wire.beginTransmission(addr);
    Wire.write(channel_reg);
    Wire.endTransmission();

    Wire.requestFrom(addr, 2);
    while (!Wire.available());

    uint8_t highbyte = Wire.read();
    uint8_t lowbyte = Wire.read() & 0xF0;

    return (highbyte << 4) | (lowbyte >> 4);
#else // Raspberry Pi
    uint8_t buf[2] = {channel_reg, 0};
    i2c->write(buf, 1);
    i2c->read(buf, 2);
    // return (buf[0] << 4) | (buf[1] >> 4); // TODO
    return (buf[0] << 4) | (buf[1] >> 4);
}
#endif

void ADC128::i2c_bus_init() {
#ifdef ARDUINO
    Wire.begin();
#else // Raspberry Pi
    i2c = std::unique_ptr<I2CDevice>(new I2CDevice(addr, "/dev/i2c-0"));
#endif
}

inline int ADC128::reg_write(uint8_t reg, uint8_t data) {
#ifdef ARDUINO
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(data);
    return Wire.endTransmission();
#else
    uint8_t buf[] = {reg, data};
    i2c->write(buf, 2);
#endif
}

inline uint8_t ADC128::reg_read(uint8_t reg) {
#ifdef ARDUINO
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(addr, 1);
    while (!Wire.available());
    return Wire.read();
#else
    uint8_t buf[] = {reg};
    i2c->write(buf, 1);
    i2c->read(buf, 1);
    return buf[0];
#endif
}

inline int ADC128::writeConfig() {
    return reg_write(reg::config, config_data);
}

inline int ADC128::writeAdvConfig() {
    return reg_write(reg::adv_config, adv_config_data);
}

