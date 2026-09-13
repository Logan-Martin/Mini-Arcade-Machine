const int buttonPinA = 10; 
const int buttonPinB = 8; 
//const int ledPin = 13; 
int buttonAState = 0; 
int buttonBState = 0; 

void setup() {
  pinMode(buttonPinA, INPUT_PULLUP);
  pinMode(buttonPinB, INPUT_PULLUP);

  // Need this to see prints:
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonAState = digitalRead(buttonPinA);
  buttonBState = digitalRead(buttonPinB);

  if (buttonAState == LOW) {
    Serial.println("Pressed ButtonA!");
  }

  if (buttonBState == LOW) {
    Serial.println("Pressed ButtonB!");
  }

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  //if (buttonState == HIGH) {
    // turn LED on:
  //  digitalWrite(ledPin, HIGH);
  //} else {
    // turn LED off:
  //  digitalWrite(ledPin, LOW);
  //}
}
