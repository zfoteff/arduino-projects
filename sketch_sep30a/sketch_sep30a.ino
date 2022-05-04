#define RED_LED 6
#define BLUE_LED 5
#define GREEN_LED 9
#define SOUND_PIN 7

int red_value = 255;
int blue_value = 

void Initialize()
{
  analogWrite(RED_LED, 0);
  analogWrite(GREEN_LED, 0);
  analogWrite(GREEN_LED, 0);
}

void setup() 
{
  // put your setup code here, to run once:
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(SOUND_LED, INPUT);

  Initialize()
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
