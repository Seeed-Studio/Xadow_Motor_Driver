/*
 
  there are four motor state you can use:

  -MSTOP		-> stop
  -MFOR			-> go forward
  -MREV			-> go reverse
  -MHOLD		-> hold the recent state
  
  **NOTE: 
  there are four addreass you can choose, it's up to the hardware,
  for more information, refer to www.seeedstudio.com
  
  -MOTORADDRESS0       0x40                // A0 LOW, A1 LOW
  -MOTORADDRESS1       0x41                // A0 HIGH, A1 LOW
  -MOTORADDRESS2       0x42                // A0 LOW, A1 HIGH
  -MOTORADDRESS3       0x43                // A0 HIGH, A1 HIGH
  
  use this function: setMotorRun(unsigned char sMotorA, unsigned char sMotorB);
  you can contrl the both motor. 
  
 
*/

#include <Wire.h>

#include "XadowMotor.h"

void setup()
{
    Serial.begin(38400);
    xadowMotor.begin(MOTORADDRESS3);
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