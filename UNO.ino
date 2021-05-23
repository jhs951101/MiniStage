#include <Servo.h>

int numOfLed = 12;  // numOfLed: LED의 갯수
Servo leftServo;  // leftServo: 왼쪽의 서보 모터를 의미하는 변수
Servo rightServo;  // rightServo: 오른쪽의 서보 모터를 의미하는 변수
int evenLedState = LOW;  // evenLedState: 짝수 번의 LED 핀 상태를 의미

void setup() {
  
  for(int i=2; i<numOfLed; i++)  // 2 ~ 11번 핀을 모두 LED 핀으로 지정함
    pinMode(i,OUTPUT);

  leftServo.attach(12);
  rightServo.attach(13);  // 12, 13번 핀을 서보 모터 핀으로 지정함

  leftServo.write(0);
  rightServo.write(180);  // 두 서보 모터의 각도를 초기화함
}

void loop() {
  int sensorValue = analogRead(A0);

  allLedClear();  // 항상 시작할때 모든 LED를 OFF 상태로 만듬
  
  if(sensorValue < 100)  // 조도 센서의 값을 읽어들임으로써 밝을 때랑 어두울 때랑 서로 다르게 동작하도록 할 수 있음
    performanceStart();
  else 
    performanceStop();
}

void performanceStop(){  // 밝기가 밝을 때 동작하는 함수
  for(int i=2; i<numOfLed-2; i++){  // LED를 하나씩 깜빡임
    if(i == 2){  // 처음에만 다른 명령을 처리하고 나머지는 동일함
      digitalWrite(numOfLed-3,LOW);
      digitalWrite(i,HIGH);
    }
    else{
      digitalWrite(i-1,LOW);
      digitalWrite(i,HIGH);
    }
    delay(300);
  }
}

void performanceStart(){  // 밝기가 어두울 때 동작하는 함수
  int i = 0;
  int j = 0;  /* i, j : 서로 반의 관계를 가진 보조 변수
                 ex) if i = 180 then j = 0 , if i = 160 then j = 20 */
  int increase = 1;  // increase: 1이면 변수 i가 증가하고 -1이면 감소함

  changeEvenLedState();  // 초기에 짝수 번의 LED 핀 상태는 HIGH로 지정함
  
  while(i != -1){
    if(i == 180){  // i가 증가하다가 180에 도달하면 감소하게 만들고 짝수 번의 LED 핀 상태를 바꿔줌
      increase = increase * -1;
      changeEvenLedState();
    }
    
    j = 180 - i;  // j는 i와 서로 반의 관계를 갖도록 함
    
    leftServo.write(i);
    rightServo.write(j);  // 1만큼 증가 또는 감소하는 값을 write() 함수의 인자로 계속 넣어주어야 모터가 천천히 돌아가게 할 수 있음

    if(i == 90)  // i가 증가 또는 감소하다가 '90'이 되면 짝수 번의 LED 핀 상태를 바꿔줌
      changeEvenLedState();
    
    delay(10);  // 모터가 천천히 돌아가도록 하기 위해 필요

    i = i + increase;  // i 값을 1만큼 증가 또는 감소시킴
  }
}

void changeEvenLedState(){  /* 짝수 번의 LED 핀 상태를 Toggle 해주는 함수
                               ( 홀수 번의 LED 핀 상태는 반대로 지정됨,
                                  ex: 짝수 번이 HIGH이면 홀수 번은 LOW가 됨 ) */

  evenLedState = !evenLedState;

  for(int a=2; a<numOfLed; a=a+2){  // 짝수 번의 LED 핀 상태를 Toggle함
    digitalWrite(a, evenLedState);
  }

  for(int a=3; a<numOfLed; a=a+2){  // 홀수 번의 LED 핀 상태는 반대로 지정함
    digitalWrite(a, !evenLedState);
  }
}

void allLedClear(){  // 모든 LED를 OFF해주는 함수
  for(int i=2; i<numOfLed; i++)
    digitalWrite(i,LOW);
}
