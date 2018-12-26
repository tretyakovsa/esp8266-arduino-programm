#include <time.h>               //Содержится в пакете.  Видео с уроком http://esp8266-arduinoide.ru/step8-timeupdate/
void Time_init() {
  HTTP.on("/Time", handle_Time);     // Синхронизировать время устройства по запросу вида /Time
  HTTP.on("/timeZone", handle_time_zone);    // Установка времянной зоны по запросу вида http://192.168.0.101/timeZone?timeZone=3
  timeSynch(jsonReadtoInt(configSetup, "timezone"));
}
void timeSynch(int zone){
  if (WiFi.status() == WL_CONNECTED) {
    // Настройка соединения с NTP сервером
    configTime(zone * 3600, 0, "pool.ntp.org", "ru.pool.ntp.org");
    int i = 0;
    Serial.println("\nWaiting for time");
    while (!time(nullptr) && i < 10) {
      Serial.print(".");
      i++;
      delay(1000);
    }
    Serial.println("");
    Serial.println("ITime Ready!");
    Serial.println(GetTime());
    Serial.println(GetDate());
  }
}
// Установка параметров времянной зоны по запросу вида http://192.168.0.101/timeZone?timeZone=3
void handle_time_zone() {
   jsonWrite(configSetup, "timezone", (int)HTTP.arg("timeZone").toInt()); // Получаем значение timezone из запроса конвертируем в int сохраняем
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void handle_Time(){
  timeSynch(jsonReadtoInt(configSetup, "timezone"));
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  }

// Получение текущего времени
String GetTime() {
 time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
 String Time = ""; // Строка для результатов времени
 Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
 int i = Time.indexOf(":"); //Ишем позицию первого символа :
 Time = Time.substring(i - 2, i + 6); // Выделяем из строки 2 символа перед символом : и 6 символов после
 return Time; // Возврашаем полученное время
}

// Получение даты
String GetDate() {
 time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
 String Data = ""; // Строка для результатов времени
 Data += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
 int i = Data.lastIndexOf(" "); //Ишем позицию последнего символа пробел
 String Time = Data.substring(i - 8, i+1); // Выделяем время и пробел
 Data.replace(Time, ""); // Удаляем из строки 8 символов времени и пробел
 Data.replace("\n", ""); // Удаляем символ переноса строки
 return Data; // Возврашаем полученную дату
}
