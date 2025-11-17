#include <NewPing.h>
#define TRIGGER1_PIN  2  // ultrasonik depan.
#define ECHO1_PIN     3  
#define TRIGGER2_PIN  13  // ultrasonik kiri
#define ECHO2_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER3_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO3_PIN     10  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int ENA = 9;
int ENB = 6;
int IN1 = 8;
int IN2 = 4;
int IN3 = 5;
int IN4 = 7;
int jdepan, jkiri, jkanan;

NewPing sonar1(TRIGGER1_PIN, ECHO1_PIN, MAX_DISTANCE);
NewPing sonar2(TRIGGER2_PIN, ECHO2_PIN, MAX_DISTANCE);
NewPing sonar3(TRIGGER3_PIN, ECHO3_PIN, MAX_DISTANCE);

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  jdepan = sonar1.ping_cm();
  jkiri = sonar2.ping_cm();
  jkanan = sonar3.ping_cm();
  Serial.print("depan : ");
  Serial.print(jdepan);
  Serial.println();
  Serial.print("kiri : ");
  Serial.print(jkiri);
  Serial.println();
  Serial.print("kanan : ");
  Serial.print(jkanan);
  Serial.println();
 
 if(jdepan < 10){
  Stop();
  delay(800);
  Mundur(); 
  delay(800);
  Kanan();
  
  }
 else if(jkiri > 15){
   Kiri();
   delay(800);   
 }  
 else if (jkiri < 10) {
   Kanan();
   delay(800);
 }
  else if(jkiri > 15 && jkiri < 10){
  Maju();
 }
} 

void Maju() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.print("maju");
  Serial.println();
}

void Mundur(){
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.print("mundur");
  Serial.println();
}

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.print("stop");
  Serial.println();  

}

void Kanan() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 127);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.print("kanan");
  Serial.println();
}

void Kiri() {
  analogWrite(ENA, 127);
  analogWrite(ENB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);  
  Serial.print("kiri");  
  Serial.println();
}
