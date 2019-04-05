#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include "adc128.h"

int main(int argc, char *argv[]) {
    usleep(100000); // wait more than 33ms on poweron
    ADC128 adc(0x1D);
    adc.begin();

    // while (adc.is_busy()) {
    //     usleep(100000);
    // }

    while (true) {
        for (int chan = 0; chan < 8; chan++) {
            uint16_t val = adc.analogRead(chan);
            printf("%6x ", val);
        }
        printf("\n");
        delay(500);
    }
}


