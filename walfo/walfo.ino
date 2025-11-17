#include <NewPing.h>

#define SONAR_NUM 2             //define Number of ultrasonic sensor used
#define MAX_DISTANCE 800            //Max distance between the object and robot
#define PING_INTERVAL 33           
#define trigPin1  2                  // define pin connections for sensor and motor
#define echoPin1 3
#define trigPin2 13
#define echoPin2 12
int IN1 = 8;
int IN2 = 4; 
int IN3 = 5;    
int IN4 = 7;    
int ENA = 9; 
int ENB = 6;

int rangeFront = 0;
int rangeWall  = 0;

NewPing sonar[SONAR_NUM] = {                                // Define a Newping array to measure the distance
  NewPing(trigPin1, echoPin1, MAX_DISTANCE),
  NewPing(trigPin2, echoPin2, MAX_DISTANCE)
};
void setup()               // setup function to make pin configuration to define whether it is input or output
{
  int i;
  Serial.begin (115200);
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  digitalWrite(trigPin1, LOW);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  digitalWrite(trigPin2, LOW);
}

int toCloseWall = 1800;           //Initialze and define the values for distance between wall and robot
int toFarWall = 2500;
int toCloseFront = 1000;

void loop()
{
Main:
  rangeFront = readRangeFront();  // Read the sensor value by the function call
  Serial.print(rangeFront);          
  Serial.print(" Front");
  Serial.println();
  rangeWall = readRangeWall();
  Serial.print(rangeWall);
  Serial.print(" Wall");
  Serial.println(); 
  if (rangeFront <= 400)         //As the sensor value reads the small values we are manipulating to high values
  {
    rangeFront = 3000;
  }
  if(rangeWall <= 400)
  {
    rangeWall = 3000;
  }

 if (rangeFront < toCloseFront)  //Condition to check whether front sensor is close to robot
 {
    delay(500);
    drive_backward();
    delay(500);
    Serial.print(" Drive Back");
    //turn_right();
    Serial.print(" Right Turn");
    Serial.println();
    delay(800);
    drive_forward();
    turn_right();
    delay(1700);
    goto Main;   
  } 
 
  if(rangeWall > toCloseWall && rangeWall < toFarWall) //condition to check distance measured by front and side sensor is maintained correctly
  {
    drive_forward();
    Serial.print(" Drive Forward");
    Serial.println();
    goto Main;
  } 

  if (rangeWall < toCloseWall)                       //condition to check side wall is close to robot
  {
    delay(100);
    //turn_left();
    turn_right();
    delay(500);
    Serial.print(" Turn Left");
    drive_forward();
    Serial.print(" Drive Forward");
    Serial.println();
    goto Main;
  }

  if (rangeWall > toFarWall)                         //condition to check robot is far from side wall
  {
    delay(100);
    //turn_right();
    turn_left();
    Serial.print(" Turn Right");
    delay(500);
    drive_forward();
    Serial.print(" Drive Forward");
    Serial.println();
    goto Main;
  } 
}


void motor_stop()                                  // function to stop the robot
{   
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


void drive_forward()                               // function to drive the robot forward
{   
  analogWrite(ENA, 128);
  analogWrite(ENB, 128);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void drive_backward()                             // function to drive the robot backward
{ 
  analogWrite(ENA, 128);
  analogWrite(ENB, 128);  
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turn_left()                                  // function to turn the robot left
{  
  analogWrite(ENA, 128);
  analogWrite(ENB, 128);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void turn_right()                                     //function to turn the robot right
{
  analogWrite(ENA, 128);
  analogWrite(ENB, 128);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

int readRangeFront()                                 //function to read the front sensor value
{
  delay(50);
  unsigned rangeFront = sonar[0].ping();
  sonar[0].timer_stop();
  return rangeFront;
}
int readRangeWall()                                 // function to read the left sensor value
{
  delay(50);
  unsigned rangeWall = sonar[1].ping();
  sonar[1].timer_stop();
  return rangeWall;
}
