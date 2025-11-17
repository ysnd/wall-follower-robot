#include <NewPing.h>
#define TRIGGER_PIN1    2     
#define ECHO_PIN1       3     
#define TRIGGER_PIN2    11    
#define ECHO_PIN2       10 
#define TRIGGER_PIN3    13    
#define ECHO_PIN3       12  
#define MAX_DISTANCE    200  
int IN1 = 8;
int IN2 = 4; 
int IN3 = 5;    
int IN4 = 7;    
int ENA = 9; 
int ENB = 6;  
int jdepan=0, jkiri=0, jkanan=0;
          


NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);  
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);  
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE);  


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
  jkanan = sonar2.ping_cm();
  jkiri = sonar3.ping_cm();
  delay(50);  
  Serial.print("jarak depan : ");
  Serial.print(jdepan);
  Serial.println();
  Serial.print("jarak kanan : ");
  Serial.print(jkanan);
  Serial.println();
  Serial.print("jarak kiri : ");
  Serial.print(jkiri);
  Serial.println();
  if (jdepan <= 15){
  Stop();
  }
  else if (jkiri >= 15 && jkiri <= 15){
  Maju();
  }
  else if(jkiri <= 15){
  delay(100);
  Kanan();
  delay(500);
  Maju();        
  }  
  else if (jkiri >= 15){
  delay(100);
  Kiri();
  delay(500);
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
  Serial.println("berhenti");
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
 
