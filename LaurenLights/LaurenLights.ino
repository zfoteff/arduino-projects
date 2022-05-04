#include <Adafruit_NeoPixel.h>
#define LED_COUNT   150
#define RED_PIN     12
#define WHITE_PIN   11
#define YELLOW_PIN  10
#define PINK_PIN    9
#define DIM_PIN     8
#define BRIGHT_PIN  7
#define POWER_PIN   6
#define LED_PIN     5


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int power, off, brightness;
uint32_t color = 0xE1A009;


void setup(){
  // put your setup code here, to run once:
  power = 0;
  off = 1;
  brightness = 45;
  color = 0xFCE5B0;
  
  pinMode(POWER_PIN, INPUT_PULLUP);
  pinMode(WHITE_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, INPUT_PULLUP);
  pinMode(YELLOW_PIN, INPUT_PULLUP);
  pinMode(PINK_PIN, INPUT_PULLUP);
  pinMode(DIM_PIN, INPUT_PULLUP);
  pinMode(BRIGHT_PIN, INPUT_PULLUP);
  
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}

void loop() {
  int powerState = digitalRead(POWER_PIN);
  int whiteState = digitalRead(WHITE_PIN);
  int redState = digitalRead(RED_PIN);
  int yellowState = digitalRead(YELLOW_PIN);
  int pinkState = digitalRead(PINK_PIN);
  int upBrightness = digitalRead(BRIGHT_PIN);
  int downBrightness = digitalRead(DIM_PIN);

  //  Power button pressed
  if (powerState == LOW) {
    //  System is off --> Turn system on
    if (!power && off) {
      bloom();
      power = 1;
      off = 0;
      return;
    }

    //  System is on --> Turn system off
    else {
     slideOut();
     strip.clear();
     power = 0;
     off = 1;    
   }
  }

  //  White light button pressed
  if (whiteState == LOW && power)
    colorShift(0);

  //  Red light button pressed
  else if (redState == LOW && power)
    colorShift(1);

    //  Red light button pressed
  else if (yellowState == LOW && power)
    colorShift(2);

    //  Red light button pressed
  else if (pinkState == LOW && power)
    colorShift(3);

  //  Increase brightness button pressed
  else if (upBrightness == LOW && power)
    increaseBrightness();

  //  Decrease brightness button pressed
  else if (downBrightness == LOW && power)
    decreaseBrightness();
}

void bloom()
{
 /*
  *   Animation function that activates elements in pairs
  *   starting from the middle of the strip and expanding
  *   outwards to both sides, effectively creating a 
  *   bloom of color
  */
  int lowMid = (LED_COUNT/2) - 1;
  int highMid = (LED_COUNT/2);
  
  delay(5);
  while (lowMid >= 0 && highMid <= LED_COUNT){
    strip.setPixelColor(lowMid, color);
    strip.setPixelColor(highMid, color);
    strip.show();
    lowMid -= 1;
    highMid += 1;
    delay(1);
  }
}

void slideIn()
{
  /*
  *   Animation function that activates elements in the strip 
  *   one by one starting on the left edge of the strip. This 
  *   effectively creates a sliding animation
  */
  delay(3);
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(2);
  }
}

void slideOut ()
{
 /*
  *   Animation function that deactivates elements in the strip 
  *   one by one starting on the right edge of the strip. This 
  *   effectively creates a sliding animation. Turns the strip 
  *   off at the conclusion of the animation 
  */
  if (strip.getPixelColor(0) == 0x000000)
    //  If the strip is off, don't run the function
    return;
  
  delay(3);
  for (int i = LED_COUNT - 1; i >= 0; i--) {
    strip.setPixelColor(i, 0,0,0);
    strip.show();
  }

  power = 0;
}

void increaseBrightness ()
{
 /*
  * Function increases the power to the strip to increase the brightness 
  */
  delay(1); 
  if (brightness >= 70)
    return;
  brightness += 1;
  strip.setBrightness(brightness);
  strip.show();
}

void decreaseBrightness ()
{
 /*
  * Function decreases the power to the strip to decrease the brightness 
  */
  delay(1);
  if (brightness <= 30)
    return;
  brightness -= 1;
  strip.setBrightness(brightness);
  strip.show();
}

void colorShift (int mode){
  /*  
   *   Function changes color of the light between two modes
   *   
   *     Modes:
   *   1. WHITE
   *   2. RED
   *   3. YELLOW
   *   4. PINK
  */

  switch (mode){
    //  mode = 0 --> White room lighting
    case 0:
      color = 0xFCE5B0;
      bloom();
      break;

    //  mode = 1 --> Red room lighting
    case 1:
      color = 0xFF1493;
      bloom();
      break;

    //  mode = 2 --> Yellow room lighting
    case 2:
      color = 0xFFCC00;
      bloom();
      break;

    //  mode = 3 --> Pink room lighting
    case 3:
      color = 0xFF3399;
      bloom();
      break;

    default:
      break;
  }
}
