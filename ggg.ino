#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Replace with your actual Wi-Fi credentials
const char* ssid = "Infinix Hot 11 Play";
const char* password = "faith@202";

// Define LED pins
const int led1 = 25;
const int led2 = 26;
const int led3 = 27;

// Web server on port 80
AsyncWebServer server(80);

// Track LED states
bool ledState1 = false;
bool ledState2 = false;
bool ledState3 = false;

void setup() {
  Serial.begin(115200);

  // Set LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  // Ensure LEDs start off
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  // Connect to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Once connected
  Serial.println("\nConnected to WiFi!");
  Serial.print("Access the dashboard at: http://");
  Serial.println(WiFi.localIP());

  // Root route to serve HTML page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", getHTML());
  });

  // Toggle LED route
  server.on("/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("led")) {
      int led = request->getParam("led")->value().toInt();
      toggleLED(led);
    }
    request->send(200, "text/html", getHTML());
  });

  // Start the server
  server.begin();
}

void loop() {
  // Nothing needed here because we use AsyncWebServer
}

// Toggle LED function
void toggleLED(int ledNum) {
  switch (ledNum) {
    case 1:
      ledState1 = !ledState1;
      digitalWrite(led1, ledState1);
      break;
    case 2:
      ledState2 = !ledState2;
      digitalWrite(led2, ledState2);
      break;
    case 3:
      ledState3 = !ledState3;
      digitalWrite(led3, ledState3);
      break;
  }
}

// Return the HTML page
String getHTML() {
  return R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <title>Charity Systems Dashboard</title>
    <style>
      body { font-family: Arial; background: #f4f4f4; text-align: center; }
      h1 { color: #333; }
      .btn { padding: 15px 25px; margin: 10px; font-size: 18px; background: #2196F3; color: white; border: none; border-radius: 5px; cursor: pointer; }
      .footer { margin-top: 30px; font-size: 14px; color: #888; }
    </style>
  </head>
  <body>
    <h1>Charity Systems Lighting Dashboard</h1>
    <button class="btn" onclick="location.href='/toggle?led=1'">Toggle LED 1</button><br>
    <button class="btn" onclick="location.href='/toggle?led=2'">Toggle LED 2</button><br>
    <button class="btn" onclick="location.href='/toggle?led=3'">Toggle LED 3</button>
    <div class="footer">Developed by Charity Systems • Team GAT301</div>
  </body>
  </html>
  )rawliteral";
}
