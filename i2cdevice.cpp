#include <i2cdevice.h>

#include <stdio.h>
#include <stdlib.h>

I2CDevice::I2CDevice(uint8_t addr, const char *bus) {
    _fd = open(bus, O_RDWR);
    if (_fd < 0) {
        perror("open");
        abort();
    }
    if (ioctl(_fd, I2C_SLAVE, addr)) {
        perror("ioctl");
        abort();
    }
}

I2CDevice::~I2CDevice() {
    close(_fd);
}

ssize_t I2CDevice::write(const uint8_t *buf, size_t count) {
    return ::write(_fd, buf, count);
}

ssize_t I2CDevice::read(uint8_t *buf, size_t count) {
    return ::read(_fd, &buf, count);
}
