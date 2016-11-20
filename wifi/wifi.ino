#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define SSID "paradise"
#define PASS "tcm12345"

ESP8266WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("WiFiShield Started!");
  WiFi.begin(SSID, PASS);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []()
  {
    server.send(200, "text/html", "hello world");
    Serial.println("Client Connection");
  });

  server.on("/play", []()
  {
    server.send(200, "text/html", "play");
    String musicIndex = server.arg("musicIndex");
    Serial.print("@a "); 
    Serial.println(musicIndex);
  });

  server.on("/stop", []()
  {
    server.send(200, "text/html", "stop");
    Serial.println("@b");
  });

  server.on("/next", []()
  {
    server.send(200, "text/html", "next");
    Serial.println("@c");
  });

  server.on("/prev", []()
  {
    server.send(200, "text/html", "prev");
    Serial.println("@d");
  });

  server.begin();
  Serial.println("HTTP Server started");
}

void loop() {
  server.handleClient();
}
