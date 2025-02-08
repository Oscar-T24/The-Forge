void setup() {
 
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(A1));
  Serial.print(" and reading two ");
  Serial.print(analogRead(A2));
    Serial.print(" and reading three ");
     Serial.print(analogRead(A5));
  Serial.println();

}
