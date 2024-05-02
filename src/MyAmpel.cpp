// Importieren der Library
#include <Arduino.h>

// Klasse definieren
class MyAmpel
{
private:
    // Pinplätze defin
    int redPin;
    int yellowPin;
    int greenPin;

public:
    MyAmpel() {}

    // Methode um die Ampel zu initialisieren
    void init(int redPin, int yellowPin, int greenPin)
    {
        this->redPin = redPin;
        this->yellowPin = yellowPin;
        this->greenPin = greenPin;
        pinMode(redPin, OUTPUT);
        pinMode(yellowPin, OUTPUT);
        pinMode(greenPin, OUTPUT);
    }

    // Methode um die rote LED einzuschalten
    void turnOnRed()
    {
        digitalWrite(redPin, HIGH);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, LOW);
    }

    // Methode um die gelbe LED einzuschalten
    void turnOnYellow()
    {
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(greenPin, LOW);
    }

    // Methode um die grüne LED einzuschalten
    void turnOnGreen()
    {
        digitalWrite(redPin, LOW);
        digitalWrite(yellowPin, LOW);
        digitalWrite(greenPin, HIGH);
    }
};
