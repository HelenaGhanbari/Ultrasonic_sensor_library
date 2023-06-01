# Introduction

This library is written to use HC-SR04 ultrasonic sensor.   

# How its work ?
To start with I'm going to explain the class and its methods.

```cpp
class UltrasonicSensor
{
private:
    byte m_trig_pin;
    byte m_echo_pin;
public:
    UltrasonicSensor(byte trig_pin,byte echo_pin);
    void init();
    unsigned int distanceMeasurementCM();
    bool objectDetectionCM(unsigned int distance{20});
};
```

Constructor: the constructor takes the pin number of trig and echo pin and then it's initialize the `m_trig_pin` and `m_echo_pin` with them. 

This class has got these methods :
+ init
+ distanceMeasurementCM
+ objectDetectionCM

**An introduction to methods :** 

init: The return type of method is `void`. This method is for setting up pins.

distanceMeasurementCM: The return type of method is `unsigned int`. This method measure the distance from the the closest object that is detected and return it as an `unsigned int` (in cm).

objectDetectionCM:  The return type of method is `bool`. This method has got a parameter that you must give a distance (in cm) that is a criterion for object detection. The default value is 20 cm. If you don't enter the function argument, it will be considered 20 cm.

## What do the methods work ?

### Constructor

```cpp
UltrasonicSensor::UltrasonicSensor(byte trig_pin,byte echo_pin)
{
    m_trig_pin = trig_pin;
    m_echo_pin = echo_pin;
}
```
The constructor is initializing the `m_trig_pin` and `m_echo_pin`.

### init

```cpp
void UltrasonicSensor::init()
{
    pinMode(m_trig_pin, OUTPUT);
    pinMode(m_echo_pin, INPUT);
}
```
When you don't have a class you need to setting up the pins in void setup and when you using the `init` method you do setting up your pins.

### distanceMeasurementCM

```cpp
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
```

In the firt 5 lines it just making the pulse. In next 2 lines it's receving the pulse. But what is happening in the other lines ?   
The formula of caculating the distance from the object is :   
D = T * S   
Distance from the object = The time it takes for pulse (back and forth)/2 * speed of sound  

As you know the speed of sound is 343 meter per second and is 0.0343 centimeter per microsecond. And for calculating the distance in cm we can write like this :   

```cpp
unsigned int duration;
duration = pulseIn(m_echo_pin , HIGH);
return duration/2*0.0343;
```

For the computer working with the decimals is hard instead of working with integer numbers. Because of this we should prefer dividing by 29 instead of multiply by 0.0343.   
note : Because the time is for the time it takes for the pulse to back and forth, we must multiply by 2 or divide by 58 instead of dividing by 29.

### objectDetectionCM

```cpp
bool UltrasonicSensor::objectDetectionCM(unsigned int distance)
{
    if(distanceMeasurementCM()<=distance){
        return true;
    }else{
        return false;
    }
}
```
This method uses the `distanceMeasurementCM` method. It compare the distance for the sensor with distance for the criterion for object detection. If it was equal or less than that value it returns true and else it returns false.

# How to use
At first you should include the library which is in the libs directory.

```ino
#include ".\libs\ultrasonicSensor
```
note : you should keep in mind your directory that where is it and then you can include the library for example if you are in the main directory and the libs directory it's not in the main directory you should write this in including:

```ino
#include ".\..\libs\ultrasonicSensor
```

Now the program knows the `UltrasoniSensor` class and you can make an object of it.

```ino
#define TRIG_PIN 2
#define ECHO_PIN 3
UltrasonicSensor ultrasonic_sensor(TRIG_PIN,ECHO_PIN);
```
Here you can see a constructor that it takes pin number for trig and echo pin.

As you know this class has got these methods :
+ init
+ distanceMeasurementCM
+ objectDetectionCM

## init method:

If you want to use `init` method it's better to use it in `void setup` because it's for setting up pins.

how to use:

```ino
void setup
{
    ultrasonic_sensor.init(); //setting up pins (pinmode)
}
```

## distanceMeasurementCM method

This method gives you the distance from the object and you can contain it in a variable ,print it , pass to another function and etc. 

how to use:

```ino 
void loop
{
    unsigned int distance {ultrasonic_sensor.distanceMeasurementCM()};
}
```

## objectDetectionCM method

You can know if your sensor detect any object in that distance that you give it to it.
how to use:

```ino
void loop
{
    const int distance_for_object_detection {30};
    bool state_of_object_detection {ultrasonic_sensor.objectDetectionC  (distance_for_object_detection)};
}
```
