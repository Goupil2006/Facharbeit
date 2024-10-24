// Importiern der Librarys
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Klasse definieren
class MyOled
{
private:
    LiquidCrystal_I2C lcd;

public:
    // Konstruktor
    MyOled() : lcd(0x27, 20, 4)
    {
    }

    // Methode um das Oled zu initialisieren
    void init()
    {
        lcd.init();
    }

    // Methode um Text auf das Oled zu schreiben
    void drawtexte(int x, int y, String text)
    {
        lcd.backlight();
        lcd.clear();
        lcd.setCursor(3, 0);
        lcd.print(text);
    }
};