// Importieren der Library
#include <RCSwitch.h>

// Klasse definieren
class MySwitch
{
private:
    // Instanz der RCSwitch Klasse erstellen
    RCSwitch rcSwitch;

public:
    MySwitch(int pin)
    {
    }

    // Methode um die Steckdose zu initialisieren
    void init(int pin)
    {
        rcSwitch.enableTransmit(pin); // Set the transmitting pin
        off();
    }

    // Methode um die Steckdose einzuschalten
    void on()
    {
        rcSwitch.switchOn("11011", "10000");
    }

    // Methode um die Steckdose auszuschalten
    void off()
    {
        rcSwitch.switchOff("11011", "10000");
    }
};
