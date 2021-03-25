class Led {
  public:
  int pin;
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
  Led blueLed;
  int targetPin;
  int hitTime = 3000;
  int active = 0;
  long startTime;
  int points[3] = {0, 0, 0};

  Target(int target, int red, int blue) {
    redLed.construct(red);
    blueLed.construct(blue);
    targetPin = target;
    pinMode(targetPin, INPUT);
  }

  void activate(int color) {
    active = color;
    turnOn(color);
    startTime = millis();
  }

  bool update() {
    if (millis() - startTime > hitTime || hit()) {
      active = 0;
      turnOff();
    }
  }

  bool hit() {
    if (random(1,10) == 1) {
      points[active]++;
      return true;
    }
    return false;
    //return digitalRead(targetPin) == 1;
  }

  void turnOn(int color) {
    if (color == 1) {
      redLed.on();
    } else if (color == 2) {
      blueLed.on();
    }
  }

  void turnOff() {
    redLed.off();
    blueLed.off();
  }

  int activeColor() {
    return active;
  }
};

const int RED = 1;
const int BLUE = 2;

Target target_1(1, 5, 6);
Target target_2(2, 7, 8);
Target target_3(3, 9, 10);
Target target_4(4, 11, 12);
Target targets[] = {target_1, target_2, target_3, target_4};

int redPoints = 0;
int bluePoints = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("LOOP ");Serial.print(targets[0].active);Serial.print(targets[1].active);Serial.print(targets[2].active);Serial.print(targets[3].active);
  Serial.print("     RED POINTS ");Serial.print(redPoints);Serial.print(" BLUE POINTS ");Serial.print(bluePoints);
  Serial.print("\n");
  for (int i = 0; i++, i < 4;) {
    targets[i].update();
    redPoints += targets[i].points[RED];
    bluePoints += targets[i].points[BLUE];
  }
  
  if (isAnyTargetActive(RED) == false) {
    activateRandom(RED);
  }
  if (isAnyTargetActive(BLUE) == false) {
    activateRandom(BLUE);
  }
  delay(100);
}

bool isAnyTargetActive(int color) {
  return (targets[0].active == color || targets[1].active == color || targets[2].active == color || targets[3].active == color);
}

void activateRandom(int color) {
  bool found = false;
  while (found == false) {
    int targetNr = random(0,4);   
    if (targets[targetNr].active == 0) {
      targets[targetNr].activate(color);
      found = true;
    }
  }
}
