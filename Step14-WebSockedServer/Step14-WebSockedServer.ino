/*
 * Шаг №14
 * ESP8266 Библиотека WebSocketsServer
 * Передача данных на страницу средствами WebSockets
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
  //Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start 3-SSDP");
  SSDP_init();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 2-WebServer");
  HTTP_init();
  //Настраиваем и запускаем webSoket интерфейс
  Serial.println("Start 14-webSoket_init");
  webSoket_init();
    // Включаем Вывод времени и даты каждую секунду
  Serial.println("Start 13-sec_init");
  sec_init();
  Serial.println("Start 13-DHT");
  DHT_init();


}

void loop() {
  ts.update(); //планировщик задач
  HTTP.handleClient(); // Работа Web сервера
  yield();
  webSocket.loop(); // Работа webSocket
  dnsServer.processNextRequest(); // Для работы DNS в режиме AP
}
