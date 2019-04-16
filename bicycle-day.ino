
#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11
#define LDR 2

int step_number = 0, index = 0;
const int numReadings = 10;
int readings[numReadings];
unsigned long average = 0, total = 0, rpm = 0, lastMillis = 0;
volatile int rpmCount = 0;

void setup() {
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(LDR, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LDR), inc_rpm_count, FALLING);
  Serial.begin(9600);
  for (int i = 0; i < 2048; i++) {
    OneStep(true);
    delay(2);
  }
}

void loop() {
    for(int i = 0; i < 2048; i++){

  if (millis() - lastMillis >= 1000) {
    detachInterrupt(LDR);
    total = 0;
    readings[index] = rpmCount * 60;
    for (int i = 0; i <= 9; i++) {
      total = total + readings[i]; 
    }
    average = total / numReadings;
    rpm = average;
    rpmCount = 0;
    index++;
    if (index >= numReadings){
      index = 0;  
    }

    if (millis() > 11000) {
      Serial.print("RPM: ");
      Serial.println(rpm);  
    }

    lastMillis = millis();
    attachInterrupt(digitalPinToInterrupt(LDR), inc_rpm_count, FALLING);
  }
  
    if (rpm > 800) {
      OneStep(true);
      delay(2);
    } else if (rpm > 400) {
      OneStep(true);
      delay(4);  
    } else if (rpm > 350) {
      OneStep(true);
      delay(6);  
    } else if (rpm > 300) {
      OneStep(true);
      delay(8);
    } else if (rpm > 250) {
      OneStep(true);
      delay(10);
    } else if (rpm > 200) {
      OneStep(true);
      delay(12);
    } else if (rpm > 150) {
      OneStep(true);
      delay(14);
    } else {
      OneStep(true);
      delay(25);
    }
  }
}

void inc_rpm_count(){
  rpmCount++;  
}


void OneStep(bool dir){
  if(dir){
    switch(step_number){
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    } 
  } else {
    switch(step_number){
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);


    } 
  }
  step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
