#include <Arduino.h>

#define BUTTON_PIN 25
#define RED_PIN    26
#define GREEN_PIN  27
#define YELLOW_PIN 12
#define BLUE_PIN   14

int count = 0;
int lastButtonState = LOW;

void updateLEDs(int c) {
    digitalWrite(RED_PIN,    (c >= 1) ? HIGH : LOW);
    digitalWrite(GREEN_PIN,  (c >= 2) ? HIGH : LOW);
    digitalWrite(YELLOW_PIN, (c >= 3) ? HIGH : LOW);
    digitalWrite(BLUE_PIN,   (c >= 4) ? HIGH : LOW);
}

void setup() {
    Serial.begin(115200);

    pinMode(BUTTON_PIN, INPUT);
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    updateLEDs(count);
}

void loop() {
    int buttonState = digitalRead(BUTTON_PIN);

    // Edge detection: act only on rising edge (transition from LOW to HIGH)
    if (buttonState == HIGH && lastButtonState == LOW) {
        count = (count + 1) % 5;
        updateLEDs(count);
        Serial.print("count=");
        Serial.println(count);
        delay(50); // Debounce delay
    }

    lastButtonState = buttonState;
    delay(10);
}
