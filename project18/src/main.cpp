#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "MORE_ESP32";
const char* password = "123456789";
// Define the LED pin
const int ledPin = 2;  // Often GPIO 2 for built-in LED, check your board's documentation


WebServer server(80);  // HTTP server on port 80

// Function declarations
void handleRoot();
void handleOn();
void handleOff();
void ledON();
void ledOFF();

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point Started with IP: ");
  Serial.println(IP);

  // Configure HTTP routes
  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  
  server.begin();
  Serial.println("HTTP server started");
}



void loop() {
  server.handleClient();
}

// Handlers for HTTP requests
void handleRoot() {
  String html = "<!DOCTYPE html><html><head>"
                "<style>"
                "button {"
                "  width: 200px; height: 100px;"  // Set width and height
                "  font-size: 24px;"             // Increase font size
                "  margin: 10px;"                // Add some space around the buttons
                "  cursor: pointer;"             // Cursor changes to pointer on hover
                "}"
                "</style>"
                "</head><body>"
                "<h1>Hello, this server is working</h1>"
                "<button onclick=\"location.href='/on'\">ON</button>"
                "<button onclick=\"location.href='/off'\">OFF</button>"
                "</body></html>";
  server.send(200, "text/html", html);
}



void handleOn() {
  ledON();
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");  // Redirect to root
}

void handleOff() {
  ledOFF();
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");  // Redirect to root
}

void ledON() {
  Serial.println("LED ON");
  digitalWrite(ledPin, HIGH);  // Turn LED on
}

void ledOFF() {
  Serial.println("LED OFF");
  digitalWrite(ledPin, LOW);  // Turn LED off
}

