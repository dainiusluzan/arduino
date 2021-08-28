class Led {
  public:
    int pin;
    void construct(int ledPin) {
      pin = ledPin;
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
    }
    void on() {
      digitalWrite(pin, LOW);
    }
    void off() {
      digitalWrite(pin, HIGH);
    }
};

class Target {
  public:
    Led redLed;
    Led blueLed;
    int targetPin;
    int hitTime = 2000;
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
      if (active != 0 && millis() - startTime > hitTime) {
        active = 0;
        turnOff();
        return false;
      } else if (active != 0 && hit()) {
        active = 0;
        turnOff();
        return true;
      }
    }

    bool hit() {
      if (digitalRead(targetPin) == 1) {
        return true;
      }
      return false;
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
};

const int RED = 1;
const int BLUE = 2;

Target target_1(1, 5, 6);
Target target_2(2, 7, 8);
Target target_3(3, 9, 10);
Target target_4(4, 11, 12);
Target targets[4] = {target_1, target_2, target_3, target_4};

int redPoints = 0;
int bluePoints = 0;
long gameStarted;
long gameTime = 15000;
bool gameOver = false;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  gameStarted = millis();
}

void loop() {
  blinkTargets(RED, 1);
  redPoints = 0;
  bluePoints = 0;
  targets[2].activate(RED);
  targets[1].activate(BLUE);
  while (gameOver == false) {
    for (int i = 0; i++, i < 4;) {
      targets[i].update();
    }
    if (isAnyTargetActive(RED) == false) {
      Serial.print("No active red"); Serial.print("\n");
      activateRandom(RED);
      Serial.print("WHILE "); Serial.print(targets[0].active); Serial.print(targets[1].active); Serial.print(targets[2].active); Serial.print(targets[3].active); Serial.print("\n");
    }
    if (isAnyTargetActive(BLUE) == false) {
      Serial.print("No active blue"); Serial.print("\n");
      activateRandom(BLUE);
      Serial.print("WHILE "); Serial.print(targets[0].active); Serial.print(targets[1].active); Serial.print(targets[2].active); Serial.print(targets[3].active); Serial.print("\n");
    }

    delay(50);
    if (millis() - gameStarted > gameTime) {
      gameOver = true;
    }
  }


  for (int i = 0; i++, i < 4;) {
    redPoints += targets[i].points[RED];
    bluePoints += targets[i].points[BLUE];
  }

  Serial.print("     RED POINTS "); Serial.print(redPoints); Serial.print(" BLUE POINTS "); Serial.print(bluePoints);
  Serial.print("\n Game over \n");
  delay(100000000);
}

bool isAnyTargetActive(int color) {
  return (targets[0].active == color || targets[1].active == color || targets[2].active == color || targets[3].active == color);
}

void activateRandom(int color) {
  bool found = false;
  while (found == false) {
    int targetNr = random(0, 4);
    if (targets[targetNr].active == 0) {
      targets[targetNr].activate(color);
      found = true;
    }
  }
}


void blinkTargets(int color, int times) {
  for (int i = 0;  i < times; i++) {
    for (int s = 0;  s < 4; s++) {
      targets[s].turnOn(color);
      delay(77);
    }

    for (int s = 0;  s < 4; s++) {
      targets[s].turnOff();
      delay(77);
    }

  }
}

void initiativeBlinking() {
    for (int i = 0;  i < 4; i++) {
    targets[i].turnOn(RED);
    delay(400);
    targets[i].turnOff();
    targets[i].turnOn(BLUE);
    delay(400);
    targets[i].turnOff();
  }
}