#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
#define WIFI_SSID "Arafat"
#define WIFI_PASSWORD "20212203007"

// Firebase credentials
#define FIREBASE_HOST "capstone-6769d-default-rtdb.firebaseio.com"  // Without "https://"
#define FIREBASE_AUTH "pjdeu2GgEZV41ilJaWLRk8sqM9TQQ2kW6mmzKsw7"

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void setup() {
  Serial.begin(9600);            // Initialize serial communication with Arduino
  
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");

  // Set up Firebase configuration
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  // Begin Firebase connection
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  // Check Firebase connection
  if (Firebase.ready()) {
    Serial.println("Connected to Firebase");
  } else {
    Serial.println("Failed to connect to Firebase");
  }
}

void loop() {
  if (Serial.available() > 0) {
    String distance = Serial.readStringUntil('\n');  // Read distance data from Arduino
    Serial.println(distance);
    
  FirebaseJson json;

  // Update specific properties of the JSON object
  json.set("fill_level", distance);  // Simulate temperature change
  json.set("latitude", 16.43972 + random(0, 10));      // Simulate humidity change
  json.set("longitude", 16.43972 + random(0, 10));      // Simulate humidity change
  json.set("name", "hi");      // Simulate humidity change
  json.set("updated_at", 10);      // Simulate humidity change
  

  // Send the updated JSON object to Firebase at the "/sensor" path
  if (Firebase.updateNode(firebaseData, "/dustbin", json)) {
    Serial.println("Object properties updated in Firebase");
  } else {
    Serial.println("Failed to update object properties");
    Serial.println(firebaseData.errorReason());
  }

  // Delay before the next update
  delay(2000);
  }
}
