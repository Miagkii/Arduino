/*
   Мощный компьютерный розыгрыщ на основе платформы BS Micro
   (SS Micro, Arduino Leonardo, Arduino Pro Micro, Atmega32U4)
   Плата вставляется в USB порт и по случайному таймеру активирует случайно одно из действий:
   - Случайный сдвиг курсора мыши
   - Нажатие случайной клавиши (буква, цифра, символ)
   - Пишет слово
   - Меняет активное окно (Alt+TAB)
   - Закрывает активное окно (Alt+F4)
   - Перемещает окно в случайное место (WIN+стрелка случайно)
   - Кликает PageDown
   - Кликает Insert
   - Сворачивает все окна (Win+D)
   - Меняет раскладку клавиатуры (Alt+Shift)
   - Включает/выключает Caps Lock

   **************************************
   Разработал: AlexGyver
   http://alexgyver.ru/pc-prank/
   https://github.com/AlexGyver/pc-prank/
*/

#include "Keyboard.h"
#include "Mouse.h"

void setup() {
  Mouse.begin();
  Keyboard.begin();
  delay(500);
  Serial.begin(9600);
}

void loop() {
  Mouse.move(random(400) - 200, random(400) - 200);
  delay(30000);
}

/* МЫШЬ
    Функции
  Mouse.click()
  Mouse.move()
  Mouse.press()
  Mouse.release()

  Кнопки мыши для функций click, press и release:
  MOUSE_LEFT
  MOUSE_RIGHT
  MOUSE_MIDDLE

   КЛАВИАТУРА
   Для отправки "единичного" нажатия испольузем Keyboard.write
   Для эмуляции одновременного нажатия нескольких клавиш используйте команду Keyboard.press().
   Отпустить можно командой Keyboard.release(), также Keyboard.releaseAll() отпускает все нажатые
   Список клавиш-модификаторов
  KEY_LEFT_CTRL
  KEY_LEFT_SHIFT
  KEY_LEFT_ALT
  KEY_LEFT_GUI
  KEY_RIGHT_CTRL
  KEY_RIGHT_SHIFT
  KEY_RIGHT_ALT
  KEY_RIGHT_GUI

  KEY_UP_ARROW
  KEY_DOWN_ARROW
  KEY_LEFT_ARROW
  KEY_RIGHT_ARROW
  KEY_BACKSPACE
  KEY_TAB
  KEY_RETURN
  KEY_ESC
  KEY_INSERT
  KEY_DELETE
  KEY_PAGE_UP
  KEY_PAGE_DOWN
  KEY_HOME
  KEY_END
  KEY_CAPS_LOCK
  KEY_F1
  KEY_F2
  KEY_F3
  KEY_F4
  KEY_F5
  KEY_F6
  KEY_F7
  KEY_F8
  KEY_F9
  KEY_F10
  KEY_F11
  KEY_F12
*/
