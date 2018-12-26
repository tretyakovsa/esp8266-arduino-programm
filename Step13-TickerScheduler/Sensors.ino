// -----------------  DHT
void DHT_init() {
  dht.setup(dhtPin); //Запускаем датчик
  delay(1000); // Нужно ждать иначе датчик не определится правильно
  static uint16_t test = dht.getMinimumSamplingPeriod(); // Получим минимальное время между запросами данных с датчика
  jsonWrite(configJson, "dhttime", test); // Отправим в json переменную configJson ключ dhttime полученное значение
  dht.getTemperature();   // обязательно делаем пустое чтение первый раз иначе чтение статуса не сработает
  String statusDHT = dht.getStatusString(); // Определим стстус датчика
  Serial.print("DHT = ");
  Serial.println(statusDHT); //  и сообщим в Serial

  if (statusDHT == "OK") { // включим задачу если датчик есть
    jsonWrite(configJson, "temperature", dht.getTemperature());  // отправить температуру в configJson
    jsonWrite(configJson, "humidity", dht.getHumidity());        // отправить влажность в configJson

    ts.add(0, test, [&](void*) { // Запустим задачу 0 с интервалом test
      jsonWrite(configJson, "temperature", dht.getTemperature());   // отправить температуру в configJson
      jsonWrite(configJson, "humidity", dht.getHumidity());         // отправить влажность в configJson
      //Serial.print(".");
    }, nullptr, true);
  }
}

// -----------------  Вывод времени и даты в /config.live.json каждую секунду
void sec_init() {
  ts.add(1, 1000, [&](void*) { // Запустим задачу 1 с интервалом 1000ms
    // поместим данные для web страницы в json строку configJson
    // Будем вызывать эту функцию каждый раз при запросе /config.live.json
    // jsonWrite(строка, "ключ", значение_число); Так можно дабавить или обнавить json значение ключа в строке
    // jsonWrite(строка, "ключ", "значение_текст");
    jsonWrite(configJson, "time", GetTime()); // отправить время в configJson
    jsonWrite(configJson, "date", GetDate()); // отправить дату в configJson
  }, nullptr, true);
}
/* ---------------- Задание для закрепления материала
    Заставьте мигать светодиод на любом pin с частотой 5 секунд
    сделайте новую задачу под индексом 2
    в /config.live.json отправляйте состояние светодиода с ключем "stateLed"
    Выводите состояние светодиода на график по запросу вида /charts.json?data=stateLed
    Процедуру blink_init() инициализируйте в setup
*/

void blink_init() {
  // здесь пишите код решения
}

void GetSensor() {
  String string_array = "24.8,24.9,25.9,24.5,25.0,23.9,21.5,24.0,24.8,23.8,47.0,45.4,D,";
  uint8_t i = 0;
  String tmp;
  do {
    tmp = selectToMarker(string_array, ",");// Выделим первый элемент
    if (tmp != "D") {                               // если там не D
      jsonWrite(configJson, "sensor" + (String)(i), tmp); // запишем параметр в configJson
      string_array = deleteBeforeDelimiter(string_array, ","); //откинем использованное значение
      i++; // Увеличим index параметра
    } else { // иначе
      string_array = deleteBeforeDelimiter(string_array, ","); // откиним D
    }
  } while (tmp != "D");
}

void hendlSerial(){

  }
