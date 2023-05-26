#include ".\..\libs\ultrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(byte trig_pin,byte echo_pin)
{
    m_trig_pin = trig_pin;
    m_echo_pin = echo_pin;
}
void UltrasonicSensor::init()
{
    pinMode(m_trig_pin, OUTPUT);
    pinMode(m_echo_pin, INPUT);
}
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
bool UltrasonicSensor::objectDetectionCM(unsigned int distance)
{
    if(distanceMeasurementCM()<=distance){
        return true;
    }else{
        return false;
    }
}