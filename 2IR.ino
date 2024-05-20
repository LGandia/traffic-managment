const int Ir1 = 8; // First IR sensor pin INCREASE
const int Ir2 = 11; // Second IR sensor pin DECREASE
const int Ir3 = 12; // Third IR sensor pin INCREASE
const int Ir4 = 9; // Fourth IR sensor pin DECREASE

int green1 = 5;
int red2 = 4; // first set of traffic lights
int green2 = 3;
int red1 = 2; // second set of traffic lights
int carCount1 = 0;
int carCount2 = 0;
int lightChange = 0;
bool carDetected1 = false; // Variable to track if a car has been detected by sensor 1
bool carDetected2 = false; // Variable to track if a car has been detected by sensor 2
bool carDetected3 = false; // Variable to track if a car has been detected by sensor 3
bool carDetected4 = false; // Variable to track if a car has been detected by sensor 4

unsigned long lastChange = 0;

void setup() {
  pinMode(Ir1, INPUT);
  pinMode(Ir2, INPUT);
  pinMode(Ir3, INPUT);
  pinMode(Ir4, INPUT);
  pinMode(green1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(green2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val1 = digitalRead(Ir1); // Read sensor 1
  int val2 = digitalRead(Ir2); // Read sensor 2
  int val3 = digitalRead(Ir3); // Read sensor 3
  int val4 = digitalRead(Ir4); // Read sensor 4

  if (val1 == LOW && !carDetected1) { // If sensor 1 is blocked and no car has been detected by sensor 1
    carDetected1 = true; // Set carDetected1 to true
    carCount1++; // Increment the count
    Serial.print("Cars 1: ");
    Serial.println(carCount1);
    delay(500); // Delay to prevent counting multiple times for the same car
  }

  if (val2 == LOW && !carDetected2) { // If sensor 2 is blocked and no car has been detected by sensor 2
    carDetected2 = true; // Set carDetected2 to true
    if (carCount1 > 0) { // Check if count is greater than 0 before decrementing
      carCount1--; // Decrement the count
      Serial.print("Cars 1: "); 
      Serial.println(carCount1);
    } else {
      Serial.println("Count already at 0! Lane 1"); // Display message when count is already at 0
    }
    delay(500); // Delay to prevent counting multiple times for the same car
  }

  if (val3 == LOW && !carDetected3) { // If sensor 3 is blocked and no car has been detected by sensor 3
    carDetected3 = true; // Set carDetected3 to true
    carCount2++; // Increment the count
    Serial.print("Cars 2: ");
    Serial.println(carCount2);
    delay(500); // Delay to prevent counting multiple times for the same car
  }

  if (val4 == LOW && !carDetected4) { // If sensor 4 is blocked and no car has been detected by sensor 4
    carDetected4 = true; // Set carDetected4 to true
    if (carCount2 > 0) { // Check if count is greater than 0 before decrementing
      carCount2--; // Decrement the count
      Serial.print("Cars 2: ");
      Serial.println(carCount2);
    } else {
      Serial.println("Count already at 0! Lane 2"); // Display message when count is already at 0
    }
    delay(1000); // Delay to prevent counting multiple times for the same car
  }

  // Check if sensor 1 is unblocked after delay
  if (carDetected1 && val1 == HIGH) {
    carDetected1 = false; // Reset carDetected1
  }

  // Check if sensor 2 is unblocked after delay
  if (carDetected2 && val2 == HIGH) {
    carDetected2 = false; // Reset carDetected2
  }

  // Check if sensor 3 is unblocked after delay
  if (carDetected3 && val3 == HIGH) {
    carDetected3 = false; // Reset carDetected3
  }

  // Check if sensor 4 is unblocked after delay
  if (carDetected4 && val4 == HIGH) {
    carDetected4 = false; // Reset carDetected4
  }

  lightChange++;
  if (lightChange > 500){
    changeLight();
    lightChange = 0;
  }

}

void changeLight(){
  if (carCount1 > carCount2){
      digitalWrite(green1,HIGH);
      digitalWrite(red2,HIGH);
      digitalWrite(red1, LOW);
      digitalWrite(green2, LOW);

  }
  else{
      digitalWrite(green1,LOW);
      digitalWrite(red2,LOW);
      digitalWrite(red1, HIGH);
      digitalWrite(green2, HIGH);
  }
  lastChange = millis(); // Update thetime of the last light change
}
