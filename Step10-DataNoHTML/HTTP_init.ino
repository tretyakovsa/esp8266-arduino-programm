
void HTTP_init(void) {

  // --------------------Выдаем данные configJson
  HTTP.on("/config.live.json", HTTP_GET, []() {
    jsonWrite(configJson, "time", GetTime());
    jsonWrite(configJson, "date", GetDate());
    jsonWrite(configJson, "gpio0", digitalRead(0));
    jsonWrite(configJson, "A0", analogRead(A0));
    HTTP.send(200, "application/json", configJson);
  });
  // -------------------Выдаем данные configSetup
  HTTP.on("/config.setup.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", configSetup);
  });
  // -------------------Выдаем данные configSetup
  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  httpUpdater.setup(&HTTP);
  // Запускаем HTTP сервер
  HTTP.begin();
}
