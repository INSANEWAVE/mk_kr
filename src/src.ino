#include <Servo.h> //Библиотека для работы с сервоприводами и бесколлекторными моторами

#define sensorPin A5 // Пин фоторезистора

Servo myservo;

unsigned long next_time;
unsigned long next_time_2;
unsigned long next_time_3;
int timeout = 5;        // Частота обновления датчика оборотов
int timeout2 = 1000;   // Частота вычисления оборотов в секунду
int timeout3 = 500;   // Частота обновления таймера работы электромотора
int sensorValue = 0; // Переменная для хранения значения с фоторезистора
bool elementDetected = false;
   
long counter = 0;      //Счётчик оборотов
void setup() {
  
  myservo.attach(7);          //Подключение сервопривода
  myservo.write(0);
  delay(1000);
  myservo.write(180);
  delay(1000);
  myservo.write(0);
  delay(1000);
  Serial.begin(250000);   // Инициализация Serial для вывода данных.
  next_time = millis() + timeout;
  next_time_2 = millis() + timeout2;

}


void loop() {
  unsigned long now_time = millis();                          
  sensorValue = analogRead(sensorPin);
            
    if( now_time >= next_time ){               
      next_time = now_time + timeout;
      
      if(sensorValue < 940){
    elementDetected = true;            
    counter++;                         
  }else {elementDetected = false;}     
        
         }

   if( now_time >= next_time_2 ){               
        next_time_2 = now_time + timeout2;
          float RPM = (counter/timeout)*60;
            
          Serial.println("RPM:");
          Serial.println(RPM);

          float val = map(RPM, 0, 2000, 0, 180);
          myservo.write(val);                            
          counter = 0;
         } 
   
  
}


