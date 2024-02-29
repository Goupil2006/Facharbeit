#include <Servo.h>

class MyServo
{
public:
    int pin;
    int angle;
    int steps;
    Servo servoMotor;

    MyServo(int pin, int startAngle, int steps)
    {
        // Constructor code here
        this->pin = pin;
        this->angle = startAngle;
        this->steps = steps;
        servoMotor.attach(pin, 900, 1500);
        servoMotor.write(180 - startAngle);
    }

    void addRotation(int numSteps)
    {
        angle += (180 / steps) * numSteps;
        servoMotor.write(180 - angle);
    }

    void reset()
    {
        angle = 0;
        servoMotor.write(180 - angle);
    }

    void setAngle(int newAngle)
    {
        angle = newAngle;
        servoMotor.write(180 - angle);
    }

    int getAngle()
    {
        return angle;
    }
};
