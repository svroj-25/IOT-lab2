#include <Arduino.h>

#define RED_PIN    26
#define GREEN_PIN  27
#define YELLOW_PIN 12
#define BLUE_PIN   14

struct ChaseStep {
    uint8_t pin;
    const char* name;
};

const ChaseStep CHASE_SEQUENCE[] = {
    {RED_PIN,    "RED"},
    {GREEN_PIN,  "GREEN"},
    {YELLOW_PIN, "YELLOW"},
    {BLUE_PIN,   "BLUE"},
    {YELLOW_PIN, "YELLOW"},
    {GREEN_PIN,  "GREEN"}
};

const uint8_t TOTAL_STEPS = sizeof(CHASE_SEQUENCE) / sizeof(CHASE_SEQUENCE[0]);
const uint8_t ALL_LEDS[] = {RED_PIN, GREEN_PIN, YELLOW_PIN, BLUE_PIN};

int currentStep = 0;

void setup() {
    Serial.begin(115200);

    for (uint8_t pin : ALL_LEDS) {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
}

void loop() {
    // Turn on the current LED and turn off all other LEDs
    for (uint8_t pin : ALL_LEDS) {
        if (pin == CHASE_SEQUENCE[currentStep].pin) {
            digitalWrite(pin, HIGH);
        } else {
            digitalWrite(pin, LOW);
        }
    }

    // Print the name of the LED that just turned on
    Serial.print("chase=");
    Serial.println(CHASE_SEQUENCE[currentStep].name);

    // Advance to next step
    currentStep = (currentStep + 1) % TOTAL_STEPS;

    // Single delay per loop iteration as required
    delay(150);
}
