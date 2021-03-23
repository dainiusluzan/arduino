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
  int targetPin;

  Target(int target, int red, int green) {
    redLed.construct(red);
    greenLed.construct(green);
    targetPin = target;
    pinMode(targetPin, INPUT);
  }

  bool hit() { bool hited = digitalRead(targetPin); }

  void turnOff() {
    redLed.off();
    greenLed.off();
  }
  void turnOnRed() { redLed.on(); }
  void turnOffRed() { redLed.off(); }
  void turnOnGreen() { greenLed.on(); }
  void turnOffGreen() { greenLed.off(); }
};

int hitTime = 1000;

Target target_1(1, 2, 3);
Target target_2(4, 5, 6);
Target target_3(7, 8, 9);
Target target_4(10, 11, 12);

void setup() {
  Serial.begin(9600);
}

void loop() {

}


