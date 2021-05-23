#include <Servo.h>

int numOfLed = 12;  // numOfLed: LED�� ����
Servo leftServo;  // leftServo: ������ ���� ���͸� �ǹ��ϴ� ����
Servo rightServo;  // rightServo: �������� ���� ���͸� �ǹ��ϴ� ����
int evenLedState = LOW;  // evenLedState: ¦�� ���� LED �� ���¸� �ǹ�

void setup() {
  
  for(int i=2; i<numOfLed; i++)  // 2 ~ 11�� ���� ��� LED ������ ������
    pinMode(i,OUTPUT);

  leftServo.attach(12);
  rightServo.attach(13);  // 12, 13�� ���� ���� ���� ������ ������

  leftServo.write(0);
  rightServo.write(180);  // �� ���� ������ ������ �ʱ�ȭ��
}

void loop() {
  int sensorValue = analogRead(A0);

  allLedClear();  // �׻� �����Ҷ� ��� LED�� OFF ���·� ����
  
  if(sensorValue < 100)  // ���� ������ ���� �о�������ν� ���� ���� ��ο� ���� ���� �ٸ��� �����ϵ��� �� �� ����
    performanceStart();
  else 
    performanceStop();
}

void performanceStop(){  // ��Ⱑ ���� �� �����ϴ� �Լ�
  for(int i=2; i<numOfLed-2; i++){  // LED�� �ϳ��� ������
    if(i == 2){  // ó������ �ٸ� ����� ó���ϰ� �������� ������
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

void performanceStart(){  // ��Ⱑ ��ο� �� �����ϴ� �Լ�
  int i = 0;
  int j = 0;  /* i, j : ���� ���� ���踦 ���� ���� ����
                 ex) if i = 180 then j = 0 , if i = 160 then j = 20 */
  int increase = 1;  // increase: 1�̸� ���� i�� �����ϰ� -1�̸� ������

  changeEvenLedState();  // �ʱ⿡ ¦�� ���� LED �� ���´� HIGH�� ������
  
  while(i != -1){
    if(i == 180){  // i�� �����ϴٰ� 180�� �����ϸ� �����ϰ� ����� ¦�� ���� LED �� ���¸� �ٲ���
      increase = increase * -1;
      changeEvenLedState();
    }
    
    j = 180 - i;  // j�� i�� ���� ���� ���踦 ������ ��
    
    leftServo.write(i);
    rightServo.write(j);  // 1��ŭ ���� �Ǵ� �����ϴ� ���� write() �Լ��� ���ڷ� ��� �־��־�� ���Ͱ� õõ�� ���ư��� �� �� ����

    if(i == 90)  // i�� ���� �Ǵ� �����ϴٰ� '90'�� �Ǹ� ¦�� ���� LED �� ���¸� �ٲ���
      changeEvenLedState();
    
    delay(10);  // ���Ͱ� õõ�� ���ư����� �ϱ� ���� �ʿ�

    i = i + increase;  // i ���� 1��ŭ ���� �Ǵ� ���ҽ�Ŵ
  }
}

void changeEvenLedState(){  /* ¦�� ���� LED �� ���¸� Toggle ���ִ� �Լ�
                               ( Ȧ�� ���� LED �� ���´� �ݴ�� ������,
                                  ex: ¦�� ���� HIGH�̸� Ȧ�� ���� LOW�� �� ) */

  evenLedState = !evenLedState;

  for(int a=2; a<numOfLed; a=a+2){  // ¦�� ���� LED �� ���¸� Toggle��
    digitalWrite(a, evenLedState);
  }

  for(int a=3; a<numOfLed; a=a+2){  // Ȧ�� ���� LED �� ���´� �ݴ�� ������
    digitalWrite(a, !evenLedState);
  }
}

void allLedClear(){  // ��� LED�� OFF���ִ� �Լ�
  for(int i=2; i<numOfLed; i++)
    digitalWrite(i,LOW);
}
