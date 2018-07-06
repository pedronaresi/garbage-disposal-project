//
//  garbage-disposal-project.ino
//
//  Garbage Disposal Project
//
//  Created by Pedro Manhez Naresi on 5/24/18.
//  Copyright © 2018 Pedro Manhez Naresi. All rights reserved.
//

#include <Servo.h>

#define ESPERA_ABERTO 500   // tempo para aguarda entre leituras do sensor, quando aberta a lixeira
#define ESPERA_FECHADO 100  // tempo para aguardar entre leituras do sensor, quando fechada a lixeira
#define TEMPO_PARA_FECHAR 3000 // tempo que a tampa espera para fechar

//Bargraph LEDs pin declaration
const int ledPin1 = 5;
const int ledPin2 = 6;
const int ledPin3 = 7;
const int ledPin4 = 8;
const int ledPin5 = 9;
const int ledPin6 = 10;
const int ledPin7 = 11;
const int ledPin8 = 52;
const int ledPin9 = 4;
const int ledPin10 = 3;

// Limites tampa
int const TAMPA_ABERTA = 125;
int const TAMPA_FECHADA = 55;

// Variaveis de controle do servo
Servo alavanca;          // cria um objeto servo para controlar um servo
int pos = 0;          // variavel para armazenar a posicao dos servos
int lastPos = 0;      // variavel temporaria de posicao do servo
int atraso = 10; // configurar a velocidade de movimentacao da tampa em milisegundos

//Infra Red Sensors pin declaration
const int infraRedPin1 = 24;
const int infraRedPin2 = 21;
const int infraRedPin3 = 22;

//Infra Red Sensors States
int infraRedPin1State = 0;
int infraRedPin2State = 0;
int infraRedPin3State = 0;

// Define pinos que usaremos para o sensor ultrassonico
int const trigPin = 13; // disparo do sensor (trigger)
int const echoPin = 12;  // leitura do eco do sensor (echo)

// Cria variaveis para armazenar a duracao do eco do sensor e a distancia que vamos calcular
int duration, distancia, lastDuration; // Duration will be the input pulse width and distance will be the distance to the obstacle in centimeters

// Define nomes para distancias padrao para as quais faremos a tampa ser acionada
int const ACT_DIST = 10;  //acima disso tampa permanece fechada

// Display 7 segmentos declaracao
const int aLedPin = 30;
const int bLedPin = 31;
const int cLedPin = 32;
const int dLedPin = 33;
const int eLedPin = 34;
const int fLedPin = 35;
const int gLedPin = 35;

//LEDs display 7 segmentos states
int aLedPinState = 0;
int bLedPinState = 0;
int cLedPinState = 0;
int dLedPinState = 0;
int eLedPinState = 0;
int fLedPinState = 0;
int gLedPinState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(infraRedPin1, INPUT);
  pinMode(infraRedPin2, INPUT);
  pinMode(infraRedPin3, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(ledPin6, OUTPUT);
  pinMode(ledPin7, OUTPUT);
  pinMode(ledPin8, OUTPUT);
  pinMode(ledPin9, OUTPUT);
  pinMode(ledPin10, OUTPUT);
  pinMode(aLedPin, OUTPUT);
  pinMode(bLedPin, OUTPUT);
  pinMode(cLedPin, OUTPUT);
  pinMode(dLedPin, OUTPUT);
  pinMode(eLedPin, OUTPUT);
  pinMode(fLedPin, OUTPUT);
  pinMode(gLedPin, OUTPUT);

  alavanca.attach(2);              // Alavanca acoplada no servo do pino PWM 2
  
  pinMode(trigPin, OUTPUT);      // pino de disparo do sensor de distancia
  pinMode(echoPin, INPUT);       // pino de leitura da duracao do eco do sensor
  
  MoveTampa(TAMPA_FECHADA);      // vamos comecar com a tampa da lixeira fechada
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  //Garbage Level Infra Red Sensors
  infraRedPin1State = !digitalRead(infraRedPin1);
  infraRedPin2State = !digitalRead(infraRedPin2);
  infraRedPin3State = !digitalRead(infraRedPin3);

  if (infraRedPin1State == 1 && infraRedPin2State == 1 && infraRedPin3State == 1) {
    // Dez LEDs acessos.
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
  else if (infraRedPin1State == 1 && infraRedPin2State == 1 && infraRedPin3State == 0) {
    // Seis LEDs acessos.
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
  else if (infraRedPin1State == 1 && infraRedPin2State == 0 && infraRedPin3State == 0) {
    // Dois LEDs acessos.
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
  else if (infraRedPin1State == 0 && infraRedPin2State == 0 && infraRedPin3State == 0) {
    // Todos os LEDs apagados.
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
  else {
    // Todos os LEDs apagados.
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

  lastDuration = duration; // armazena ultima leitura do sensor para suavizacao

  //Faz trigger do sensor ultrasonico
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  if(duration < 5) {
    duration = lastDuration; // se vier alguma leitura fora de faixa, preserva a anterior
  }
  if(duration > 5000){
    duration = 5000; // se vier alguma leitura acima de faixa, segura no limite 5000
  }
  
  distancia = (duration/2) / 29.1;    // A distancia eh a metade da duracao, dividida por 29.1 (segundo datasheet do sensor)
  Serial.println(distancia);
      
  delay(1);        // delay entre as leituras, para maior estabilidade
 
     if (distancia <= ACT_DIST && distancia >= 0) {
        MoveTampa(TAMPA_ABERTA);
        delay(ESPERA_ABERTO);
        
    }
    else {
      MoveTampa(TAMPA_FECHADA);
      delay(ESPERA_FECHADO);    
    }

  //seteLedsFechar();
}
void MoveTampa(int posicaoFinal) {
  sweepServo(posicaoFinal, atraso);
}

void sweepServo (int endPos, int sweepDelay){
  int sweepPos, beginPos;

  beginPos = lastPos;
  
  if (beginPos < 0) {
    beginPos = 0;
  }
  if (endPos > 179) {
    endPos = 180;
  }

  if(beginPos > endPos) {
      for (sweepPos = beginPos; sweepPos >= endPos; sweepPos -= 1) // reduz angulo
      {
        alavanca.write(sweepPos);
        delay(sweepDelay);
      } 

  } else {
      for (sweepPos = beginPos; sweepPos <= endPos; sweepPos += 1) 
      {
        alavanca.write(sweepPos);
        delay(sweepDelay);
      }
  }
  lastPos = endPos;
}


/*void seteLedsFechar(void) {
  // Escreve 4
  digitalWrite(aLedPin, LOW);
  digitalWrite(bLedPin, HIGH);
  digitalWrite(cLedPin, HIGH);
  digitalWrite(dLedPin, LOW);
  digitalWrite(eLedPin, LOW);
  digitalWrite(fLedPin, HIGH);
  digitalWrite(gLedPin, HIGH);
  delay(1000);

  // Escreve 3
  digitalWrite(aLedPin, HIGH);
  digitalWrite(bLedPin, HIGH);
  digitalWrite(cLedPin, HIGH);
  digitalWrite(dLedPin, HIGH);
  digitalWrite(eLedPin, LOW);
  digitalWrite(fLedPin, LOW);
  digitalWrite(gLedPin, HIGH);
  delay(1000);

  // Escreve 2
  digitalWrite(aLedPin, HIGH);
  digitalWrite(bLedPin, HIGH);
  digitalWrite(cLedPin, LOW);
  digitalWrite(dLedPin, HIGH);
  digitalWrite(eLedPin, HIGH);
  digitalWrite(fLedPin, LOW);
  digitalWrite(gLedPin, HIGH);
  delay(1000);

  // Escreve 1
  digitalWrite(aLedPin, LOW);
  digitalWrite(bLedPin, HIGH);
  digitalWrite(cLedPin, HIGH);
  digitalWrite(dLedPin, LOW);
  digitalWrite(eLedPin, LOW);
  digitalWrite(fLedPin, LOW);
  digitalWrite(gLedPin, LOW);
  delay(1000);

  // Escreve 0
  digitalWrite(aLedPin, HIGH);
  digitalWrite(bLedPin, HIGH);
  digitalWrite(cLedPin, HIGH);
  digitalWrite(dLedPin, HIGH);
  digitalWrite(eLedPin, HIGH);
  digitalWrite(fLedPin, HIGH);
  digitalWrite(gLedPin, LOW);
}*/
