#include <Adafruit_TLC59711.h>
#include <SPI.h>

#define NUM_TLC59711 1
#define NUM_GRAYSCALE_LED 12 //new define (Numbers of LED)

#define data 11
#define clock 13
#define MAX_VAL 65535

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);

int a_brightness_pin = A0;
int sensorValue_brightness = 0;

void setup() {
  tlc.begin();
  tlc.write();
}

void loop() {
  setLedPwm(0, setBright_Led()); //R0 Channel
  setLedPwm(1, setBright_Led()); //G0 Channel
  setLedPwm(2, setBright_Led()); //B0 Channel
  
  //setLedPwm(9, setBright_Led());  //R3 Channel
  //setLedPwm(10, setBright_Led());  //G3 Channel
  //setLedPwm(11, setBright_Led());  //B3 Channel

  //changeBr(setBright_Led());
  //delay(100);
}

int setBright_Led() {
  int val;
  sensorValue_brightness = analogRead(a_brightness_pin);
  val = map(sensorValue_brightness, 0, 1023, 0, 65535);
  return val;
}

void setLedPwm(uint8_t num, uint16_t br) {
  tlc.setPWM(num, br);
  tlc.write();
  delay(10);
}

void changeBr(uint16_t _br) {
  static int preindex, index;
  
  setLedPwm(preindex, 0);
  setLedPwm(index, _br);

  preindex = index;
  index++;
  if(index == 12) {
    index = 0;
  }
}
