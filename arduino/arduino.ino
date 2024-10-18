const int trigPin = 9;  // Trigger pin of HC-SR04
const int echoPin = 10;  // Echo pin of HC-SR04
long duration;
int distance;

void setup() {
  Serial.begin(9600);  // Start serial communication
  pinMode(trigPin, OUTPUT);  // Set trigPin as OUTPUT
  pinMode(echoPin, INPUT);  // Set echoPin as INPUT
}

void loop() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in cm
  distance = duration * 0.034 / 2;  // Speed of sound is 0.034 cm/us

  // Send distance to NodeMCU via Serial
  Serial.print("Distance: ");
  Serial.println(distance);

  delay(1000);  // Wait for 1 second before the next reading
}
