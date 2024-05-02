// Importieren der Library
#include <Servo.h>

// Klasse definieren
class MyServo
{
public:
    int pin;
    int angle;
    int steps;
    Servo servoMotor;

    // Konstruktor
    MyServo(int pin, int startAngle, int steps)
    {
        // Constructor code here
        this->pin = pin;
        this->angle = startAngle;
        this->steps = steps;
    }

    // Methode um den Servo zu initialisieren an einen übergebenen Pin
    void init(int pin)
    {
        this->pin = pin;
        servoMotor.attach(pin, 900, 1500);
        servoMotor.write(180 - angle);
    }

    // Methode um den Servo zu drehen je nach anzahl der definierten Schritte
    void addRotation(int numSteps)
    {
        angle += (180 / steps) * numSteps;
        servoMotor.write(180 - angle);
    }

    // Methode um den Servo auf 0 Grad zu setzen
    void reset()
    {
        angle = 0;
        servoMotor.write(180 - angle);
    }

    // Methode um den Servo auf belibigen Winkel zu setzen
    void setAngle(int newAngle)
    {
        angle = newAngle;
        servoMotor.write(180 - angle);
    }

    // Methode um den aktuellen Winkel des Servos zu bekommen
    int getAngle()
    {
        return angle;
    }
};
