const int analogInPin = A0;  // ESP8266 Analog Pin ADC0 = A0

float sensorValue = 0;  // value read from the pot

void setup() {
  // initialize serial communication at 115200
  Serial.begin(115200);
}

float analogEmulation() {
  return random(20, 35);
}


void loop() {
  sensorValue = analogRead(analogInPin);
  sensorValue = sensorValue * 0.03176;
  
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\n");

  sensorValue = analogEmulation();

  Serial.print("sensor Emulado = ");
  Serial.print(sensorValue);
  Serial.print("\n");
  
  delay(1000);
}
