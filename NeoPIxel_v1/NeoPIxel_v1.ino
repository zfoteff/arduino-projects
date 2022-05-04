#include <Adafruit_NeoPixel.h>
#include "LinkedList.h"
#define LED_COUNT   448
#define SEG1_RE    137
#define SEG2_RE    300
#define POWER_PIN   2
#define LEFT_PIN    11
#define CENTER_PIN  10
#define RIGHT_PIN   9
#define LED_PIN     6
#define WHITE_PIN   8
#define RED_PIN     7
#define UP_PIN      4
#define DOWN_PIN    3


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
int power, brightness;
bool rightSeg, leftSeg, centSeg;
uint32_t color = 0xE1A009;

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
    delay(0.25);
  }
}

void closeOut()
{
  /*
   *  Animation funtion that deactivates elements in pairs starting
   *  from the edges of the screen, in opposition to the bloom function
   */
  delay(5);
   
  int startCount = 0;
  int endCount = LED_COUNT-1;

  while (startCount <= (LED_COUNT/2)-1 && endCount >= LED_COUNT/2){
    strip.setPixelColor(startCount, 0,0,0);
    strip.setPixelColor(endCount, 0,0,0);
    strip.show();
    startCount += 1;
    endCount -= 1;
    delay(0.25);
  }
}


/* Depreciated */
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


/* Depreciated */
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

void everyThird()
{
  /*
   *  Turns off every third LED to increase power in other LED's
   */
   for (int i=0; i<LED_COUNT-1; i++) {
    if (i % 4 == 0)
      strip.setPixelColor(i, 0,0,0);
   }
}

void everyLED()
{
  for (int i=0; i<LED_COUNT-1; i++) {
    strip.setPixelColor(i, color);
  }
}

void increaseBrightness ()
{
 /*
  * Function increases the power to the strip to increase the brightness 
  */
  delay(1); 
  if (brightness > 140)
    brightness = 141;

  //  Turn off every third LED if brightness is in the 70 -> 140 range
  if (brightness >= 70 && brightness <= 140)
    everyThird();
 
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
    brightness = 31;

  //  Turn on every LED if it is in the 30 -> 70 brightness range
  if (brightness > 30 && brightness < 70)
    everyLED();
    
  brightness -= 1;
  strip.setBrightness(brightness);
  strip.show();
}

void toggleSegment(int seg)
{
  /*
   * Function toggles segments of strip on and off
   *  Segments:
   *  0: Left wall
   *  1: Center wall
   *  2: Right wall
   */
   switch (seg)
   {
     // Turn off left segment
     case 0:
       if (leftSeg){
        //  If left segment is on --> turn it off and set leftSeg = false
        strip.fill(strip.Color(0,0,0), 0, SEG1_RE);
        leftSeg = false;
       } else {
        //  If left sement if off --> turn it on and set leftSeg = True
        strip.fill(color, 0, SEG1_RE);
        leftSeg = true;
       }
         
       strip.show();
       delay(5);
       break;

     // Turn off middle segment
     case 1:
       if (centSeg) {
        //  If center segment is on --> turn it off and set centSeg = false
        strip.fill(strip.Color(0,0,0), SEG1_RE, 185);
        centSeg = false;
       } else {
        //  If center segment is off --> turn it on and set centSeg = true
        strip.fill(color, SEG1_RE, 185);
        centSeg = true; 
       }
       
       strip.show();
       delay(5);
       break;

     // Turn off right segment
     case 2:
       if (rightSeg) {
        //  If right segment is on --> turn if off and set rightSeg = false
        strip.fill(strip.Color(0,0,0), SEG2_RE+1, 150);
        rightSeg = false;
       } else {
        //  If right segment is off --> turn it on and set rightSeg = true
        strip.fill(color, SEG2_RE+1, 150);
        rightSeg = true;
       }
         
       strip.show();
       delay(5);
       break;

     default:
        break;
   }
}

void colorShift (int mode){
  /*  
   *   Function changes color of the light between two modes
   *   
   *     Modes:
   *   1. WHITE
   *   2. LIGHT ORANGE
  */

  switch (mode){
    //  mode = 0 --> White room lighting
    case 0:
      color = 0xFCE5B0;
      bloom();
      break;

    //  mode = 1 --> Red room lighting
    case 1:
      color = 0x800000;
      bloom();
      break;

    default:
      break;
  }
}

void setup(){
  // put your setup code here, to run once:
  power = 0;
  brightness = 45;
  rightSeg = true;
  leftSeg = true;
  centSeg = true;
  color = 0xFCE5B0;
  
  pinMode(POWER_PIN, INPUT_PULLUP);
  pinMode(WHITE_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(CENTER_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}

void loop() {
  int powerState = digitalRead(POWER_PIN);
  int leftSeg = digitalRead(LEFT_PIN);
  int centerSeg = digitalRead(CENTER_PIN);
  int rightSeg = digitalRead(RIGHT_PIN);
  int whiteState = digitalRead(WHITE_PIN);
  int redState = digitalRead(RED_PIN);
  int upBrightness = digitalRead(UP_PIN);
  int downBrightness = digitalRead(DOWN_PIN);

  //  Power button pressed
  if (powerState == LOW) {
    //  System is off --> Turn system on
    if (!power) {
      bloom();
      power = 1;
      return;
    }

    //  System is on --> Turn system off
    else {
     closeOut();
     strip.clear();
     power = 0;
     return;
   }
  }

  //  White light button pressed
  if (whiteState == LOW && power)
    colorShift(0);

  //  Custom light button pressed
  else if (redState == LOW && power)
    colorShift(1);

  //  Increase brightness button pressed
  else if (upBrightness == LOW && power)
    increaseBrightness();

  //  Decrease brightness button pressed
  else if (downBrightness == LOW && power)
    decreaseBrightness();

  //  Toggle left segment button pressed
  else if (leftSeg == LOW && power)
    toggleSegment(0);

  //  Toggle right segment button pressed
  else if (rightSeg == LOW && power)
    toggleSegment(2);

  //  Toggle center segment button pressed
  else if (centerSeg == LOW && power)
    toggleSegment(1);
}
