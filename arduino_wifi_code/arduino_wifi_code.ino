#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "football";        
char pass[] = "football";        
int status = WL_IDLE_STATUS;

WiFiServer server(80);

// Motor Pins
int moteurGaucheForward = 5;
int moteurGaucheReverse = 4;
int moteurDroiteReverse = 3;
int moteurDroiteForward = 2;
int push = 12;
int enb = 9;
int ena = 10;

boolean isShoot = false;
boolean isTalo = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(moteurGaucheForward, OUTPUT);
  pinMode(moteurGaucheReverse, OUTPUT);
  pinMode(moteurDroiteReverse, OUTPUT);
  pinMode(moteurDroiteForward, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(push, OUTPUT);
  
  digitalWrite(push, HIGH);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }
  else{
    Serial.println("Module found");
  }

  Serial.print("Creating access point: ");
  Serial.println(ssid);
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }

  delay(10000);
  server.begin();
  printWiFiStatus();

  //myservo.attach(6);
  //myservo.write(0);
  //delay(1000);
  //myservo.write(60);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        if (c == '\n') {
          if (request.startsWith("GET /forward")) {
            moveForward();
          } else if (request.startsWith("GET /backward")) {
            moveBackward();
          } else if (request.startsWith("GET /left")) {
            turnLeft();
          } else if (request.startsWith("GET /right")) {
            turnRight();
          } else if (request.startsWith("GET /shoot")) {
            shoot();
          } else if (request.startsWith("GET /stop")) {
            stopMotors();
          }
          request = "";
          break;
        }
      }
    }
    client.stop();
  }
}

void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(moteurGaucheForward, HIGH);
  digitalWrite(moteurGaucheReverse, LOW);
  digitalWrite(moteurDroiteForward, HIGH);
  digitalWrite(moteurDroiteReverse, LOW);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}

void moveBackward() {
  Serial.println("Moving Backward");
  digitalWrite(moteurGaucheForward, LOW);
  digitalWrite(moteurGaucheReverse, HIGH);
  digitalWrite(moteurDroiteForward, LOW);
  digitalWrite(moteurDroiteReverse, HIGH);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}

void turnLeft() {
  Serial.println("Turning Left");
  digitalWrite(moteurGaucheForward, LOW);
  digitalWrite(moteurGaucheReverse, HIGH);
  digitalWrite(moteurDroiteForward, HIGH);
  digitalWrite(moteurDroiteReverse, LOW);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(moteurGaucheForward, HIGH);
  digitalWrite(moteurGaucheReverse, LOW);
  digitalWrite(moteurDroiteForward, LOW);
  digitalWrite(moteurDroiteReverse, HIGH);
  analogWrite(ena, 255);
  analogWrite(enb, 255);
}

void stopMotors() {
  Serial.println("Stopping Motors");
  digitalWrite(moteurGaucheForward, LOW);
  digitalWrite(moteurGaucheReverse, LOW);
  digitalWrite(moteurDroiteForward, LOW);
  digitalWrite(moteurDroiteReverse, LOW);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void shoot() {
  Serial.println("Shooting!");
  isShoot = ! isShoot;
  digitalWrite(push, isShoot);
}


void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Open browser at: http://");
  Serial.println(WiFi.localIP());
}
