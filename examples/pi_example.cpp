#include <wiringPi.h>
#include "adc128.h"

int main(int argc, char *argv[]) {
    wiringPiSetup();
    ADC128 adc(0x1D);
    adc.begin();

    while (true) {
        Serial.println(adc.analogRead(0), HEX);
        delay(500);
    }
}


