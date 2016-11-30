#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "bangul";
const char *password = "qwertyuiop";

ESP8266WebServer server(80);

void handleRoot() {
  server.send ( 200, "text/html", "root" );
}

void setup ( void ) {
  Serial.begin ( 9600 );
  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.println ( "" );
  Serial.print ( "Connected to " );
  Serial.println ( ssid );
  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.on("/play", []()
  {
    server.send(200, "text/html", "play");
    Serial.print("@a");
    Serial.println(server.arg(0));
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
  Serial.println ( "HTTP server started" );
}

void loop ( void ) {
  if (WiFi.status() != WL_CONNECTED) {
    setup();
    delay(5000);
  }

  server.handleClient();
}
