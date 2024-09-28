#include <Arduino.h>
#include <DallasTemperature.h>
// библиотека для работы с протоколом 1-Wire
#include <OneWire.h>
// Определение пинов для датчиков
// Правое плечо
#define TRIG_PIN1 18
#define ECHO_PIN1 19
// Левое плечо
#define TRIG_PIN2 22
#define ECHO_PIN2 23
// Спина 
#define TRIG_PIN3 25
#define ECHO_PIN3 26
///// триггеры
#define LEFT_VIBRO 33
#define BACK_VIBRO 14
#define RIGHT_VIBRO 27
#define CHEST_COOLER 16
// Термодатчик 
#define ONE_WIRE_BUS 4
// Создаем объект OneWire
OneWire oneWire(ONE_WIRE_BUS);

// Создаем объект DallasTemperature для работы с датчиком
DallasTemperature sensors(&oneWire);
// Функция для измерения расстояния
long measureDistance(int trigPin, int echoPin) {
  // Отправка ультразвукового сигнала
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Измерение времени возврата сигнала
  long duration = pulseIn(echoPin, HIGH);

  // Преобразование времени в расстояние
  long distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  // Инициализация последовательного соединения
  Serial.begin(115200);
    sensors.begin();
  // Инициализация пинов для первого датчика
  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);

  // Инициализация пинов для второго датчика
  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);

  // Инициализация пинов для третьего датчика
  pinMode(TRIG_PIN3, OUTPUT);
  pinMode(ECHO_PIN3, INPUT);

  pinMode(LEFT_VIBRO, OUTPUT);
  pinMode(BACK_VIBRO, OUTPUT);
  pinMode(RIGHT_VIBRO, OUTPUT);
  pinMode(CHEST_COOLER, OUTPUT);

}

void loop() {
  // Запрашиваем температуру с датчика
  sensors.requestTemperatures();
  // Получаем температуру с датчика в градусах Цельсия
  float temperatureC = sensors.getTempCByIndex(0);
  // Выводим температуру в последовательный порт
  Serial.println("//////////////////////////////////////////////////////");
  Serial.print("Temperature under SUIT: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  if(temperatureC>27){
    Serial.print("ITS TOO WARM");
    digitalWrite(CHEST_COOLER, HIGH);
  }
  else{
    digitalWrite(CHEST_COOLER, LOW);
  }
  // Измерение расстояния с первого датчика
  long distance1 = measureDistance(TRIG_PIN1, ECHO_PIN1);
  Serial.print("Right shoulder: ");
  Serial.print(distance1);
  Serial.println(" cm");
  if(distance1<=100){
 Serial.println("ON U RIGHT SHOULDER");
digitalWrite(RIGHT_VIBRO, HIGH);
  }
  else{
digitalWrite(RIGHT_VIBRO, LOW);
  }
  // Измерение расстояния со второго датчика
  long distance2 = measureDistance(TRIG_PIN2, ECHO_PIN2);
  Serial.print("Left Shoulder: ");
  Serial.print(distance2);
  Serial.println(" cm");
  if(distance2<=100){
Serial.println("ON U LEFT SHOULDER");
digitalWrite(LEFT_VIBRO, HIGH);
  }
  else{
digitalWrite(LEFT_VIBRO, LOW);
  }
  // Измерение расстояния с третьего датчика
  long distance3 = measureDistance(TRIG_PIN3, ECHO_PIN3);
  Serial.print("Back: ");
  Serial.print(distance3);
  Serial.println(" cm");
  if(distance3<=100){
 Serial.println("ON U BACK");
digitalWrite(BACK_VIBRO, HIGH);
  }
  else{
digitalWrite(BACK_VIBRO, LOW);
  }
  // Задержка между измерениями
}