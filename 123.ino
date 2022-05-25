#include <Servo.h>
int val;
int buzzPin = 9;
int servoPin1 = 10;
int servoPin2 = 11;
int ENA = 5;
int ENB = 6;

int IN1 = 3;
int IN2 = 4;
int IN3 = 7;
int IN4 = 2;
int LASER = 12;
int o = 0;
int i = 0;
int angle = 90;
int sped = 100;
char data[3];

Servo Servo1;
Servo Servo2;
void setup()
{
Serial.begin(9600);
Servo1.attach(servoPin1);
Servo2.attach(servoPin2);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(13, OUTPUT); // зеленый
pinMode(14, OUTPUT); // красный

pinMode(LASER, OUTPUT); // лазер
pinMode(buzzPin, OUTPUT); //пищалка
}
void loop()
{
if (Serial.available())
{
  val = Serial.read();
   if (val == 'A')
    {
      i = 0;
      data[0] = '0';
      data[1] = '0';
      data[2] = '0';
      while(Serial.available() <= 0) {}
      while(Serial.peek() != 'N') 
      {
        delay(3);
        while(Serial.available() <= 0) {}
        data[i] = Serial.read();
        i = i + 1;
      }
      if (i == 1)
        angle = (data[0]-48);
      else if (i == 2)
        angle = ((data[0]-48)*10 + (data[1]-48));
      else
        angle = ((data[0]-48)*100 + (data[1]-48)*10 + (data[2]-48));
      Servo1.write(angle);
      Serial.read();
    }
  if (val == 'C')
    {
      i = 0;
      data[0] = '0';
      data[1] = '0';
      data[2] = '0';
      while(Serial.available() <= 0) {}
      while(Serial.peek() != 'V') 
      {
        delay(3);
        while(Serial.available() <= 0) {}
        data[i] = Serial.read();
        i = i + 1;
      }
      if (i == 1)
        sped = (data[0]-48);
      else if (i == 2)
        sped = ((data[0]-48)*10 + (data[1]-48));
      else
        sped = ((data[0]-48)*100 + (data[1]-48)*10 + (data[2]-48));
      Serial.read();
    }
  if (val == 'B')
    {
      o = 0;
      data[0] = '0';
      data[1] = '0';
      data[2] = '0';
      while(Serial.available() <= 0) {}
      while(Serial.peek() != 'P') 
      {
        delay(3);
        while(Serial.available() <= 0) {}
        data[o] = Serial.read();
        o = o + 1;
      }
      if (o == 1)
        angle = (data[0]-48);
      else if (o == 2)
        angle = ((data[0]-48)*10 + (data[1]-48));
      else
        angle = ((data[0]-48)*100 + (data[1]-48)*10 + (data[2]-48));
      Servo2.write(angle);
      Serial.read();
    }
  if (val == 'W') // W вперёд 
  {
  analogWrite(ENA, sped); // Устанавливаем скорость 1-го мотора
  analogWrite(ENB, sped); // Устанавливаем скорость 2-го мотора
  // Задаём направление для 1-го мотора
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Задаём направление для 2-го мотора
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
  if (val == 'S') // S назад
  {
  analogWrite(ENA, sped); // Устанавливаем скорость 1-го мотора
  analogWrite(ENB, sped); // Устанавливаем скорость 2-го мотора
  // Задаём направление для 1-го мотора
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Задаём направление для 2-го мотора
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }
  if (val == 'L') // L влево
  {
  analogWrite(ENA, sped); // Устанавливаем скорость 1-го мотора
  analogWrite(ENB, sped); // Устанавливаем скорость 2-го мотора
  // Задаём направление для 1-го мотора
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // Задаём направление для 2-го мотора
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  }
  if (val == 'D') // D вправо
  {
  analogWrite(ENA, sped); // Устанавливаем скорость 1-го мотора
  analogWrite(ENB, sped); // Устанавливаем скорость 2-го мотора
  // Задаём направление для 1-го мотора
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // Задаём направление для 2-го мотора
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  }
  // Стоп режим
  // При отпускании клавиш в программе в порт шлется "T"
  if ( val == 'T') // При нажатии клавиши "T"
  {
    // Выводы ENABLE притянуты к минусу, моторы не работают
    digitalWrite(IN2, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(IN1, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(13, LOW);
  }
  if (val == 'U')
  {
    tone(buzzPin, 100);
    digitalWrite(LASER, HIGH);
  }
  if (val == 'I')
  {
    noTone(buzzPin);
    digitalWrite(LASER, LOW);
   }
   if (val == 'Q')
   {
     digitalWrite(14, HIGH);
   }
   if (val == 'Y')
   {
   digitalWrite(14, LOW);
   }  
}
}
