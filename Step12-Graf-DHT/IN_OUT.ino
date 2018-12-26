// поместим данные для web страницы в json строку configJson
// Будем вызывать эту функцию каждый раз при запросе /config.live.json
// jsonWrite(строка, "ключ", значение_число); Так можно дабавить или обнавить json значение ключа в строке
// jsonWrite(строка, "ключ", "значение_текст");
void outData() {
  jsonWrite(configJson, "time", GetTime());
  jsonWrite(configJson, "date", GetDate());
  jsonWrite(configJson, "flashChip", String(ESP.getFlashChipId(), HEX));
}

// -----------------  DHT
void DHT_init() {
  dht.setup(dhtPin); //Запускаем датчик
  delay(1000); // Нужно ждать иначе датчик не определится правильно
  static uint16_t test = dht.getMinimumSamplingPeriod(); // Получим минимальное время между запросами данных с датчика
  jsonWrite(configJson, "dhttime", test); // Отправим в json переменную configJson ключ dhttime полученное значение
  dht.getTemperature();   // попытаемся считать данные
  Serial.print("DHT = ");
  Serial.println(dht.getStatusString()); // Определим стстус датчика и сообщим в Serial
  // Реакция на запрос /temperature.json
  HTTP.on("/temperature.json", HTTP_GET, []() { // Все что здесь выполняется только при запросе, если запроса нет то температура не измеряется
    String data = graf(dht.getTemperature()); // получаем значение температуры и формируем строку для графика
    jsonWrite(data, "refresh", jsonReadtoInt(configJson, "dhttime")); // Добовляем к строке настройку обновления refresh, данные берем с ключа dhttime
    HTTP.send(200, "application/json", data); // Будем отпровлять ответ json из переменной data
  });
  // Реакция на запрос /humidity.json
  HTTP.on("/humidity.json", HTTP_GET, []() { // Все что здесь выполняется только при запросе, если запроса нет то влажность не измеряется
    String data = graf(dht.getHumidity()); //получаем значение влажности и формируем строку для графика
    jsonWrite(data, "refresh", jsonReadtoInt(configJson, "dhttime")); // Добовляем к строке настройку обновления refresh, данные берем с ключа dhttime
    HTTP.send(200, "application/json", data); // Будем отпровлять ответ json из переменной data
  });

}
