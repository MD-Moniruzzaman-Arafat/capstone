#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
#define WIFI_SSID "BUBT FAMILY"
#define WIFI_PASSWORD "Bubt987654321"

// Firebase credentials
#define FIREBASE_HOST "smart-waste-management-cd0e0-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "2dloBbdwGM7hVvC36Q1gSvx0Q5PnxVKtx5PSAPgc"

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Define static GPS coordinates (use these when GPS data is unavailable)
#define STATIC_LATITUDE 23.8107261
#define STATIC_LONGITUDE 90.3560521

// For generating a fake timestamp based on millis() since startup:
unsigned long previousMillis = 0;
unsigned long secondsCounter = 0;

int seconds = 0;
int minutes = 0;
int hours = 0;
int days = 0;

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  delay(100);

  // Connect to Wi-Fi
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ Connected to Wi-Fi");

  // Set up Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  delay(2000);

  // Verify Firebase connection
  if (Firebase.ready()) {
    Serial.println("✅ Connected to Firebase");
  } else {
    Serial.println("❌ Failed to connect to Firebase:");
    Serial.println(firebaseData.errorReason());
  }
}

String getFormattedTimestamp() {
  // Update the fake time based on millis() since startup
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    secondsCounter++;

    // Increment time variables
    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
    }
    if (minutes >= 60) {
      minutes = 0;
      hours++;
    }
    if (hours >= 24) {
      hours = 0;
      days++;
    }
  }
  // Here, we assume an arbitrary start date (e.g., 2025-02-23 00:00:00)
  int year = 2025;
  int month = 2;
  int day = 23 + days;  // Add days to the arbitrary start date
  
  char timestamp[25];
  sprintf(timestamp, "%04d-%02d-%02dT%02d:%02d:%02dZ", year, month, day, hours, minutes, seconds);
  return String(timestamp);
}

void loop() {
  // Ensure Serial data is available (simulate receiving sensor and GPS data)
  if (Serial.available() > 0) {
    delay(100);  // Ensure full data arrival

    // Read sensor and GPS data from Serial
    String distance1Str = Serial.readStringUntil('\n');
    String distance2Str = Serial.readStringUntil('\n');
    String latitudeStr = Serial.readStringUntil('\n');
    String longitudeStr = Serial.readStringUntil('\n');

    // Remove extra spaces or newline characters
    distance1Str.trim();
    distance2Str.trim();
    latitudeStr.trim();
    longitudeStr.trim();

    // Convert values to appropriate data types
    int distance1 = distance1Str.toInt();
    int distance2 = distance2Str.toInt();
    float latitude = latitudeStr.toFloat();
    float longitude = longitudeStr.toFloat();

    // Check if GPS data is valid (not 0.0 and not NaN)
    if (latitude == 0.0 || isnan(latitude) || longitude == 0.0 || isnan(longitude)) {
      Serial.println("\n⚠️ GPS Data Not Available - Using Static Coordinates.");
      latitude = STATIC_LATITUDE;
      longitude = STATIC_LONGITUDE;
    } else {
      Serial.println("\n✅ GPS Data Received.");
    }

    // Get the formatted timestamp
    String timestamp = getFormattedTimestamp();

    // Debugging: Print received values
    Serial.println("\nReceived Data:");
    Serial.println("Distance 1: " + String(distance1));
    Serial.println("Distance 2: " + String(distance2));
    Serial.println("Latitude: " + String(latitude, 6));
    Serial.println("Longitude: " + String(longitude, 6));
    Serial.println("Timestamp: " + timestamp);

    // Prepare JSON for Firebase
    int capacity = 100;    // Example capacity value
    int capacityType = 11; // Example capacity type
    String binKey = "999"; // Unique key for the dustbin

    FirebaseJson json;
    json.set("bin_id", "1111");
    json.set("name", "Real Dustbin");
    json.set("fill_level", distance2);
    json.set("latitude", latitude);
    json.set("longitude", longitude);
    json.set("capacity_type", capacityType);
    json.set("capacity", capacity);
    json.set("data_updated_at", timestamp);  // Using formatted timestamp

    // Send data to Firebase under key "999"
    if (Firebase.updateNode(firebaseData, "/dustbins/" + binKey, json)) {
      Serial.println("\n✅ Data successfully updated in Firebase:");
      String jsonString;
      json.toString(jsonString, true);
      Serial.println(jsonString);
    } else {
      Serial.println("\n❌ Failed to update data in Firebase:");
      Serial.println(firebaseData.errorReason());
    }
  }

  delay(100);  // Short delay before checking Serial again
}
