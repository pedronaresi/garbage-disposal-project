#include <Servo.h>

//Infra Red Sensors pin declaration
const int infraRedPin1 = 1;
const int infraRedPin2 = 2;
const int infraRedPin3 = 3;

//Bargraph LEDs pin declaration
const int ledPin1 = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;
const int ledPin4 = 7;
const int ledPin5 = 8;
const int ledPin6 = 9;
const int ledPin7 = 10;
const int ledPin8 = 11;
const int ledPin9 = 12;
const int ledPin10 = 13;

//Infra Red Sensors States
int infraRedPin1State = 0;
int infraRedPin2State = 0;
int infraRedPin3State = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(infraRedPin1, INPUT);
  pinMode(infraRedPin2, INPUT);
  pinMode(infraRedPin3, INPUT);

}

void loop() {
  //Garbage Level Infra Red Sensors
  infraRedPin1State = digitalRead(infraRedPin1);
  infraRedPin2State = digitalRead(infraRedPin2);
  infraRedPin3State = digitalRead(infraRedPin3);

  if (infraRedPin1State == 1 && infraRedPin2State == 1 && infraRedPin3State == 1){
    //Dez LEDs acessos.
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, HIGH);
    digitalWrite(ledPin6, HIGH);
    digitalWrite(ledPin7, HIGH);
    digitalWrite(ledPin8, HIGH);
    digitalWrite(ledPin9, HIGH);
    digitalWrite(ledPin10, HIGH);
    
  }
  else if (infraRedPin1State == 1 && infraRedPin2State == 1 && infraRedPin3State == 0){
    //Seis LEDs acessos.
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, HIGH);
    digitalWrite(ledPin5, HIGH);
    digitalWrite(ledPin6, HIGH);
    digitalWrite(ledPin7, LOW);
    digitalWrite(ledPin8, LOW);
    digitalWrite(ledPin9, LOW);
    digitalWrite(ledPin10, LOW);
  }
  else if (infraRedPin1State == 1 && infraRedPin2State == 0 && infraRedPin3State == 0){
    //Dois LEDs acessos.
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin6, LOW);
    digitalWrite(ledPin7, LOW);
    digitalWrite(ledPin8, LOW);
    digitalWrite(ledPin9, LOW);
    digitalWrite(ledPin10, LOW);
  }
  else if (infraRedPin1State == 0 && infraRedPin2State == 0 && infraRedPin3State == 0){
    //Todos os LEDs apagados.
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin6, LOW);
    digitalWrite(ledPin7, LOW);
    digitalWrite(ledPin8, LOW);
    digitalWrite(ledPin9, LOW);
    digitalWrite(ledPin10, LOW);
  }
  else{
    //Todos os LEDs apagados.
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);
    digitalWrite(ledPin5, LOW);
    digitalWrite(ledPin6, LOW);
    digitalWrite(ledPin7, LOW);
    digitalWrite(ledPin8, LOW);
    digitalWrite(ledPin9, LOW);
    digitalWrite(ledPin10, LOW);
  }


  //

}
