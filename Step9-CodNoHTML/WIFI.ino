void WIFIinit() {
  // --------------------Получаем SSDP со страницы
  HTTP.on("/ssid", HTTP_GET, []() {
  jsonWrite(configSetup, "ssid", HTTP.arg("ssid"));
  jsonWrite(configSetup, "password", HTTP.arg("password"));
  saveConfig();                 // Функция сохранения данных во Flash
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
   // --------------------Получаем SSDP со страницы
  HTTP.on("/ssidap", HTTP_GET, []() {
  jsonWrite(configSetup, "ssidAP", HTTP.arg("ssidAP"));
  jsonWrite(configSetup, "passwordAP", HTTP.arg("passwordAP"));
  saveConfig();                 // Функция сохранения данных во Flash
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });


  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  String _ssid = jsonRead(configSetup, "ssid");
  String _password = jsonRead(configSetup, "password");
  if (_ssid == "" && _password == "") {
    WiFi.begin();
  }
  else {
    WiFi.begin(_ssid.c_str(), _password.c_str());
  }
  // Делаем проверку подключения до тех пор пока счетчик tries
  // не станет равен нулю или не получим подключение
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    // Если не удалось подключиться запускаем в режиме AP
    Serial.println("");
    Serial.println("WiFi up AP");
    StartAPMode();
  }
  else {
    // Иначе удалось подключиться отправляем сообщение
    // о подключении и выводим адрес IP
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode() {
  IPAddress apIP(192, 168, 4, 1);
  // Отключаем WIFI
  WiFi.disconnect();
  // Меняем режим на режим точки доступа
  WiFi.mode(WIFI_AP);
  // Задаем настройки сети
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  // Включаем WIFI в режиме точки доступа с именем и паролем
  // хронящихся в переменных _ssidAP _passwordAP
  String _ssidAP = jsonRead(configSetup, "ssidAP");
  String _passwordAP = jsonRead(configSetup, "passwordAP");
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());
  return true;
}
