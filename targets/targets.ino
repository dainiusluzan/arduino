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
  Led blueLed;
  int targetPin;
  int hitTime = 1500;
  int active = 0;
  long startTime;


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

    if (millis() - startTime > hitTime) {
      //Serial.print("Update ");Serial.print(targetPin); Serial.print("\n");
      //Serial.print("Start time ");Serial.print(startTime); Serial.print("\n");
      active = 0;
      blueLed.off();
      redLed.off();
    }
  }
  void turnOn(int color) {
    Serial.print(". PIN ");Serial.print(targetPin); Serial.print("\n");
    Serial.print(". LED ON COLOR ");Serial.print(color); Serial.print("\n");
    if (color == 1) {
      redLed.on();
    } else if (color == 2) {
      blueLed.on();
    }
  }

  void turnOff(int color) {
    Serial.print(". PIN ");Serial.print(targetPin); Serial.print("\n");
    Serial.print(". LED OFF COLOR ");Serial.print(color); Serial.print("\n");
    if (color == 1) {
      redLed.off();
    } else if (color == 2) {
      blueLed.off();
    }
  }
};
const int OFF = 0;
const int RED = 1;
const int BLUE = 2;

Target target_1(13, 2, 3);
Target target_2(13, 5, 6);
Target target_3(13, 8, 9);
//Target target_4(13, 10, 11);

Target targetsv2[] = {target_1, target_2, target_3};
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  Serial.print(" Loop ");Serial.print("\n");
  target_1.update();
  target_2.update();
  target_3.update();
  if (isAnyTargetActive(RED) == false) {
    activateRandom(RED);
  }
  if (isAnyTargetActive(BLUE) == false) {
    activateRandom(BLUE);
  }
  delay(300);
}

bool isAnyTargetActive(int color) {
  return (target_1.active == color || target_2.active == color|| target_3.active == color);
}

void activateRandom(int color) {
  bool found = false;
  while (found == false) {
    int targetNr = random(0,3);
    target_1.update();
    target_2.update();
    target_3.update();
    //Serial.print("Target nr ");Serial.print(targetNr);
    //Serial.print(". Active ");Serial.print(targetsv2[targetNr].active);
    //Serial.print(".");
    
    if (targetsv2[targetNr].active == 0) {
      targetsv2[targetNr].activate(color);
      found = true;
    }
  }
  Serial.print(" Out of while ");Serial.print("\n");
}

