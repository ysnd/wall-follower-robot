#include <TaskScheduler.h>

// Pin definitions
#define trigPin 2
#define echoPin 3
int IN1 = 8;
int IN2 = 4;
int IN3 = 5;
int IN4 = 7;
int ENA = 9;
int ENB = 6;

long duration;
float distance;
char command = 'S'; // Default command is to stop

// TaskScheduler
Scheduler runner;

void measureDistance();
Task task1(500, TASK_FOREVER, &measureDistance); // Measure distance every 500 milliseconds

void serialControl();
Task task2(50, TASK_FOREVER, &serialControl); // Check for serial commands every 50 milliseconds

void setup() {
  // Set all the motor control pins to outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start the serial communication
  Serial.begin(9600);

  // Add tasks to scheduler
  runner.init();
  runner.addTask(task1);
  runner.addTask(task2);
  task1.enable();
  task2.enable();
}

void loop() {
  runner.execute();
}

void measureDistance() {
  // Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echoPin, return the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distance = (duration * 0.034) / 2;

  // Send the distance to the serial port
  Serial.println(distance);
}

void serialControl() {
  // Read the command from the serial port
  if (Serial.available() > 0) {
    command = Serial.read();
  }

  // Control the motor based on the command
  switch (command) {
    case 'F':
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 255); // Set maximum speed
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 255); // Set maximum speed
      break;
    case 'B':
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      analogWrite(ENA, 255); // Set maximum speed
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      analogWrite(ENB, 255); // Set maximum speed
      break;
    case 'S':
    default:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      analogWrite(ENA, 0);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
      analogWrite(ENB, 0);
      break;
  }
}
