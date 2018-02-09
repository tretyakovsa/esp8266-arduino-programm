  // поместим данные для web страницы в json строку configJson
  // Будем вызывать эту функцию каждый раз при запросе /config.live.json
  // jsonWrite(строка, "ключ", значение_число); Так можно дабавить или обнавить json значение ключа в строке
  // jsonWrite(строка, "ключ", "значение_текст");
void outData(){
    jsonWrite(configJson, "time", GetTime());
    jsonWrite(configJson, "date", GetDate());
    jsonWrite(configJson, "gpio0", digitalRead(0));
    jsonWrite(configJson, "A0", analogRead(A0));
    jsonWrite(configJson, "flashChip", String(ESP.getFlashChipId(), HEX));
  }
