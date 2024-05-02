// Importiern der Librarys
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Klasse definieren
class MyOled
{
private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

public:
    // Konstruktor
    MyOled() : u8g2(U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE))
    {
    }

    // Methode um das Oled zu initialisieren
    void init()
    {
        u8g2.begin();
    }

    // Methode um Text auf das Oled zu schreiben
    void drawtexte(int x, int y, const char *text)
    {
        u8g2.setFont(u8g2_font_8x13_tf);
        u8g2.setCursor(x, y);
        u8g2.print(text);
        update();
    }

    // Methode um ein Rechteck auf das Oled zu zeichnen (wird momentan noch nicht verwendet)
    void drawRectangle(int x, int y, int width, int height)
    {
        u8g2.drawFrame(x, y, width, height);
    }

    // Methode um das Oled zu löschen
    void clear() { u8g2.clear(); }

    // Methode um den Buffer zu löschen
    void clearBuffer()
    {
        u8g2.clearBuffer();
    }

    // Methode um ein Tipp auf das Oled zu zeichnen
    void drawTip(int x, int y, const char *tip)
    {
        // Beispiel icon
        const unsigned char light_bulb_bits[] = {
            0x3c, 0x7e, 0x7e, 0x7e, 0x7e, 0x3c, 0x18, 0x18};

        const int light_bulb_width = 10;
        const int light_bulb_height = 10;

        // Icon zeichnen
        u8g2.drawXBMP(x, y, light_bulb_width, light_bulb_height, light_bulb_bits);

        // Text zeichnen
        u8g2.setFont(u8g2_font_8x13_tf);
        u8g2.setCursor(x + light_bulb_width + 5, y + 10);
        u8g2.print(tip);

        // Buffer senden
        update();
    }

    // Methode um den Buffer zu senden
    void update()
    {
        u8g2.sendBuffer();
    }
};
