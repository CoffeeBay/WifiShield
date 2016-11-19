#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define SSID "paradise"
#define PASS "tcm12345"

ESP8266WebServer server(80);

void setup(void) {
  delay(1000);
  Serial.begin(9600);
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
  });

  server.on("/stop", []()
  {
    server.send(200, "text/html", "stop");
    Serial.println("stop");
  });

  server.on("/next", []()
  {
    server.send(200, "text/html", "next");
    Serial.println("next");
  });

  server.on("/prev", []()
  {
    server.send(200, "text/html", "prev");
    Serial.println("prev");
  });

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
