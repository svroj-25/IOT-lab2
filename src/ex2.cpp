#include <Arduino.h>

#define LIGHT_PIN 33

void setup() {
    Serial.begin(115200);
    pinMode(LIGHT_PIN, INPUT);
}

void loop() {
    int samples[10];
    int minVal = 4096; // ESP32 ADC max is 4095 (12-bit)
    int maxVal = 0;
    long sum = 0;

    // Take 10 back-to-back samples with no delay between them
    for (int i = 0; i < 10; i++) {
        samples[i] = analogRead(LIGHT_PIN);
        if (samples[i] < minVal) {
            minVal = samples[i];
        }
        if (samples[i] > maxVal) {
            maxVal = samples[i];
        }
        sum += samples[i];
    }

    int avgVal = sum / 10;

    // Print statistics in exact format: min=120 max=340 avg=210
    Serial.printf("min=%d max=%d avg=%d\n", minVal, maxVal, avgVal);

    // Wait 1000 ms between readings
    delay(1000);
}
