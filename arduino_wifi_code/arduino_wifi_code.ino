#include <SPI.h>
#include <WiFiNINA.h>

char ssid[] = "football";        // your network SSID
char pass[] = "football";        // your network password
int keyIndex = 0;                // network key index number
int status = WL_IDLE_STATUS;

WiFiServer server(80);

// Motor Pins (modify these based on your hardware setup)
int moteurGaucheForward = 5;
int moteurGaucheReverse = 4;
int moteurDroiteReverse = 3;
int moteurDroiteForward = 2;
int push = 12;
int enb = 9;
int ena = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(moteurGaucheForward, OUTPUT);
  pinMode(moteurGaucheReverse, OUTPUT);
  pinMode(moteurDroiteReverse, OUTPUT);
  pinMode(moteurDroiteForward, OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(push,OUTPUT);
  
  digitalWrite(push,HIGH);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true);
  }

  Serial.print("Creating access point named: ");
  Serial.println(ssid);
  status = WiFi.beginAP(ssid, pass);
  if (status != WL_AP_LISTENING) {
    Serial.println("Creating access point failed");
    while (true);
  }

  delay(10000);
  server.begin();
  printWiFiStatus();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("<html><body>");
            client.print("<h1>Robot Controller</h1>");
            client.print("<script>");
            client.print("document.addEventListener('keydown', function(e) {");
            client.print("  var action = ''; ");
            client.print("  if (e.key === 'w') action = '/forward';");
            client.print("  if (e.key === 's') action = '/backward';");
            client.print("  if (e.key === 'a') action = '/left';");
            client.print("  if (e.key === 'd') action = '/right';");
            client.print("  if (e.key === 'e') action = '/shoot';");
            client.print("  if (action !== '') { var xhr = new XMLHttpRequest(); xhr.open('GET', action, true); xhr.send(); }");
            client.print("});");
            client.print("document.addEventListener('keyup', function(e) {");
            client.print("  var xhr = new XMLHttpRequest(); xhr.open('GET', '/stop', true); xhr.send();");
            client.print("});");
            client.print("</script>");
            client.print("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

        if (currentLine.startsWith("GET /forward?speed=")) {
          String speedStr = currentLine.substring(currentLine.indexOf("=") + 1);
          int speed = speedStr.toInt();
          moveBackward(speed);
        }
        if (currentLine.startsWith("GET /backward?speed=")) {
          String speedStr = currentLine.substring(currentLine.indexOf("=") + 1);
          int speed = speedStr.toInt();
          moveForward(speed);
        }
        if (currentLine.startsWith("GET /left?speed=")) {
          String speedStr = currentLine.substring(currentLine.indexOf("=") + 1);
          int speed = speedStr.toInt();
          turnLeft(speed);
        }
        if (currentLine.startsWith("GET /right?speed=")) {
          String speedStr = currentLine.substring(currentLine.indexOf("=") + 1);
          int speed = speedStr.toInt();
          turnRight(speed);
        }
        if (currentLine.endsWith("GET /stop")) {
          stopMotors();
        }
        if (currentLine.endsWith("GET /shoot")) {
          shoot();
        }
      }
    }
    client.stop();
  }
}

void moveForward(int speed) {
  digitalWrite(moteurGaucheForward, HIGH);
  digitalWrite(moteurGaucheReverse, LOW);
  digitalWrite(moteurDroiteReverse, HIGH);
  digitalWrite(moteurDroiteForward, LOW);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void moveBackward(int speed) {
  digitalWrite(moteurGaucheForward, LOW);
  digitalWrite(moteurGaucheReverse, HIGH);
  digitalWrite(moteurDroiteReverse, LOW);
  digitalWrite(moteurDroiteForward, HIGH);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void turnLeft(int speed) {
  digitalWrite(moteurGaucheForward, LOW);
  digitalWrite(moteurGaucheReverse, HIGH);
  digitalWrite(moteurDroiteReverse, HIGH);
  digitalWrite(moteurDroiteForward, LOW);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void turnRight(int speed) {
  digitalWrite(moteurGaucheForward, HIGH);
  digitalWrite(moteurGaucheReverse, LOW);
  digitalWrite(moteurDroiteReverse, LOW);
  digitalWrite(moteurDroiteForward, HIGH);
  analogWrite(ena, speed);
  analogWrite(enb, speed);
}

void stopMotors() {
  digitalWrite(moteurGaucheForward, LOW);
  digitalWrite(moteurGaucheReverse, LOW);
  digitalWrite(moteurDroiteReverse, LOW);
  digitalWrite(moteurDroiteForward, LOW);
  digitalWrite(push,HIGH);
  analogWrite(ena, 0);
  analogWrite(enb, 0);
}

void shoot() {
  digitalWrite(push, LOW);
  //digitalWrite(push,HIGH);
}

void printWiFiStatus() {
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
