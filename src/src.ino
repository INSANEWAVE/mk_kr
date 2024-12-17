unsigned long next_time;
unsigned long second_next_time; 
int timeout = 5; // Частота обновления датчика оборотов
int timeout2 = 1000; //Частота вычисления оборотов в секунду
int sensorPin = A0;   // Пин, к которому подключен фоторезистор
int sensorValue = 0;   // Переменная для хранения значения с фоторезистора
int counter = 0; //Счётчик оборотов
void setup() {
  Serial.begin(9600);   // Инициализация Serial для вывода данных.
  next_time = millis() + timeout;
  second_next_time = millis() + timeout2; // вычисляем время следующего переключения
}

void loop() {
  int now_time = millis();                          
  sensorValue = analogRead(sensorPin);            
  float voltage = sensorValue * (5.0 / 1023.0);     //Конвертируем входной сигнал в вольты
                 
    if( now_time >= next_time ){               
        next_time = now_time + timeout; //Условие-счётчик, за выделенное время (timeout2) насчитывае количество высоких сигналов и затем сбрасывается
          if(voltage < 4){
    counter++;
  }       
         
         }
   if( now_time >= second_next_time ){               
        second_next_time = now_time + timeout2;
          float RPM = counter/(timeout2/1000);    
          Serial.println(RPM);    // 02.12.2024 Тут нужно сделать вывод на сервопривод. В идеале использовать функцию map
                                  // Стрелочный индикатор на 360 градусов. 
                                  //Также нужно уменьшить зеркальный элемент на роторе и решить проблему с зашкаливанием датчика - сейчас крайнее значение 200 оборотов в секунду.
          counter = 0;
         } 
        
}


