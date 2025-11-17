#include <NewPing.h>

#define TRIGGER_PIN1    10     // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1       11     // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2    2    // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2       3    // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE    200   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int IN1 = 8;
int IN2 = 4; 
int IN3 = 5;    
int IN4 = 7;    
int ENA = 9; 
int ENB = 6;               

int pwm;

int Upper =100;               
int Lower =45;                
NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE);  // NewPing setup of pins and maximum distance.

void setup() 
{
  Serial.begin(115200);       
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() 
{
  delay(50);
  unsigned int us = sonar1.ping();     // Send ping, get ping time in microseconds (uS).
  int kanan = us / US_ROUNDTRIP_CM;
  unsigned int us2 = sonar2.ping();    .
  int depan = us2 / US_ROUNDTRIP_CM;

  if (kanan>20) {kanan=20;}            .
  else {kanan=kanan;}
 


  if (depan<=7)                        
  {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255 - 100);
  analogWrite(ENB, 100);
  }
  
  else
  {
  int sp = 7;                          // sp = set point, posisi robot harus senantiasa di jarak 7 cm
  int error = sp - kanan;              // mendefinisikan nilai error, selisih antara setpoint dan pembacaan sensor kanan
    
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  int pid = 9*error;                   // Pembobotan nilai PID, Angka 9 adalah konstanta proporsional (Kp)
    
  pwm=sp*10-pid;                       // Pembobotan OUTPUT/pwm hasil perhitungan PID, saya masih belum yakin ini sesuai dengan teori PID
  if(pwm>Upper){pwm=Upper;}            // Angka 10 adalah konstanta yang membuat pwm berada dikisaran angka ratusan/motor bisa berputar
  if(pwm<Lower){pwm=Lower;}
  int ki=pwm;
  
  pwm=sp*10+pid;
  if(pwm>Upper){pwm=Upper;}
  if(pwm<Lower){pwm=Lower;}
  int ka=pwm;
      
  analogWrite(ENA, 255 - ka);
  analogWrite(ENB, 255 - ki);
  }
}
