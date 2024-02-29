#include <RCSwitch.h>

class MySwitch
{
private:
    RCSwitch rcSwitch;

public:
    MySwitch(int pin)
    {
        rcSwitch.enableTransmit(pin); // Set the transmitting pin
        off();
    }

    void on()
    {
        rcSwitch.switchOn("11011", "10000");
    }

    void off()
    {
        rcSwitch.switchOff("11011", "10000");
    }
};
