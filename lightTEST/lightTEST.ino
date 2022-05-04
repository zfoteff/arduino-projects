#define RED_LED 6
#define BLUE_LED 5
#define GREEN_LED 9

int brightness = 256;
int gBright = 0;
int rBright = 0;
int bBright = 0;

void Test()
{ 
  analogWrite(RED_LED, 0);
  analogWrite(GREEN_LED, 0);
  analogWrite(BLUE_LED, 0);
  
  for (int i = 0; i < brightness; i++)
  {
    analogWrite(RED_LED, rBright);
    rBright += 1;
    delay(100);
  }

  for (int i = rBright; i > 0; i--)
  {
    analogWrite(RED_LED, rBright);
    rBright -= 1;
    delay(100);
  }

  for (int i = 0; i < brightness; i++)
  {
    analogWrite(GREEN_LED, gBright);
    gBright += 1;
    delay(100);
  }

  for (int i = gBright; i > 0; i--)
  {
    analogWrite(GREEN_LED, gBright);
    gBright -= 1;
    delay(100);
  }

  for (int i = 0; i < brightness; i++)
  {
    analogWrite(BLUE_LED, bBright);
    bBright -= 1;
    delay(100);
  }

  for (int i = bBright; i > 0; i--)
  {
    analogWrite(BLUE_LED, bBright);
    bBright -= 1;
    delay(100);
  }

  for (int i = 256; i > 0; i--)
  {
    analogWrite(RED_LED, i);
    analogWrite(GREEN_LED, i);
    analogWrite(BLUE_LED, i);
    delay(10);
  }

  analogWrite(RED_LED, 0);
  analogWrite(GREEN_LED, 0);
  analogWrite(BLUE_LED, 0);
}

void setup()
{
  // put your setup code here, to run once:
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  
}

void loop()
{
  analogWrite(RED_LED, 150);
  analogWrite(GREEN_LED, 255);
  analogWrite(BLUE_LED, 0);
}
