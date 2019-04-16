#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <wiringPi.h>
#include "adc128.h"

double calculate_temperature(uint16_t adc_reading);

int main(int argc, char *argv[]) {
    usleep(100000); // wait more than 33ms on poweron
    ADC128 adc(0x1D);

    while(adc.is_busy())
        usleep(100000);

    adc.begin();

    while (true) {
        for (uint8_t chan = 0; chan < 8; chan++) {
            uint16_t val = adc.analogRead(chan);
            printf("%6f ", calculate_temperature(val) - 273.15);
        }
        printf("\n");
        delay(500);
    }
}

double calculate_temperature(uint16_t adc_reading) {
    const double t25 = 298.15; // kelvin
    const double b25 = 3435;   // units kelvin but just so the units all match
    const double r25 = 10e3;   // nominal thermistor resistance
    const double r1  = 18e3;   // resistor divider resistance

    // fraction of VCC
    double v_frac = ((double) adc_reading) / ((double) 0xFFF);
    // thermistor resistance
    double rth = r1 * v_frac/(1-v_frac);
    // temperature from emperical formula
    double tmp = 1/t25 + log(rth/r25)/b25;
    double temperature = 1/tmp;
    return temperature;
}

