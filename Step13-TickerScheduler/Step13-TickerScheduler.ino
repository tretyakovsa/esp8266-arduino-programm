/*
 * Шаг №13
 * ESP8266 Библиотека TickerScheduler
 * Получение времени из сети
 * загрузите файловую систему если у вас не
 * установлен плагин качайте его здесь: https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.3.0/ESP8266FS-0.3.0.zip
 * видео как установить здесь: https://www.youtube.com/watch?v=0eO6esXBYRo

*/
#include "set.h"

void setup() {

  Serial.begin(115200);
  delay(5);
  Serial.println("");
  //Запускаем файловую систему
  Serial.println("Start 4-FS");
  FS_init();
  Serial.println("Step7-FileConfig");
  configSetup = readFile("config.json", 4096);
  jsonWrite(configJson, "SSDP", jsonRead(configSetup, "SSDP"));
  Serial.println(configSetup);
  Serial.println("Start 1-WIFI");
  //Запускаем WIFI
  WIFIinit();
  Serial.println("Start 8-Time");
  // Получаем время из сети
  Time_init();
  sec_init();
  //Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start 3-SSDP");
  SSDP_init();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 2-WebServer");
  HTTP_init();
  DHT_init();
  GetSensor();
  count_init();

}

void loop() {
  ts.update(); //планировщик задач
  HTTP.handleClient(); // Работа Web сервера
  yield();
  dnsServer.processNextRequest(); // Для работы DNS в режиме AP
}
