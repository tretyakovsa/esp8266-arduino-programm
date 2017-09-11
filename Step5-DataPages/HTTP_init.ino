void HTTP_init(void) {
  HTTP.on("/restart", handle_Restart); // Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
  HTTP.on("/configs.json", handle_ConfigJSON); // формирование configs.json страницы для передачи данных в web интерфейс
  // Запускаем HTTP сервер
  HTTP.begin();

}

// Перезагрузка модуля по запросу вида http://192.168.0.101/restart?device=ok
void handle_Restart() {
  String restart = HTTP.arg("device");
  if (restart == "ok") ESP.restart();
  HTTP.send(200, "text/plain", "OK");
}

void handle_ConfigJSON() {
 String json = "{";  // Формировать строку для отправки в браузер json формат
                     //{"SSDP":"SSDP-test","ssid":"home","password":"i12345678","ssidAP":"WiFi","passwordAP":"","ip":"192.168.0.101"}
 // Имя SSDP
 json += "\"SSDP\":\"";
 json += SSDP_Name;
  // Имя сети
 json += "\",\"ssid\":\"";
 json += _ssid;
 // Пароль сети
 json += "\",\"password\":\"";
 json += _password;
 // Имя точки доступа
 json += "\",\"ssidAP\":\"";
 json += _ssidAP;
 // Пароль точки доступа
 json += "\",\"passwordAP\":\"";
 json += _passwordAP;
 // IP устройства
 json += "\",\"ip\":\"";
 json += WiFi.localIP().toString();
 json += "\"}";
 HTTP.send(200, "text/json", json);
}




