#include "adc128.h"

ADC128 adc(0x1D);

void setup() {
    Serial.begin(9600);
    adc.begin();
}

void loop() {
    Serial.println(adc.analogRead(0), HEX);
    delay(500);
}
