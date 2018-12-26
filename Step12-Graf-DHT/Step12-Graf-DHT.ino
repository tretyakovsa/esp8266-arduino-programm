/*
 * Шаг №12
 * ESP8266 температура и влажность на графикe
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
  //Настраиваем и запускаем SSDP интерфейс
  Serial.println("Start 3-SSDP");
  SSDP_init();
  //Настраиваем и запускаем HTTP интерфейс
  Serial.println("Start 2-WebServer");
  HTTP_init();
  DHT_init();

}

void loop() {
  HTTP.handleClient();
  delay(1);
  dnsServer.processNextRequest();
}
