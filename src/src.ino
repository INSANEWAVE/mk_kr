#include <GyverEncoder.h> //Библиотека для гибкого управления энкодером
#include <Servo.h> //Библиотека для работы с сервоприводами и бесколлекторными моторами
#include <Shifty.h> //Библиотека для сдвиговых регистров - оптимизация кода

#define clock 13 
#define data 12 
#define latch 10
#define sensorPin A0 // Пин фоторезистора

Servo myservo;
Servo motor;

unsigned long next_time;
unsigned long next_time_2;
unsigned long next_time_3;
int timeout = 5;        // Частота обновления датчика оборотов
int timeout2 = 1000;   // Частота вычисления оборотов в секунду
int timeout3 = 500;   // Частота обновления таймера работы электромотора
int sensorValue = 0;   // Переменная для хранения значения с фоторезистора
int counter = 0; //Счётчик оборотов
void setup() {
  motor.attach(6,1000,2000);
  myservo.attach(7);
  myservo.write(180);
  delay(1000);
  myservo.write(0);
  delay(1000);
  myservo.write(180);
  delay(1000);
  pinMode(clock, OUTPUT);
  pinMode(data, OUTPUT);
  pinMode(latch, OUTPUT);
  digitalWrite(latch, HIGH); //Это надо заменить на подачу питания с шины 5 вольт по возможности
  Serial.begin(9600);   // Инициализация Serial для вывода данных.
  next_time = millis() + timeout;
  next_time_2 = millis() + timeout2;
  next_time_3 = millis() + timeout3; // вычисляем время следующего переключения
}


void loop() {
  int now_time = millis();                          
  sensorValue = analogRead(sensorPin);            
  float voltage = sensorValue * (5.0 / 1023.0);     //Конвертируем входной сигнал в вольты
  
                 
    if( now_time >= next_time ){               
        next_time = now_time + timeout;  //Условие-счётчик, за выделенное время (timeout2) насчитывает количество высоких сигналов 
          if(voltage < 4){              //и затем сбрасывается
    counter++;                         // НУЖНО ПЕРЕРАБОТАТЬ ВЕСЬ ТАЙМЕР - НЕТ СЧИТЫВАНИЯ НИЗКИХ ОБОРОТОВ. Теоретический вариант - измерять время между вспышками
  }       
         
         }
   if( now_time >= next_time_2 ){               
        next_time_2 = now_time + timeout2;
          float RPS = counter/(timeout2/1000);
          float RPM = RPS*60;    
          Serial.println(RPM);
          float val = map(RPM, 0, 50, 0, 180);
          myservo.write(val);                            
          counter = 0;
         } 
   if( now_time >= next_time_3 ){               
        next_time_3 = now_time + timeout3; //Условие счётчик для управления мотором
         }
  
}


