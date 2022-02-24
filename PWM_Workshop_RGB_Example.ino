#include <Adafruit_TLC59711.h>
#include <SPI.h>

#define NUM_TLC59711 1
#define NUM_RGB_LED 4 //new define (Numbers of LED)

#define data 11
#define clock 13
#define MAX_VAL 65535

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);

uint16_t val_r = 0;
uint16_t val_g = 0;
uint16_t val_b = 0;

int switchPin = 2;

int a_red_pin = A0;
int a_green_pin = A1;
int a_blue_pin = A2;

int sensorValue_red = 0;
int sensorValue_green = 0;
int sensorValue_blue = 0;

void setup() {
  pinMode(switchPin, INPUT);
  
  tlc.begin();
  tlc.write();
}

void loop() {
  //setColorLed(0, setBright_red(), setBright_green(), setBright_blue());
  //setColorLed(1, setBright_red(), setBright_green(), setBright_blue());
  //setColorLed(2, setBright_red(), setBright_green(), setBright_blue());
  //setColorLed(3, setBright_red(), setBright_green(), setBright_blue());
  
  changeColor();
}

int setBright_red() {
  int val;
  sensorValue_red = analogRead(a_red_pin);
  val = map(sensorValue_red, 0, 1023, 0, 65535);
  return val;
}

int setBright_green() {
  int val;
  sensorValue_green = analogRead(a_green_pin);
  val = map(sensorValue_green, 0, 1023, 0, 65535);
  return val;
}

int setBright_blue() {
  int val;
  sensorValue_blue = analogRead(a_blue_pin);
  val = map(sensorValue_blue, 0, 1023, 0, 65535);
  return val;
}

void setColorLed(uint8_t num, uint16_t r, uint16_t g, uint16_t b) {
  tlc.setLED(num, r, g, b);
  tlc.write();
  delay(10);
}

void changeColor() {
  colorWipe(65535, 0, 0, 100); // "Red" (depending on your LED wiring)
  delay(200);
  colorWipe(0, 65535, 0, 100); // "Green" (depending on your LED wiring)
  delay(200);
  colorWipe(0, 0, 65535, 100); // "Blue" (depending on your LED wiring)
  delay(200);
}

void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for (uint16_t i = 0; i < NUM_RGB_LED * NUM_TLC59711; i++) {
    tlc.setLED(i, r, g, b);
    tlc.write();
    delay(wait);
  }  
}
