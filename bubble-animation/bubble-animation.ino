#include <CapacitiveSensor.h>
#include <Adafruit_NeoPixel.h>
#define strip1PIN A0
#define strip2PIN A1
#define strip3PIN A2
#define strip4PIN A3
#define strip5PIN A4
#define NUM_LEDS 16


//DEFINE PIN MATRIX
const int numOfRows = 5;
const int numOfCols = 8;
int delayTime = 300;

int pinMatrix[numOfRows][numOfCols] = {
  {13, 12, 11, 10, 9, 8, 7, 6},
  {5, 4, 3, 2, 22, 23, 24, 25},
  {26, 27, 28, 29, 30, 31, 32, 33},
  {34, 35, 36, 37, 38, 39, 40, 41},
  {42, 43, 44, 45, 46, 47, 48, 49},
};

//DEFINE CAPACITIVE SENSOR
CapacitiveSensor Sensor1 = CapacitiveSensor(50, 51);
CapacitiveSensor Sensor2 = CapacitiveSensor(50, 52);
long SwitchCapa1;
long SwitchCapa2;

int count = 0;
int SwitchState = 0;
int LastSwitchState = 0;

//CREATE NEOPIXEL STRIP
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_LEDS, strip1PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(NUM_LEDS, strip2PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(NUM_LEDS, strip3PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4 = Adafruit_NeoPixel(NUM_LEDS, strip4PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5 = Adafruit_NeoPixel(NUM_LEDS, strip5PIN, NEO_GRB + NEO_KHZ800);

//DEFINE BLACK COLOR
uint32_t black1 = strip1.Color(0,0,0);
uint32_t black2 = strip2.Color(0,0,0);
uint32_t black3 = strip3.Color(0,0,0);
uint32_t black4 = strip4.Color(0,0,0);
uint32_t black5 = strip5.Color(0,0,0);


void setup() {
  Serial.begin(9600);

  //SET UP MATRIX PIN
  Serial.println("set up start");
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfCols; j++) {
      pinMode(pinMatrix[ i ][ j ], OUTPUT);
    }//close for i
  }//close for J

  //SET UP NEOPIXEL
  strip1.begin();
  strip1.show();
  strip2.begin();
  strip2.show();
  strip3.begin();
  strip3.show();
  strip4.begin();
  strip4.show();
  strip5.begin();
  strip5.show();

//resetLED();
}

void resetLED(){
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.clear();
  strip5.clear();
//    strip5.fill(black1, 0, 16);
//    strip5.show();
//    strip4.fill(black2, 0, 16);
//    strip4.show();
//    strip3.fill(black3, 0, 16);
//    strip3.show();
//    strip2.fill(black4, 0, 16);
//    strip2.show();
//    strip1.fill(black5, 0, 16);
//    strip1.show();
}

void loop() {

  //READ CAPACITIVE VALUE
  SwitchCapa1 = Sensor1.capacitiveSensor(30);
  SwitchCapa2 = Sensor2.capacitiveSensor(30);
  Serial.print("SwitchCapa1:");
  Serial.println(SwitchCapa1);
  Serial.print("SwitchCapa2:");
  Serial.println(SwitchCapa2);

  //DETECT SWITCH STATE
  if ( SwitchCapa1 > 2000 || SwitchCapa2 > 2000 ) {
    SwitchState = 1;
  } else {
    SwitchState = 0;
  }
  Serial.print("SwitchState:");
  Serial.println(SwitchState);


  //WATERFALL AND LED WHEN TURN ON SWITCH
  if (SwitchState == 1 ) {
    delay(5000);
    waterfall();
  } else {
    if (count == 0 ) {
      randomBubble();
    } else {
      breath();
    }
  }

  //TURN ON LED
  ledEffect();

  //COUNT OF TURNING ON SWITCH
  if (LastSwitchState == 0 && SwitchState == 1 ) {
    count++;
    Serial.print("count:");
    Serial.println(count);
  }

  LastSwitchState = SwitchState;
  delay(500);

  //RECOUNT AFTER FIVE TIMES OF REFILLING
  if (count > 5 ) {
    count = 0;
resetLED();
  }
}

//WATERFALL EFFECT
void waterfall() {
  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfCols; j++) {
      digitalWrite(pinMatrix[i][j], HIGH);
    }//close for j
    delay(delayTime);
  }//close for i

  for (int i = 0; i < numOfRows; i++) {
    for (int j = 0; j < numOfCols; j++) {
      digitalWrite(pinMatrix[i][j], LOW);
    }//close for j
    delay(delayTime);
  }//close for i
}

//down to up multiple line
void bigwave() {
  int waveTime = 2;
  while (waveTime > 0) {
    for (int j = 0; j < numOfCols; j++) {
      for (int i = 0; i < numOfRows; i++) {
        digitalWrite(pinMatrix[ i ][ j ], HIGH);
        delay(100);
      }//close for i
      delay(100);
    }//close for j

    for (int j = 0; j <  numOfCols; j++) {
      for (int i = 0; i < numOfRows; i++) {
        digitalWrite(pinMatrix[ i ][ j ], LOW);
        delay(100);
      }//close for j
      delay(100);
    }
    waveTime--;
  }//close for i
  delay(1000);
  count = 0;
}

void randomBubble() {
  int randI1 = random(0, numOfRows);
  int randJ1 = random(0, numOfCols);
  int randI2 = random(0, numOfRows);
  int randJ2 = random(0, numOfCols);
  digitalWrite(pinMatrix[randI1][randJ1], HIGH);
  delay(500);
  digitalWrite(pinMatrix[randI2][randJ2], HIGH);
  delay(1000);

  digitalWrite(pinMatrix[randI1][randJ1], LOW);
  delay(500);
  digitalWrite(pinMatrix[randI2][randJ2], LOW);
  delay(1000);
}

void breath() {
  for (int i = numOfRows - count; i < numOfRows; i++) {
    for (int j = 0; j < numOfCols; j++) {
      digitalWrite(pinMatrix[i][j], HIGH);
    }//close for j
  }//close for i
  delay(3000);

  for (int i = numOfRows - count; i < numOfRows; i++) {
    for (int j = 0; j < numOfCols; j++) {
      digitalWrite(pinMatrix[i][j], LOW);
    }//close for j
  }
  delay(2000);
}

void middleWave() {

}

void ledEffect() {
  uint32_t blue1 = strip1.Color(255, 255, 255);
  uint32_t blue2 = strip2.Color(255, 255, 255);
  uint32_t blue3 = strip3.Color(255, 255, 255);
  uint32_t blue4 = strip4.Color(255, 255, 255);
  uint32_t blue5 = strip5.Color(255, 255, 255);

  if (count == 1) {
    strip5.fill(blue5, 0, 16);
    strip5.show();
  } else if (count == 2) {
    strip5.fill(blue5, 0, 16);
    strip5.show();
    delay(delayTime);
    strip4.fill(blue4, 0, 16);
    strip4.show();
  } else if (count == 3) {
    strip5.fill(blue5, 0, 16);
    strip5.show();
    delay(delayTime);
    strip4.fill(blue4, 0, 16);
    strip4.show();
    delay(delayTime);
    strip3.fill(blue3, 0, 16);
    strip3.show();
  } else if (count == 4) {
    strip5.fill(blue5, 0, 16);
    strip5.show();
    delay(delayTime);
    strip4.fill(blue4, 0, 16);
    strip4.show();
    delay(delayTime);
    strip3.fill(blue3, 0, 16);
    strip3.show();
    delay(delayTime);
    strip2.fill(blue2, 0, 16);
    strip2.show();
  } else if (count == 5) {
    strip5.fill(blue5, 0, 16);
    strip5.show();
    delay(delayTime);
    strip4.fill(blue4, 0, 16);
    strip4.show();
    delay(delayTime);
    strip3.fill(blue3, 0, 16);
    strip3.show();
    delay(delayTime);
    strip2.fill(blue2, 0, 16);
    strip2.show();
    delay(delayTime);
    strip1.fill(blue1, 0, 16);
    strip1.show();
    bigwave();
  }
}
