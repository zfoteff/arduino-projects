#include <Adafruit_NeoPixel.h>
#define LED_COUNT           20
#define LED_PIN             6
#define POWER_PIN           2
#define BRIGHTNESS_UP_PIN   3
#define BRIGHTNESS_DOWN_PIN 4
#define MAX_BRIGHTNESS      200
#define MIN_BRIGHTNESS      50

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int brightness;
bool POWERED;
uint32_t color = 0xE1A009;

void allOn() {
    strip.fill(color, 0, LED_COUNT - 1);
    strip.show();
}

void allOff() {
    strip.fill(strip.Color(0,0,0), 0, LED_COUNT - 1);
    strip.show();
}

/** 
 * Private Methods 
 */
void flickerIn() {
    /**
     * Flicker the lights into the on state. Simulating an actual neon sign
     */

    delay(5);
}

void flickerOut() {
    /**
     * Flicker the lights into the off state. Simulating an actual neon sign
     */

    delay(5);
}

void increaseBrightness() {
    delay(1);
    brightness += 1;

    if (brightness > MAX_BRIGHTNESS)
        brightness = MAX_BRIGHTNESS;

    strip.setBrightness(brightness);
    strip.show();
}

void decreaseBrightness() {
    delay(1);
    brightness -= 1;

    if (brightness < MIN_BRIGHTNESS)
        brightness = MIN_BRIGHTNESS;

    string.setBrightness(brightness);
    strip.show();
}


/**
 * Arduino Methods
 */

void setup() {
    brightness = 75;
    POWERED = false;

    pinMode(POWER_PIN, INPUT_PULLUP);
    pinMode(BRIGHTNESS_UP_PIN, INPUT_PULLUP);
    pinMode(BRIGHTNESS_DOWN_PIN, INPUT_PULLUP);

    strip.begin();
    strip.setBrightness(brightness);
    strip.show();
}

void loop() {
    int powerState = digitalRead(POWER_PIN);
    int upBrightnessState = digitalRead(BRIGHTNESS_UP_PIN);
    int downBrightnessState = digitalRead(BRIGHTNESS_DOWN_PIN);

    //  Power button pushed
    if (powerState == LOW) {
        if (!POWERED) {
            // System is off --> Turn system on
            POWERED = true;
            flickerIn();
            return;
        } else {
            // System is on --> Turn system off
            POWERED = false;
            flickerOut();
            strip.clear();
            return;
        }
    }

    if (upBrightnessState == LOW && POWERED)
        increaseBrightness();
    
    if (downBrightnessState == LOW && POWERED)
        decreaseBrightness();
}