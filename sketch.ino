#include <LiquidCrystal.h>

const uint8_t PIN_BTN_ETAJ1 = 2;
const uint8_t PIN_BTN_ETAJ2 = 3;
const uint8_t PIN_LED_ETAJ1 = 4;
const uint8_t PIN_LED_ETAJ2 = 5;
const uint8_t PIN_BUZZER    = 6;

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

typedef enum {
  STATE_IDLE,      
  STATE_MOVING,    
  STATE_ARRIVED    
} ElevatorState_t;

ElevatorState_t currentState = STATE_IDLE;
uint8_t currentFloor = 1;
uint8_t targetFloor = 1;

uint32_t movementStartTime = 0;
const uint32_t MOVEMENT_DURATION = 3000; 

void setup() {
  pinMode(PIN_BTN_ETAJ1, INPUT_PULLUP);
  pinMode(PIN_BTN_ETAJ2, INPUT_PULLUP);
  pinMode(PIN_LED_ETAJ1, OUTPUT);
  pinMode(PIN_LED_ETAJ2, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  lcd.begin(16, 2);
  Serial.begin(9600);

  digitalWrite(PIN_LED_ETAJ1, HIGH);
  digitalWrite(PIN_LED_ETAJ2, LOW);
  updateDisplay("Liftul e la etajul", currentFloor);
}

void loop() {
  readInputs();
  updateLogic();
}


void readInputs() {
  if (currentState == STATE_IDLE) {
    if (digitalRead(PIN_BTN_ETAJ1) == LOW && currentFloor != 1) {
      targetFloor = 1;
    } 
    else if (digitalRead(PIN_BTN_ETAJ2) == LOW && currentFloor != 2) {
      targetFloor = 2;
    }
  }
}

void updateLogic() {
  switch (currentState) {
    
    case STATE_IDLE:
      if (targetFloor != currentFloor) {
        currentState = STATE_MOVING;
        movementStartTime = millis(); 
        
        updateDisplay("Merge la etajul", targetFloor);
        Serial.print("Pleaca spre etajul: ");
        Serial.println(targetFloor);
        
        digitalWrite(PIN_LED_ETAJ1, LOW);
        digitalWrite(PIN_LED_ETAJ2, LOW);
      }
      break;

    case STATE_MOVING:
      if (millis() - movementStartTime >= MOVEMENT_DURATION) {
        currentFloor = targetFloor;
        currentState = STATE_ARRIVED; 
      }
      break;

    case STATE_ARRIVED:
      updateDisplay("Liftul e la etajul", currentFloor);
      Serial.print("A ajuns la etajul: ");
      Serial.println(currentFloor);
      
      digitalWrite(currentFloor == 1 ? PIN_LED_ETAJ1 : PIN_LED_ETAJ2, HIGH);
      
      tone(PIN_BUZZER, 950, 200);
      
      currentState = STATE_IDLE;
      break;
  }
}

void updateDisplay(const char* message, uint8_t floorNumber) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
  lcd.setCursor(0, 1);
  lcd.print(floorNumber);
}
