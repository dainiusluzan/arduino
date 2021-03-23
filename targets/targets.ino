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
  bool active = false;
  float startTime;
  int hitTime = 3000;

  Target(int target, int red, int green) {
    redLed.construct(red);
    greenLed.construct(green);
    targetPin = target;
    pinMode(targetPin, INPUT);
  }
  void activate() {
    active = true;
    redLed.on();
    startTime = millis();
  }

  bool isActive() {
     bool sactive = (active && millis() - startTime > hitTime);
     if (sactive == false) {
       redLed.off();
       active = false;
     }
     //Serial.print(active);
     return sactive;
  }

  bool hit() { bool hited = digitalRead(targetPin); }
};

Target target_1(1, 2, 3);
Target target_2(4, 5, 6);
Target target_3(7, 8, 9);
Target target_4(10, 11, 12);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  if (isAnyTargetActive() == false) {
    activateRandom();
  } else {
    
  }
  delay(300);
}

bool isAnyTargetActive() {
  return (target_1.isActive() || target_2.isActive() || target_3.isActive());
}

void activateRandom() {
  int targetNr = random(1,5);
  Serial.print(targetNr);
  switch (targetNr) {
    case 1:
      target_1.activate();
      break;
    case 2:
      target_2.activate();
      break;
    case 3:
      target_3.activate();
      break;
    case 4:
      target_4.activate();
      break;
  }
}
