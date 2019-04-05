#include <stdint.h>
#include <linux/i2c-dev.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

class I2CDevice {
public:
    I2CDevice(uint8_t addr, const char *bus = "/dev/i2c-1");
    ~I2CDevice();
    ssize_t write(const uint8_t *buf, size_t count);
    ssize_t read(uint8_t *buf, size_t count);

private:
    int _fd;
};
