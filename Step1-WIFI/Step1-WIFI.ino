/*
 * Шаг №1
 * WI-FI подключение
 */
#include <WiFi.h>        //Содержится в пакете
IPAddress apIP(192, 168, 4, 1);

// Определяем переменные
String _ssid     = "home"; // Для хранения SSID
String _password = "i12345678"; // Для хранения пароля сети
String _ssidAP = "WiFi";   // SSID AP точки доступа
String _passwordAP = ""; // пароль точки доступа

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Start 1-WIFI");
  //Запускаем WIFI
  WIFIinit();
}

void loop() {
  delay(1);
}



