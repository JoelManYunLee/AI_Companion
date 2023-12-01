#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

#define WIFI_NETWORK "SM-G781W9234"
#define WIFI_PASSWORD "iwza5561"
#define WIFI_TIMEOUT_MS 20000

// Replace with your OpenAI API key
const char* apiKey = "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";

// put function declarations here:
void initWifi(){
  Serial.print("Connecting to WiFi network: ");
  Serial.print(WIFI_NETWORK); 
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS) {
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("failed!");
  } else {
    Serial.print("connected: ");  
    Serial.println(WiFi.localIP());
  }
}

void initChatGPT(){
   // Send request to OpenAI API
  String inputText = "Hello, ChatGPT!";
  String apiUrl = "https://api.openai.com/v1/completions";
  String payload = "{\"prompt\":\"" + inputText + "\",\"max_tokens\":100, \"model\": \"text-davinci-003\"}";

  HTTPClient http;
  http.begin(apiUrl);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + String(apiKey));
  
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode == 200) {
    String response = http.getString();
  
    // Parse JSON response
    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, response);
    String outputText = jsonDoc["choices"][0]["text"];
    Serial.println(outputText);
  } else {
    Serial.printf("Error %i \n", httpResponseCode);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initWifi();
  initChatGPT();
}

void loop() {
  // put your main code here, to run repeatedly:
}