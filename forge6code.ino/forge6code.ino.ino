void setup() {
 
 // Configuration : Broche ENA sur pin 3 (PWM) broche IN1 sur pin 2
 pinMode(3,OUTPUT);
pinMode(2,OUTPUT);
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
