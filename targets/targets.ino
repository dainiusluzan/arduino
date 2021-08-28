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

Target target_1(22, 42, 43);
Target target_2(24, 36, 37);
Target target_3(26, 40, 41);
Target target_4(28, 38, 39);
Target targets[4] = {target_1, target_2, target_3, target_4};

const int RED = 1;
const int BLUE = 2;
int redPoints = 0;
int bluePoints = 0;
int points[3] = {0,0,0};
long gameStarted;
long gameTime = 45000;
bool gameOver = false;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {

  initiativeBlinking();
  
  runTheGame(RED);
  
  initiativeBlinking();

  runTheGame(BLUE);
 
  
  if (points[RED] > points[BLUE]) {
    blinkTargets(RED, 10);
  } else {
    blinkTargets(BLUE, 10);
  }
  
  Serial.print("\nRED POINTS "); Serial.print(redPoints); Serial.print(" BLUE POINTS "); Serial.print(bluePoints);
  Serial.print("\n Game over \n");
  delay(120000);
}

void runTheGame(int color) {
  gameStarted = millis();
  gameOver = false;
  while (gameOver == false) {
    
    for (int i = 0;  i < 4; i++) {
      if (targets[i].update() == true) {
        points[color] += 1;
        Serial.print(points[color]);
        Serial.print("\n\n");
        delay(500);
      }
    }
    if (isAnyTargetActive(color) == false) {
      activateRandom(color);
    }
    
    delay(100);
    
    // Check if time run out
    if (millis() - gameStarted > gameTime) {
      gameOver = true;
    }
  }
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