#include <stdio.h>
#include <wiringPi.h>
#include "adc128.h"

int main(int argc, char *argv[]) {
    wiringPiSetup();
    ADC128 adc(0x1D);
    adc.begin();

    while (true) {
        uint16_t val = adc.analogRead(0);
        printf("%x\n", val);
        delay(500);
    }
}


