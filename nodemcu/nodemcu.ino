#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
#define WIFI_SSID "BUBT FAMILY"
#define WIFI_PASSWORD "Bubt987654321"

// Firebase credentials
#define FIREBASE_HOST "capstone-6769d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "pjdeu2GgEZV41ilJaWLRk8sqM9TQQ2kW6mmzKsw7"

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

// Define static GPS coordinates (use these when GPS data is unavailable)
#define STATIC_LATITUDE 23.8107261
#define STATIC_LONGITUDE 90.3560521

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
  Serial.println("\nConnected to Wi-Fi");

  // Set up Firebase
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  delay(2000);

  // Verify Firebase connection
  if (Firebase.ready()) {
    Serial.println("Connected to Firebase");
  } else {
    Serial.println("Failed to connect to Firebase:");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  // Ensure Serial data is available
  if (Serial.available() > 0) {
    // Wait for data to fully arrive
    delay(100);  // Small delay ensures correct order

    // Read all data as separate lines
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

    // Debugging: Print received values
    Serial.println("\nReceived Data:");
    Serial.println("Distance 1: " + String(distance1));
    Serial.println("Distance 2: " + String(distance2));
    Serial.println("Latitude: " + String(latitude, 6));
    Serial.println("Longitude: " + String(longitude, 6));

    // Prepare JSON for Firebase
    int updatedAt = millis() / 1000;
    FirebaseJson json;
    json.set("distance1", distance1);
    json.set("fill_level", distance2);
    json.set("latitude", latitude);
    json.set("longitude", longitude);
    json.set("name", "Dustbin 1");
    json.set("updated_at", updatedAt);

    // Send data to Firebase
    if (Firebase.updateNode(firebaseData, "/dustbin", json)) {
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
