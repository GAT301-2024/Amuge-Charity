
#include <WiFi.h>
#include <WebServer.h>

// WiFi Credentials
const char* ssid = "Muhumuza";
const char* password = "79355553";

// WebServer runs on port 80
WebServer server(80);

// LED pins
const int led1 = 33;
const int led2 = 32;
const int led3 = 25;

// Improved HTML Dashboard with Better Styles and Layout
String htmlPage()
{
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>OKELLO VICENT Systems - Smart Lighting</title>
      <style>
          body {
              font-family: Arial, sans-serif;
              background: linear-gradient(to right, #e3f2fd, #f9f9f9);
              margin: 0;
              padding: 0;
              display: flex;
              flex-direction: column;
              align-items: center;
              justify-content: center;
              min-height: 100vh;
              color: #333;
          }
          h1 {
              color: #2c3e50;
              margin-top : 20px;
          }
          h2 {
              color: #34495e;
              margin-bottom: 30px;
          }
          .button-group {
              display: flex;
              flex-direction: row;
              justify-content: center;
              flex-wrap: wrap;
              margin-bottom: 20px;
          }
          .btn {
              padding: 15px 25px;
              margin: 10px;
              font-size: 18px;
              border: none;
              border-radius: 12px;
              cursor: pointer;
              transition: all 0.3s ease;
              min-width: 120px;
              box-shadow: 0 4px 6px rgba(0,0,0,0.1);
          }
          .btn:hover {
              transform: scale(1.05);
              box-shadow: 0 6px 12px rgba(0,0,0,0.2);
          }
          .on {
              background-color: #27ae60;
              color: white;
          }
          .off {
              background-color: #e74c3c;
              color: white;
          }
          footer {
              margin-top: 40px;
              padding: 10px;
              text-align: center;
              font-size: 14px;
              color: #666;
              border-top: 1px solid #ccc;
              width: 100%;
              background: #f1f1f1;
          }
      </style>
  </head>
  <body>
      <h1>AMUGE CHARITY Systems</h1>
      <h2>Intelligent Lighting Dashboard</h2>
      
      <div class="button-group">
          <a href="/led1/on"><button class="btn on">LED 1 ON</button></a>
          <a href="/led1/off"><button class="btn off">LED 1 OFF</button></a>
      </div>
      
      <div class="button-group">
          <a href="/led2/on"><button class="btn on">LED 2 ON</button></a>
          <a href="/led2/off"><button class="btn off">LED 2 OFF</button></a>
      </div>
      
      <div class="button-group">
          <a href="/led3/on"><button class="btn on">LED 3 ON</button></a>
          <a href="/led3/off"><button class="btn off">LED 3 OFF</button></a>
      </div>
      
      <footer>&copy; 2025 AMUGE CHARITY Systems | BYTEBLOOM GAT301</footer>
  </body>
  </html>
  )rawliteral";

  return html;
}


// Handle Routes
void handleRoot() { server.send(200, "text/html", htmlPage()); }

void controlLED(int led, bool state) {
  digitalWrite(led, state ? HIGH : LOW);
  server.send(200, "text/html", htmlPage());
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/", handleRoot);
  server.on("/led1/on", []() { controlLED(led1, true); });
  server.on("/led1/off", []() { controlLED(led1, false); });
  server.on("/led2/on", []() { controlLED(led2, true); });
  server.on("/led2/off", []() { controlLED(led2, false); });
  server.on("/led3/on", []() { controlLED(led3, true); });
  server.on("/led3/off", []() { controlLED(led3, false); });

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
