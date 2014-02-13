Xadow - Motor Driver
---------------------------------------------------------
[![Xadow - Motor Driver](http://www.seeedstudio.com/depot/images/product/x%20motor.jpg)](http://www.seeedstudio.com/depot/xadow-motor-driver-p-1626.html?cPath=91_92)

Xadow Motor can be used to control DC Motors. Its heart is a low-saturation two-channel bidirectional motor drive chip LB1836M, controlled by ATmega168 which handles the I2C communication with Xadow Main Board. Xadow Motor features a changeable I2C address. And it needs a separate low power to drive motors.
 
**Specification:**
- Motor Driver: LB1836M
- Battery Voltage: 2.5V ~ 9V
- Output Current per channel(Max): 300mA
- Communication Mode: I2C
- I2C Address is changeable




# Usage:

This library is written for manage Xadow, include :

* get battery voltage from xadow motor board
* control motor run
* power down mode


## Function:


there are some useful function as folowing:

### Initialization
in fact , it's just initialize I2C wire

    void begin()

### Get Voltage of battery
this function will return voltage of battery

    float getBatVol();

### Set motor state
yep, this's the most useful function that can control the both motor

    void setMotorRun(unsigned char sMotorA, unsigned char sMotorB);

there are 4 state you can use:

    MSTOP       0                   // stop
    MFOR        1                   // go forward
    MREV        2                   // go reverse..
    MHOLD       3                   // keep

## APPLICATION

off curse you can find it in examples, there I'll show you how to use this library

    #include <Wire.h>
    #include "XadowMotor.h"
    
    void setup()
    {
        Serial.begin(38400);
        xadowMotor.begin();
    }
    
    void loop()
    {
    
        Serial.print("bat vol :");
        Serial.println(xadowMotor.getBatVol());
        
        xadowMotor.setMotorRun(MFOR, MFOR);
    
        delay(2000);
    
        xadowMotor.setMotorRun(MSTOP, MSTOP);
    
        delay(500);
    
        xadowMotor.setMotorRun(MREV, MREV);
    
        delay(2000);
    
        xadowMotor.setPwrDown();
        delay(1000);
        xadowMotor.setWakeUp();
    
    }



For more information, please refer to [wiki page](http://www.seeedstudio.com/wiki/Xadow_Motor).

    
----


This software is written by loovee [luweicong@seeedstudio.com](luweicong@seeedstudio.com "luweicong@seeedstudio.com") for seeed studio<br>
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>

Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>


[![Analytics](https://ga-beacon.appspot.com/UA-46589105-3/Xadow_Motor_Driver)](https://github.com/igrigorik/ga-beacon)
