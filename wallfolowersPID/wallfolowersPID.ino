#include <NewPing.h>
#include <PID_v1.h>

// Set up ultrasonic sensors
NewPing ultrasonic1(2,3,200); // sensor depan
NewPing ultrasonic2(13,12,200); // sensor kiri
NewPing ultrasonic3(11,10,200); // sensor kanan

// Set up motor driver
int enA = 9;
int in1 = 8;
int in2 = 4;
int enB = 6;
int in3 = 5;
int in4 = 7;

int distRight, distLeft, distFront;
double setPoint = 20; // jarak yang diinginkan dari dinding
double input, output;

PID myPID(&input, &output, &setPoint, 2, 5, 0.1, DIRECT);
void setup() {
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
Serial.begin(115200);

myPID.SetMode(AUTOMATIC);
myPID.SetSampleTime(50);
}

void loop() {
// Get distance from ultrasonic sensors
distRight = ultrasonic3.ping_cm();
distLeft = ultrasonic2.ping_cm();
distFront = ultrasonic1.ping_cm();
Serial.print("Distance Right: ");
Serial.print(distRight);
Serial.print("cm Distance Left: ");
Serial.print(distLeft);
Serial.print("cm Distance Front: ");
Serial.print(distFront);
Serial.println("cm");

// Menentukan sensor yang digunakan untuk kontrol PID
if (distRight < distLeft && distRight < distFront) {
input = distRight;
}
else if (distLeft < distRight && distLeft < distFront) {
input = distLeft;
}
else if (distFront < distRight && distFront < distLeft) {
input = distFront;
}
else {
input = distRight; // atau distLeft atau distFront
}

myPID.Compute();

if (output > 0) {
// Move forward
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enA, output);
analogWrite(enB, output);
}
else if (output < 0) {
// Move backward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enA, -output);
analogWrite(enB, -output);
}
else {
// Stop
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(enA, 0);
analogWrite(enB, 0);
}
}