// #include <RCSwitch.h>

// RCSwitch mySwitch;

// void setup()
// {
//     pinMode(32, INPUT);
//     mySwitch.enableTransmit(10); // Set the transmitting pin
// }

// void loop()
// {
//     if (digitalRead() == HIGH)
//     {
//         // Repeat the on/off cycle 10 times
//         for (int i = 0; i < 10; i++)
//         {
//             // Turn on the RC switch
//             mySwitch.switchOn("11011", "10000"); // Replace 1234 with your desired code and 24 with your desired length

//             delay(1000); // Wait for 1 second

//             // Turn off the RC switch
//             mySwitch.switchOff("11011", "10000"); // Replace 1234 with your desired code and 24 with your desired length

//             delay(1000); // Wait for 1 second
//         }
//     }
// }
