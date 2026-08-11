#define MS1 A1   
#define MS2 A2   
#define DIR  A0   
#define STEP A3   
#define POT SDA   
const int   STEPS_PER_REV   = 200;       
const int   ADC_MAX         = 4095;      
const int   DEADBAND        = 15;        
const int   MIN_STEP_DELAY  = 400;       
const int   MAX_STEP_DELAY  = 4000;      
int previousPotValue = 0;
int currentStepPosition = 0;
int targetStepPosition  = 0;

void setup() {
  pinMode(MS1,  OUTPUT);
  pinMode(MS2,  OUTPUT);
  pinMode(DIR,  OUTPUT);
  pinMode(STEP, OUTPUT);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(STEP, LOW);

  previousPotValue = analogRead(POT);
  currentStepPosition = map(previousPotValue, 0, ADC_MAX, 0, STEPS_PER_REV);
  targetStepPosition  = currentStepPosition;
}

void loop() {
  int potValue = analogRead(POT);

  if (abs(potValue - previousPotValue) > DEADBAND) {

    targetStepPosition = map(potValue, 0, ADC_MAX, 0, STEPS_PER_REV);
    int delta = abs(potValue - previousPotValue);
    int stepDelay = map(delta, DEADBAND, ADC_MAX, MAX_STEP_DELAY, MIN_STEP_DELAY);
    stepDelay = constrain(stepDelay, MIN_STEP_DELAY, MAX_STEP_DELAY);git
    if (targetStepPosition > currentStepPosition) {
      digitalWrite(DIR, HIGH);
    } else {
      digitalWrite(DIR, LOW);
    }
    if (currentStepPosition != targetStepPosition) {
      digitalWrite(STEP, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(STEP, LOW);
      delayMicroseconds(stepDelay);
      if (targetStepPosition > currentStepPosition) {
        currentStepPosition++;
      } else {
        currentStepPosition--;
      }
    }

    previousPotValue = potValue;
  }
}