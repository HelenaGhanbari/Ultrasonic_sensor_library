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