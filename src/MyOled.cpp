#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class MyOled
{
private:
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

public:
    MyOled() : u8g2(U8G2_SH1106_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/U8X8_PIN_NONE))
    {
        u8g2.begin();
    }

    void drawtexte(int x, int y, const char *text)
    {
        u8g2.setFont(u8g2_font_8x13_tf);
        u8g2.setCursor(x, y);
        u8g2.print(text);
        update();
    }

    void drawRectangle(int x, int y, int width, int height)
    {
        u8g2.drawFrame(x, y, width, height);
    }

    void clear() { u8g2.clear(); }

    void clearBuffer()
    {
        u8g2.clearBuffer();
    }

    // Add more methods for drawing shapes, images, etc.
    void drawTip(int x, int y, const char *tip)
    {
        // Light bulb icon
        const unsigned char light_bulb_bits[] = {
            B00111100,
            B01111110,
            B01111110,
            B01111110,
            B01111110,
            B00111100,
            B00011000,
            B00011000
        };

        const int light_bulb_width = 8;
        const int light_bulb_height = 8;

        // Draw light bulb icon
        u8g2.drawXBMP(x, y, light_bulb_width, light_bulb_height, light_bulb_bits);

        // Draw tip text
        u8g2.setFont(u8g2_font_8x13_tf);
        u8g2.setCursor(x + light_bulb_width + 5, y + 10);
        u8g2.print(tip);

        update();
    }

    void update()
    {
        u8g2.sendBuffer();
    }
};
