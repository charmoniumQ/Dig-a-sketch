int xPin = 0;
int yPin = 1;

void setup() {
  Serial.begin(19200);
}

void loop() {
  int xVal = analogRead(xPin);
  int yVal = analogRead(yPin);
  Serial.print(xVal);
  Serial.print(',');
  Serial.print(yval);
  Serial.println();
}

