#include <Servo.h>
#include <LiquidCrystal_I2C.h>

// Константы
const int servoPin = 9;
const int displayColumns = 16;
const int displayRows = 2;
const int rotationDelay = 180000; // 3 минуты в миллисекундах

// Переменные
Servo feederServo;
LiquidCrystal_I2C lcd(0x27, displayColumns, displayRows);

// Прототипы функций
void rotateServo();
void updateDisplay();

void setup() {
  // Инициализация сервопривода
  feederServo.attach(servoPin);

  // Инициализация дисплея
  lcd.begin(displayColumns, displayRows);
  lcd.print("Добро пожаловать");
  lcd.setCursor(0, 1);
  lcd.print("в MEFeeder");

  // Ждем 3 секунды, чтобы отобразить приветственное сообщение
  delay(3000);

  // Очистка дисплея
  lcd.clear();
}

void loop() {
  // Поворот сервопривода
  rotateServo();

  // Обновление дисплея
  updateDisplay();

  // Задержка на 3 минуты
  delay(rotationDelay);
}

void rotateServo() {
  feederServo.write(200); // Поворачиваем сервопривод на 200 градусов
  delay(2000); // Задержка на 2 секунды
  feederServo.write(0); // Возвращаем сервопривод в исходное положение
}

void updateDisplay() {
  // Получаем текущее время
  unsigned long currentTime = millis();
  unsigned long nextRotationTime = currentTime + rotationDelay;
  
  // Преобразуем миллисекунды в часы, минуты и секунды
  unsigned long hours = (nextRotationTime / 3600000) % 24;
  unsigned long minutes = (nextRotationTime / 60000) % 60;
  unsigned long seconds = (nextRotationTime / 1000) % 60;

  // Отображаем время следующего поворота
  lcd.clear();
  lcd.print("Следующий поворот:");
  lcd.setCursor(0, 1);
  lcd.print(String(hours) + ":" + String(minutes) + ":" + String(seconds));
}
