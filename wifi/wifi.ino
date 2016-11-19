#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Wire.h>


#define SSID "paradise"
#define PASS "tcm12345"

SoftwareSerial toArduinoSerial(2, 3); // RX, TX

ESP8266WebServer server(80);

void setup(void) {
  toArduinoSerial.begin(115200);
  Serial.begin(115200);
  Wire.begin();
  delay(1000);
  
  toArduinoSerial.println("start");
  Serial.println("start");
  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("SoftAPIP : ");
  Serial.println(myIP);

  server.on("/", []()
  {
    server.send(200, "text/html", "hello world");
    Serial.println("Client Connection");
  });

  server.on("/play", []()
  {
    server.send(200, "text/html", "play");
    String musicIndex = server.arg("musicIndex");
    Serial.print("play "); 
    Serial.println(musicIndex);
    toArduinoSerial.print("play "); 
    toArduinoSerial.println(musicIndex);

    Wire.beginTransmission(4);
    Wire.write("play ");
//    Wire.write(musicIndex);
    Wire.endTransmission();
  });

  server.on("/stop", []()
  {
    server.send(200, "text/html", "stop");
    Serial.println("stop");
    toArduinoSerial.println("stop");

    Wire.beginTransmission(4);
    Wire.write("stop");
    Wire.endTransmission();
  });

  server.on("/next", []()
  {
    server.send(200, "text/html", "next");
    Serial.println("next");
    toArduinoSerial.println("next");
  });

  server.on("/prev", []()
  {
    server.send(200, "text/html", "prev");
    Serial.println("prev");
    toArduinoSerial.println("prev");
  });

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
