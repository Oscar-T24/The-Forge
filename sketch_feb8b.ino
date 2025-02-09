void setup() {
 
 // Configuration : Broche ENA sur pin 3 (PWM) broche IN1 sur pin 2
pinMode(2,OUTPUT);
pinMode(3,OUTPUT);


pinMode(4,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(7,OUTPUT);
pinMode(8,OUTPUT);




Serial.begin(9600);

}

void loop() {

 
  Serial.print(analogRead(A3));
  Serial.print(" A1 :  ");
  Serial.print(analogRead(A1));
  Serial.print(" A2 :   ");
  Serial.print(analogRead(A2));
  Serial.println();
  
  int xAxis1 = analogRead(A2);
  int yAxis1 = analogRead(A1);
  int button1 = analogRead(A3);
  int xAxis2 = analogRead(A4);
  int yAxis2 = analogRead(A5);
  // if joystick move
  if (yAxis1 >= 1023){
    //front
    digitalWrite (5,HIGH);
    digitalWrite(4,LOW);
    digitalWrite (3,HIGH);
    digitalWrite(2,LOW);
  }else if (yAxis1 <= 1){
    //back
    digitalWrite (4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite (3,LOW);
    digitalWrite(2,HIGH);
  }else if (xAxis1 >= 1023){
    //right
    digitalWrite (5,HIGH);
    digitalWrite(4,LOW);
    digitalWrite (2,HIGH);
    digitalWrite(3,LOW);
  } else if (xAxis1 <= 1){
    //left
    digitalWrite (4,HIGH);
    digitalWrite(5,LOW);
    digitalWrite (3,HIGH);
    digitalWrite(2,LOW);
  }else {
    digitalWrite (4,LOW);
    digitalWrite(5,LOW);
    digitalWrite (3,LOW);
    digitalWrite(2,LOW);
  }

  if (button1 <= 1){
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    analogWrite(8,255);
  } else {
    analogWrite(8,0);
  }
  
  //analogWrite(3,128);
  //analogWrite(4,128);
  //Serial.print("Running");
  //Serial.println();


//int rawValue = analogRead(A5);  // Read raw analog value
//int mappedValue = map(rawValue, 512, 1023, 0, 255);  // Map to 0-255

// Apply a quadratic function to reduce sensitivity at the beginning
//int pwmValue = (mappedValue * mappedValue) / 255;  // Quadratic scaling (pwmValue grows slower at first)

// Ensure pwmValue stays within the 0-255 range
//pwmValue = constrain(pwmValue, -255, 255);

// if (pwmValue > 10) {  // Increased threshold to reduce sensitivity
//   digitalWrite(2, HIGH);
//   digitalWrite(4, LOW);
// } else {
//   digitalWrite(4, HIGH);
//   digitalWrite(2, LOW);
// }

// Serial.println(pwmValue);  // Print the processed PWM value for debugging
// analogWrite(3, 97);  // Use the scaled PWM value

// }
// void debug(){

//   digitalWrite(2,HIGH);
//   for(unsigned char i = 0; i<255;i++){
//     analogWrite(3,i);
//     delay(20);
//   }
//     for(unsigned char i = 255; i>0;i--){
//     analogWrite(3,i);
//     delay(20);
//   }



}
