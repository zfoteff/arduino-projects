#include <Adafruit_NeoPixel.h>
#define LED_COUNT   24

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int power, brightness;
uint32_t color = 0x000000;

struct Node {
    
}

void setup()
{
    power = 0;
    brightness = 75;
    color = color = 0xFCE5B0;
    strip.begin();
    string.setBrightness(brightness);
    string.show();
}

void loop()
{

}