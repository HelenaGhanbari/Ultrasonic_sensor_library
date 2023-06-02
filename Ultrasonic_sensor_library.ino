#include ".\libs\ultrasonicsensor.h"

#define TRIG_PIN 2
#define ECHO_PIN 3

#define BAUDRATE 9600
UltrasonicSensor ultrasonic_sensor(TRIG_PIN,ECHO_PIN);

const int distance_for_object_detection {30};
bool state_of_object_detection {false}; 
void setup()
{
    Serial.begin(BAUDRATE);
    ultrasonic_sensor.init();
}

void loop()
{
    state_of_object_detection = ultrasonic_sensor.objectDetectionCM(distance_for_object_detection);  
    Serial.println(state_of_object_detection);
}