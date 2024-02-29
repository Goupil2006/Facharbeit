#include <Arduino.h>

class MyAmpel
{
private:
    int redPin;
    int yellowPin;
    int greenPin;

public:
    MyAmpel(int redPin, int yellowPin, int greenPin)
    {
        this->redPin = redPin;
        this->yellowPin = yellowPin;
        this->greenPin = greenPin;
        pinMode(redPin, OUTPUT);
        pinMode(yellowPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
    }

    void turnOnRed()
    {
        digitalWrite(redPin, HIGH);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, LOW);
    }

    void turnOnYellow()
    {
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(greenPin, LOW);
    }

    void turnOnGreen()
    {
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, HIGH);
    }
};
