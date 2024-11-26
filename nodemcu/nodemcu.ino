// #include <ESP8266WiFi.h>
// #include <FirebaseESP8266.h>

// // Wi-Fi credentials
// #define WIFI_SSID "Arafat"
// #define WIFI_PASSWORD "20212203007"

// // Firebase credentials
// #define FIREBASE_HOST "capstone-6769d-default-rtdb.firebaseio.com"  // Without "https://"
// #define FIREBASE_AUTH "pjdeu2GgEZV41ilJaWLRk8sqM9TQQ2kW6mmzKsw7"

// // Firebase objects
// FirebaseData firebaseData;
// FirebaseAuth auth;
// FirebaseConfig config;

// void setup() {
//   Serial.begin(9600); // Initialize serial communication for debugging

//   // Connect to Wi-Fi
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.println("Connected to Wi-Fi");

//   // Set up Firebase configuration
//   config.host = FIREBASE_HOST;
//   config.signer.tokens.legacy_token = FIREBASE_AUTH;

//   // Begin Firebase connection
//   Firebase.begin(&config, &auth);
//   Firebase.reconnectWiFi(true);

//   // Check Firebase connection
//   if (Firebase.ready()) {
//     Serial.println("Connected to Firebase");
//   } else {
//     Serial.println("Failed to connect to Firebase");
//   }
// }

// void loop() {
//   // Generate random data for simulation
//   int distance = random(1, 200); // Simulate distance in cm (1-200 cm)
//   float latitude = 16.43972 + (random(-500, 500) / 10000.0); // Simulate latitude change
//   float longitude = 16.43972 + (random(-500, 500) / 10000.0); // Simulate longitude change
//   int updatedAt = millis() / 1000; // Current time in seconds since startup

//   // Create Firebase JSON object
//   FirebaseJson json;

//   // Add data to JSON object
//   json.set("fill_level", distance);       // Simulate fill level
//   json.set("latitude", latitude);        // Simulate latitude
//   json.set("longitude", longitude);      // Simulate longitude
//   json.set("name", "Dustbin 1");         // Static name
//   json.set("updated_at", updatedAt);     // Simulate last update time

//   // Send JSON object to Firebase at the "/dustbin" path
//   if (Firebase.updateNode(firebaseData, "/dustbin", json)) {
//     Serial.println("Data updated in Firebase:");
//     String jsonString;
//     json.toString(jsonString, true);
//     Serial.println(jsonString); // Print JSON for debugging
//   } else {
//     Serial.println("Failed to update data in Firebase");
//     Serial.println(firebaseData.errorReason());
//   }

//   delay(2000); // Wait for 2 seconds before the next update
// }

// #include <ESP8266WiFi.h>
// #include <FirebaseESP8266.h>

// // Wi-Fi credentials
// #define WIFI_SSID "Arafat"
// #define WIFI_PASSWORD "20212203007"

// // Firebase credentials
// #define FIREBASE_HOST "capstone-6769d-default-rtdb.firebaseio.com"  // Without "https://"
// #define FIREBASE_AUTH "pjdeu2GgEZV41ilJaWLRk8sqM9TQQ2kW6mmzKsw7"

// // Firebase objects
// FirebaseData firebaseData;
// FirebaseAuth auth;
// FirebaseConfig config;

// void setup() {
//   Serial.begin(9600); // Initialize serial communication for debugging

//   // Connect to Wi-Fi
//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//   Serial.print("Connecting to Wi-Fi");
//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }
//   Serial.println();
//   Serial.println("Connected to Wi-Fi");

//   // Set up Firebase configuration
//   config.host = FIREBASE_HOST;
//   config.signer.tokens.legacy_token = FIREBASE_AUTH;

//   // Begin Firebase connection
//   Firebase.begin(&config, &auth);
//   Firebase.reconnectWiFi(true);

//   // Check Firebase connection
//   if (Firebase.ready()) {
//     Serial.println("Connected to Firebase");
//   } else {
//     Serial.println("Failed to connect to Firebase");
//   }
// }

// void loop() {
//   // Check if there is incoming data from the Arduino
//   if (Serial.available() > 0) {
//     // Read the incoming distance data
//     String distance1Str = Serial.readStringUntil('\n'); // Read distance1 data
//     String distance2Str = Serial.readStringUntil('\n'); // Read distance2 data

//     // Debugging: Print received data
//     Serial.print("Received distance1: ");
//     Serial.println(distance1Str);
//     Serial.print("Received distance2: ");
//     Serial.println(distance2Str);

//     // Remove any extra spaces or newlines
//     distance1Str.trim();
//     distance2Str.trim();

//     // Convert the distance values from String to integers
//     int distance1 = distance1Str.toInt();
//     int distance2 = distance2Str.toInt();

//     // Debugging: Print the parsed integer values
//     Serial.print("Parsed distance1: ");
//     Serial.println(distance1);
//     Serial.print("Parsed distance2: ");
//     Serial.println(distance2);

//     // Handle invalid data: If distance1 or distance2 are invalid, skip the loop
//     if (distance1 == 0 && distance1Str != "0") {
//       Serial.println("Invalid distance1 data received");
//       return; // Skip the rest of the loop if data is invalid
//     }
//     if (distance2 == 0 && distance2Str != "0") {
//       Serial.println("Invalid distance2 data received");
//       return; // Skip the rest of the loop if data is invalid
//     }

//     // Simulate other data (latitude, longitude, updated_at)
//     float latitude = 16.43972 + (random(-500, 500) / 10000.0); // Simulated latitude
//     float longitude = 16.43972 + (random(-500, 500) / 10000.0); // Simulated longitude
//     int updatedAt = millis() / 1000; // Current time in seconds since startup

//     // Create Firebase JSON object
//     FirebaseJson json;

//     // Add the sensor data to the JSON object
//     json.set("fill_level", distance1);       // Send distance1 as the fill level
//     json.set("distance2", distance2);       // Send distance2
//     json.set("latitude", latitude);        // Simulated latitude
//     json.set("longitude", longitude);      // Simulated longitude
//     json.set("name", "Dustbin 1");         // Static name
//     json.set("updated_at", updatedAt);     // Last update time

//     // Send JSON object to Firebase at the "/dustbin" path
//     if (Firebase.updateNode(firebaseData, "/dustbin", json)) {
//       Serial.println("Data updated in Firebase:");
//       String jsonString;
//       json.toString(jsonString, true);
//       Serial.println(jsonString); // Print the JSON data for debugging
//     } else {
//       Serial.println("Failed to update data in Firebase");
//       Serial.println(firebaseData.errorReason());
//     }
//   }

//   delay(2000); // Wait for 2 seconds before the next update
// }

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
#define WIFI_SSID "Fenian"
#define WIFI_PASSWORD "12345679"

// Firebase credentials
#define FIREBASE_HOST "capstone-6769d-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "pjdeu2GgEZV41ilJaWLRk8sqM9TQQ2kW6mmzKsw7"

// Firebase objects
FirebaseData firebaseData;
FirebaseAuth auth;
FirebaseConfig config;

void setup()
{
  Serial.begin(9600); // Initialize serial communication for debugging

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
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
  if (Firebase.ready())
  {
    Serial.println("Connected to Firebase");
  }
  else
  {
    Serial.println("Failed to connect to Firebase");
    Serial.println(firebaseData.errorReason());
  }
}

void loop()
{
  // Check if there is incoming data from the Arduino
  if (Serial.available() > 0)
  {
    // Read the incoming distance data
    String distance1Str = Serial.readStringUntil('\n');
    String distance2Str = Serial.readStringUntil('\n');

    // Debugging: Print received data
    Serial.print("Received distance1: ");
    Serial.println(distance1Str);
    Serial.print("Received distance2: ");
    Serial.println(distance2Str);

    // Remove any extra spaces or newlines
    distance1Str.trim();
    distance2Str.trim();

    // Convert the distance values from String to integers
    int distance1 = distance1Str.toInt();
    int distance2 = distance2Str.toInt();

    // Debugging: Print the parsed integer values
    Serial.print("Parsed distance1: ");
    Serial.println(distance1);
    Serial.print("Parsed distance2: ");
    Serial.println(distance2);

    // Handle invalid data: If distance1 or distance2 are invalid, skip the loop
    // if (distance1 == 0 && distance1Str != "0") {
    //   Serial.println("Invalid distance1 data received");
    //   return; // Skip the rest of the loop if data is invalid
    // }
    // if (distance2 == 0 && distance2Str != "0") {
    //   Serial.println("Invalid distance2 data received");
    //   return; // Skip the rest of the loop if data is invalid
    // }

    // Simulate other data (latitude, longitude, updated_at)
    float latitude = 16.43972 + (random(-500, 500) / 10000.0);  // Simulated latitude
    float longitude = 16.43972 + (random(-500, 500) / 10000.0); // Simulated longitude
    int updatedAt = millis() / 1000;                            // Current time in seconds since startup

    // Create Firebase JSON object
    FirebaseJson json;

    // Add the sensor data to the JSON object
    json.set("fill_level", distance2Str); // Send distance1 as the fill level
    // json.set("distance2", distance2);       // Send distance2
    json.set("latitude", latitude);    // Simulated latitude
    json.set("longitude", longitude);  // Simulated longitude
    json.set("name", "Dustbin 1");     // Static name
    json.set("updated_at", updatedAt); // Last update time

    // Send JSON object to Firebase at the "/dustbin" path
    if (Firebase.updateNode(firebaseData, "/dustbin", json))
    {
      Serial.println("Data updated in Firebase:");
      String jsonString;
      json.toString(jsonString, true);
      Serial.println(jsonString); // Print the JSON data for debugging
    }
    else
    {
      Serial.println("Failed to update data in Firebase");
      Serial.println(firebaseData.errorReason());
    }
  }

  delay(2000); // Wait
}
