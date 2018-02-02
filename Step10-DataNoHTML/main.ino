// ------------- Чтение значения json
String jsonRead(String &json, String name) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  return root[name].as<String>();
}

// ------------- Чтение значения json
int jsonReadtoInt(String &json, String name) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  return root[name];
}

// ------------- Запись значения json String
String jsonWrite(String &json, String name, String volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

// ------------- Запись значения json int
String jsonWrite(String &json, String name, int volume) {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);
  root[name] = volume;
  json = "";
  root.printTo(json);
  return json;
}

void saveConfig (){
  writeFile("config.json", configSetup );
}

// ------------- Чтение файла в строку
String readFile(String fileName, size_t len ) {
  File configFile = SPIFFS.open("/" + fileName, "r");
  if (!configFile) {
    return "Failed";
  }
  size_t size = configFile.size();
  if (size > len) {
    configFile.close();
    return "Large";
  }
  String temp = configFile.readString();
  configFile.close();
  return temp;
}

// ------------- Запись строки в файл
String writeFile(String fileName, String strings ) {
  File configFile = SPIFFS.open("/" + fileName, "w");
  if (!configFile) {
    return "Failed to open config file";
  }
  configFile.print(strings);
  //strings.printTo(configFile);
  configFile.close();
  return "Write sucsses";
}


// Перегрузка функций
// ------------- Создание данных для графика
String graf(int datas, int points, int refresh, String options) {
  String root = "{}";  // Формировать строку для отправки в браузер json формат
  // {"data":[1],"points":"10","refresh":"1","title":"Analog"}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  // вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  JsonArray& data = json.createNestedArray("data");
  data.add(datas);
  json["points"] = points;
  json["refresh"] = refresh;
  json["options"] = options;
  //"options":"low:0,showLine: false,showArea:true,showPoint:false",
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  return root;
}

// --------------Создание данных для графика
String graf(int datas, int points, int refresh) {
  String root = "{}";  // Формировать строку для отправки в браузер json формат
  // {"data":[1],"points":"10","refresh":"1","title":"Analog"}
  // Резервируем память для json обекта буфер может рости по мере необходимти, предпочтительно для ESP8266
  DynamicJsonBuffer jsonBuffer;
  // вызовите парсер JSON через экземпляр jsonBuffer
  JsonObject& json = jsonBuffer.parseObject(root);
  // Заполняем поля json
  JsonArray& data = json.createNestedArray("data");
  data.add(datas);
  json["points"] = points;
  json["refresh"] = refresh;
  //"options":"low:0,showLine: false,showArea:true,showPoint:false",
  // Помещаем созданный json в переменную root
  root = "";
  json.printTo(root);
  return root;
}
