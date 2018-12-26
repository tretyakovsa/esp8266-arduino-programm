
void count_init()
{
  Serial.println("Start Count");
  uint8_t cauntPin = 0;
  pinMode(cauntPin, INPUT);              // порт как выход
  attachInterrupt(cauntPin, blink, FALLING); // привязываем 0-е прерывание к функции blink().

}



void blink()
{
  static uint32_t caunt = 0;
  static unsigned long millis_prev;
  if (millis() - 20 > millis_prev) caunt++; // меняем значение на противоположное
  millis_prev = millis();
  Serial.println(caunt);
}
