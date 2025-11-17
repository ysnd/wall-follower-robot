#include <TaskScheduler.h>
#include <NewPing.h>

#define TRIGGER_PIN1    2     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1       3     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2    11    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2       10    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN3    13    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3       12    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE    200   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define INTERVAL_SONAR  500    // Interval for sonar readings in milliseconds

int IN1 = 8;
int IN2 = 4; 
int IN3 = 5;    
int IN4 = 7;    
int ENA = 9; 
int ENB = 6;  
int jdepan = 0, jkiri = 0, jkanan = 0;

Scheduler scheduler;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

void sonar(); // Deklarasi fungsi sonar()

Task sonarTask(INTERVAL_SONAR, TASK_FOREVER, &sonar);

void setup() {
  Serial.begin(115200);      
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  scheduler.init();
  scheduler.addTask(sonarTask);
  sonarTask.enable();
}

void loop() {
  scheduler.execute();
  wallfollowerLogic();
}

void sonar() { // Implementasi fungsi sonar()
  jdepan = sonar1.ping_cm();
  jkanan = sonar2.ping_cm();
  jkiri = sonar3.ping_cm();
  Serial.print("Jarak depan: ");
  Serial.println(jdepan);
  Serial.print("Jarak kanan: ");
  Serial.println(jkanan);
  Serial.print("Jarak kiri: ");
  Serial.println(jkiri);
}

void wallfollowerLogic() {
  if (jdepan <= 15) {
    Stop();
  } else if (jkiri > 15 && jkiri <= 30) {
    Maju();
  } else if (jkiri <= 15) {
    Kanan();
    Maju();
  } else if (jkiri > 30) {
    Kiri();
    Maju();
  }
}

void Mundur() {
  analogWrite(ENA, 127);
  analogWrite(ENB, 127);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Mundur");
}

void Maju() {
  analogWrite(ENA, 127);
  analogWrite(ENB, 127);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Maju");
}

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Berhenti");
}

void Kanan() {
  analogWrite(ENA, 64);
  analogWrite(ENB, 127);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Kanan");
}

void Kiri() {
  analogWrite(ENA, 127);
  analogWrite(ENB, 64);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Kiri");
}
