// #include <Servo.h>          // Include the Servo library
// #include <SoftwareSerial.h> // Include SoftwareSerial for GPS communication
// #include <TinyGPS++.h>      // Include TinyGPS++ library for parsing GPS data

// // Define pins for the first ultrasonic sensor (controls servo)
// const int trigPin1 = 2; // Trig pin for first sensor
// const int echoPin1 = 3; // Echo pin for first sensor

// // Define pins for the second ultrasonic sensor (distance measurement only)
// const int trigPin2 = 4; // Trig pin for second sensor
// const int echoPin2 = 5; // Echo pin for second sensor

// Servo myServo; // Create a Servo object

// // GPS module pins
// static const int RXPin = 6, TXPin = 7;
// static const uint32_t GPSBaud = 9600;
// TinyGPSPlus gps;
// SoftwareSerial ss(RXPin, TXPin);

// void setup()
// {
//   // Set up the pins for the first ultrasonic sensor
//   pinMode(trigPin1, OUTPUT);
//   pinMode(echoPin1, INPUT);

//   // Set up the pins for the second ultrasonic sensor
//   pinMode(trigPin2, OUTPUT);
//   pinMode(echoPin2, INPUT);

//   myServo.attach(9); // Attach the servo to digital pin 9
//   myServo.write(0);  // Initialize the servo at 0 degrees

//   // Initialize serial communications
//   Serial.begin(9600); // Serial for debugging
//   ss.begin(GPSBaud);
// }

// void loop()
// {
//   long duration1, duration2;
//   int distance1, distance2;

//   // Measure distance using the first ultrasonic sensor
//   digitalWrite(trigPin1, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin1, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin1, LOW);

//   duration1 = pulseIn(echoPin1, HIGH);
//   distance1 = duration1 * 0.034 / 2;

//   // Control the servo motor based on the first sensor's distance
//   if (distance1 < 10)
//   {
//     myServo.write(90); // Rotate servo to 180 degrees
//   }
//   else
//   {
//     myServo.write(0); // Rotate servo back to 0 degrees
//   }

//   // Measure distance using the second ultrasonic sensor
//   digitalWrite(trigPin2, LOW);
//   delayMicroseconds(2);
//   digitalWrite(trigPin2, HIGH);
//   delayMicroseconds(10);
//   digitalWrite(trigPin2, LOW);

//   duration2 = pulseIn(echoPin2, HIGH);
//   distance2 = duration2 * 0.034 / 2;

//   // Print distances from both sensors
//   Serial.print("Sensor 1 Distance: ");
//   Serial.print(distance1);
//   Serial.println(" cm");

//   Serial.print("Sensor 2 Distance: ");
//   Serial.print(distance2);
//   Serial.println(" cm");

//   // Read GPS data
//   // while (ss.available() > 0){
//   //   gps.encode(ss.read());
//   //   if (gps.location.isUpdated()){
//   //     Serial.print("Latitude= ");
//   //     Serial.print(gps.location.lat(), 6);
//   //     Serial.print(" Longitude= ");
//   //     Serial.println(gps.location.lng(), 6);
//   //   }
//   // }

//   delay(2000); // Small delay for stability
// }

#include <Servo.h>          // Include the Servo library
#include <SoftwareSerial.h> // Include SoftwareSerial for GPS communication
#include <TinyGPS++.h>      // Include TinyGPS++ library for parsing GPS data

// Define pins for the first ultrasonic sensor (controls servo)
const int trigPin1 = 2; // Trig pin for first sensor
const int echoPin1 = 3; // Echo pin for first sensor

// Define pins for the second ultrasonic sensor (distance measurement only)
const int trigPin2 = 4; // Trig pin for second sensor
const int echoPin2 = 5; // Echo pin for second sensor

Servo myServo; // Create a Servo object

// GPS module pins
static const int RXPin = 6, TXPin = 7;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  // Set up the pins for the first ultrasonic sensor
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  // Set up the pins for the second ultrasonic sensor
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  myServo.attach(9); // Attach the servo to digital pin 9
  myServo.write(0);  // Initialize the servo at 0 degrees

  // Initialize serial communications
  Serial.begin(9600); // Serial for debugging
  ss.begin(GPSBaud);
}

void loop()
{
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);

  // Control the servo motor based on the first sensor's distance
  if (distance1 < 10)
  {
    myServo.write(90); // Rotate servo to 90 degrees
  }
  else
  {
    myServo.write(0); // Rotate servo back to 0 degrees
  }

  // Print distances from both sensors
  // Serial.print("Sensor 1 Distance: ");
  Serial.print(distance1);
  Serial.println(" cm");

  // Serial.print("Sensor 2 Distance: ");
  Serial.print(distance2);
  Serial.println(" cm");

  // Read GPS data
  // while (ss.available() > 0){
  //   gps.encode(ss.read());
  //   if (gps.location.isUpdated()){
  //     Serial.print("Latitude= ");
  //     Serial.print(gps.location.lat(), 6);
  //     Serial.print(" Longitude= ");
  //     Serial.println(gps.location.lng(), 6);
  //   }
  // }

  delay(2000); // Small delay for stability
}

// Function to measure distance using an ultrasonic sensor
int getDistance(int trigPin, int echoPin)
{
  long duration;
  int distance;

  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (int)(duration * 0.034 / 2); // Calculate distance in cm

  // Ensure no negative distances due to timeout
  if (distance <= 0 || distance > 400)
  {                // Add a reasonable upper limit for safety
    distance = -1; // Invalid measurement
  }

  return distance;
}
