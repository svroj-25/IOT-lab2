#include <Arduino.h>

#define LIGHT_PIN 33

bool alertActive = false;

void setup() {
    Serial.begin(115200);
    pinMode(LIGHT_PIN, INPUT);
}

void loop() {
    int val = analogRead(LIGHT_PIN);

    // Hysteresis logic
    if (!alertActive && val > 3000) {
        alertActive = true;
        Serial.println("ALERT=1");
    } else if (alertActive && val < 2500) {
        alertActive = false;
        Serial.println("ALERT=0");
    }

    // Read every 300 ms
    delay(300);
}
