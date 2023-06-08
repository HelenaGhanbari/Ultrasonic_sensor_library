//The path of base header file (Relative path)
#include ".\..\libs\ultrasonicsensor.h"

UltrasonicSensor::UltrasonicSensor(byte trig_pin,byte echo_pin)
{
    m_trig_pin = trig_pin;
    m_echo_pin = echo_pin;
}

//This method is for setting up pins.
//@return none
//@param none
void UltrasonicSensor::init()
{
    pinMode(m_trig_pin, OUTPUT);
    pinMode(m_echo_pin, INPUT);
}
//This method is for measure the distance from the object.
//@return an unsigned int number that is the distance from the object.
//@param none 
unsigned int UltrasonicSensor::distanceMeasurementCM()
{
    digitalWrite(m_trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_trig_pin, LOW);
    unsigned int duration;
    duration = pulseIn(m_echo_pin , HIGH);
    return duration/58;
}
//This method is for 
//@return a bool value it is for when our sensor detected any object in that distance.
//@param an unsigned int hat is a criterion for object detection. 
bool UltrasonicSensor::objectDetectionCM(unsigned int distance)
{
    if(distanceMeasurementCM()<=distance){
        return true;
    }else{
        return false;
    }
}