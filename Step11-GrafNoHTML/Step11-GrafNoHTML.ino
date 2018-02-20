#include "set.h"

void setup() {
  // Здесь код зависит от версии arduino IDE.
  // Если не компелируется раскомментируйте следующую строку
  //HTTP = new ESP8266WebServer (port);
  HTTP = ESP8266WebServer (port);  // и закомментируйте эту
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
  GRAF_init();

}

void loop() {
  HTTP.handleClient();
  delay(1);
  dnsServer.processNextRequest();
}
