void HTTP_init(void) {
  HTTP.onNotFound(handleNotFound); // Сообщение если нет страницы. Попробуйте ввести http://192.168.0.101/restar?device=ok&test=1&led=on
  HTTP.on("/", handleRoot); // Главная страница http://192.168.0.101/
  HTTP.on("/restart", handle_Restart); // Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
  // Запускаем HTTP сервер
  HTTP.begin();

}

// Ответ если страница не найдена
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += HTTP.uri();
  message += "\nMethod: ";
  message += (HTTP.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += HTTP.args();
  message += "\n";
  for (uint8_t i=0; i<HTTP.args(); i++){
    message += " " + HTTP.argName(i) + ": " + HTTP.arg(i) + "\n";
  }
  HTTP.send(404, "text/plain", message);
}

// Ответ при обращении к основной странице
void handleRoot() {
  HTTP.send(200, "text/plain", "hello from esp8266!");
}

// Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
void handle_Restart() {
  String restart = HTTP.arg("device");
  if (restart == "ok") ESP.restart();
  HTTP.send(200, "text/plain", "OK");
}




