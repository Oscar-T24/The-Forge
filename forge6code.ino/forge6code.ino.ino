void setup() {
 
 // Configuration : Broche ENA sur pin 3 (PWM) broche IN1 sur pin 2
pinMode(3,OUTPUT);
pinMode(2,OUTPUT);
pinMode(4,OUTPUT);
Serial.begin(9600);

}

void loop() {

/*
  Serial.print(analogRead(A1));
  Serial.print(" and reading two ");
  Serial.print(analogRead(A2));
    Serial.print(" and reading three ");
     Serial.print(analogRead(A5));
  Serial.println();
  */
  
int rawValue = analogRead(A5);  // Read raw analog value
int mappedValue = map(rawValue, 512, 1023, 0, 255);  // Map to 0-255

// Apply a quadratic function to reduce sensitivity at the beginning
int pwmValue = (mappedValue * mappedValue) / 255;  // Quadratic scaling (pwmValue grows slower at first)

// Ensure pwmValue stays within the 0-255 range
pwmValue = constrain(pwmValue, -255, 255);

if (pwmValue > 10) {  // Increased threshold to reduce sensitivity
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);
} else {
  digitalWrite(4, HIGH);
  digitalWrite(2, LOW);
}

Serial.println(pwmValue);  // Print the processed PWM value for debugging
analogWrite(3, 97);  // Use the scaled PWM value

}
void debug(){

  digitalWrite(2,HIGH);
  for(unsigned char i = 0; i<255;i++){
    analogWrite(3,i);
    delay(20);
  }
    for(unsigned char i = 255; i>0;i--){
    analogWrite(3,i);
    delay(20);
  }



}
