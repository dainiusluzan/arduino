class Led {
  int pin;

public:
  void construct(int ledPin) {
    pin = ledPin;
    pinMode(pin, INPUT);
  }
  void on() { digitalWrite(pin, HIGH); }
  void off() { digitalWrite(pin, LOW); }
};

class Target {
public:
  Led redLed;
  Led greenLed;
  Led blueLed;
  int targetPin;

  bool redOn = false;
  bool greenOn = false;
  bool blueOn = false;
  int redCount;
  int greenCount;
  int blueCount;

  float nowBlue;
  Target(int target, int red, int green, int blue) {
    redLed.construct(red);
    greenLed.construct(green);
    blueLed.construct(blue);
    targetPin = target;
    pinMode(targetPin, INPUT);
  }

  bool hit() {
    bool hited = digitalRead(targetPin);
  }
  
  void turnOnRandom() {
    int target = random(1, 5);
    switch (target) {
    case 1:
      turnOnRed();
      break;
    case 2:
      turnOnGreen();
      break;
    case 3:
      turnOnBlue();
      break;
    }
  }
  void turnOff() {
    redLed.off();
    greenLed.off();
    blueLed.off();
  }
  void turnOnRed() {
    redLed.on();
    redOn = true;
  }
  void turnOffRed() {
    redLed.off();
    redOn = false;
  }
  void turnOnGreen() {
    greenLed.on();
    greenOn = true;
  }
  void turnOffGreen() {
    greenLed.off();
    greenOn = false;
  }
  void turnOnBlue() {
    blueLed.on();
    blueOn = true;
  }
  void turnOffBlue() {
    blueLed.off();
    blueOn = false;
  }
};

int hitTime = 1000;

Target firstTarget(7, 2, 3, 4);

void setup() {
  Serial.begin(9600);
}
void loop() {

}
