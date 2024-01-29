// пример с простым шахматным меню
// пины энкодера
#define CLK 2
#define DT 3
#define SW 4

#include "GyverEncoder.h"
Encoder enc1(CLK, DT, SW);  // для работы c кнопкой

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // адрес 0x27 или 0x3f

// переменные
int led1 = 0;
int led2 = 0;
int led3 = 0;
int led4 = 0;
int led5 = 0;

int8_t arrowPos = 0;  // позиция стрелки

int led12 = 5;
int led22 = 6;
int led32 = 7;
int led42 = 8;
int led52 = 9;

void setup() {
  pinMode(led12,OUTPUT);
  pinMode(led22,OUTPUT);
  pinMode(led32,OUTPUT);
  pinMode(led42,OUTPUT);
  pinMode(led52,OUTPUT);



  pinMode(0, OUTPUT);
  Serial.begin(9600);
  enc1.setType(TYPE2);

  lcd.init();
  lcd.backlight();
  printGUI();   // выводим интерфейс
}

void loop() {
  digitalWrite(0, HIGH);
  enc1.tick();

  if (enc1.isTurn()) {  // при любом повороте
    lcd.clear();        // очищаем дисплей

    if (enc1.isRight()) {
      arrowPos++;
      if (arrowPos >= 4) arrowPos = 3;  // ограничиваем позицию курсора
    }
    if (enc1.isLeft()) {
      arrowPos--;
      if (arrowPos < 0) arrowPos = 0;  // ограничиваем позицию курсора
    }

    // при нажатом повороте меняем переменные ++
    if (enc1.isRightH()) {
      switch (arrowPos) {
        case 0: led1++;
          break;
        case 1: led2++;
          break;
        case 2: led3++;
          break;
        case 3: led4++;
          break;
        case 4: led5++;
          break;
      }
    }

    // при нажатом повороте меняем переменные --
    if (enc1.isLeftH()) {
      switch (arrowPos) {
        case 0: led1--;
          break;
        case 1: led2--;
          break;
        case 2: led3--;
          break;
        case 3: led4--;
          break;
        case 4: led5--;
          break;
      }
    }
    
    printGUI();   // выводим интерфейс
  }
}

void printGUI() {
  lcd.setCursor(0, 0); lcd.print("led1:"); lcd.print(led1);
  lcd.setCursor(8, 0); lcd.print("led2:"); lcd.print(led2);
  lcd.setCursor(0, 1); lcd.print("led3:"); lcd.print(led3);
  lcd.setCursor(8, 1); lcd.print("led4:"); lcd.print(led4);
  // выводим стрелку
  switch (arrowPos) {
    case 0: lcd.setCursor(4, 0);
      break;
    case 1: lcd.setCursor(12, 0);
      break;
    case 2: lcd.setCursor(4, 1);
      break;
    case 3: lcd.setCursor(12, 1);
      break;
  }
  lcd.write(126);   // вывести стрелку
  
}
