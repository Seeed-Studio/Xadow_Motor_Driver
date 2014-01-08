/*
  XadowMotor.cpp
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-7-12
  www.seeedstudio.com
  WWW.github.com/reeedstudio

  will receive one byte from I2C:
  +-------+--------+--------+--------+--------+--------+--------+----------+
  | bit 7 | bit 6  | bit  5 | bit 4  | bit 3  | bit 2  | bit 1  | bit 0    |
  +-------+--------+--------+--------+--------+--------+--------+----------+
  | mode  |     motorA      |      motorB     | speed  | reser  |Odd parity|
  +-------+-----------------+-----------------+--------+--------+----------+

  mode   - 1: go into sleep mode
           0: normal mode
  motorA - 00: stop
           01: turn forware
           10: turn Reversion
           11: no change(keep)
  motorB - refer to motorA
  speed  - 0: no set speed
           1: set speed
  reser  - reservation, must be 1
  Odd parity - Odd parity

  *note: if speed set to 1, that means you want to set speed of motor, there will be one byte folowing:
  +-------+--------+--------+--------+--------+--------+--------+----------+
  | bit 7 | bit 6  | bit  5 | bit 4  | bit 3  | bit 2  | bit 1  | bit 0    |
  +-------+--------+--------+--------+--------+--------+--------+----------+
  |    speed of motorA               |     speed of motorB                 |
  +----------------------------------+-------------------------------------+

  speed of motorA:  0-15
  speed of motorB:  0-15

  **note: in this version, speed was not avaiable

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Wire.h>
#include <Arduino.h>
#include "XadowMotor.h"

/*********************************************************************************************************
** Function name:           begin
** Descriptions:            initliazer I2C
*********************************************************************************************************/
void XadowMotor::begin(int address)
{
    Wire.begin();
    i2cAddress = address;
}

/*********************************************************************************************************
** Function name:           sendI2C
** Descriptions:            send a byte to I2C Wire
*********************************************************************************************************/
void XadowMotor::sendI2C(unsigned char dta)
{
    Wire.beginTransmission(i2cAddress);               // transmit to device #4
    Wire.write(dta);                                    // sends one byte
    Wire.endTransmission();                             // stop transmitting
}

/*********************************************************************************************************
** Function name:           calcOdd
** Descriptions:            calc Odd parity, and return byte that after odd...
*********************************************************************************************************/
unsigned char XadowMotor::calcOdd(unsigned char dta)
{
    int sum = 0;
    for(int i=0; i<8; i++)
    {
        if(dta & (0x01<<i))
        {
            sum++;
        }
    }
    if(sum%2 == 1)return dta;
    else return (dta+1);
}

/*********************************************************************************************************
** Function name:           getBatVol
** Descriptions:            get battery voltage
*********************************************************************************************************/
float XadowMotor::XadowMotor::getBatVol()
{

    Wire.requestFrom(i2cAddress, 1);      // request 6 bytes from slave device #2
    delay(1);
    while(Wire.available())                 // slave may send less than requested
    {
        unsigned char c = Wire.read();      // receive a byte as character
        float tmp = c*1.0;
        tmp = (tmp+300.0)/100.0;
#if __DebugXM
        Serial.print("bat Vol = ");
        Serial.println(tmp);
#endif
        return tmp;
    }
}

/*********************************************************************************************************
** Function name:           setMotorRun
** Descriptions:            set motor run state,there are four state:
                            MSTOP       0                // stop
                            MFOR        1                  // go forward
                            MREV        2                 // go reverse..
                            MHOLD       3                // keep
*********************************************************************************************************/
void XadowMotor::setMotorRun(unsigned char sMotorA, unsigned char sMotorB)
{
    if(sMotorA != MSTOP && sMotorA != MFOR && sMotorA != MREV && sMotorA != MHOLD)return;

    unsigned char dtaSend = 0x02;
    unsigned char tmpA = sMotorA<<5;
    unsigned char tmpB = sMotorB<<3;

    dtaSend = dtaSend | tmpA | tmpB;

    dtaSend = calcOdd(dtaSend);

    sendI2C(dtaSend);
#if __DebugXM
    Serial.print("send to i2c: ");
    Serial.println(dtaSend, HEX);
#endif
}

/*********************************************************************************************************
** Function name:           setPwrDown
** Descriptions:            power down to save energy
*********************************************************************************************************/
void XadowMotor::setPwrDown()
{
    sendI2C(0x80);
}

/*********************************************************************************************************
** Function name:           setWakeUp
** Descriptions:            wake up!!
*********************************************************************************************************/
void XadowMotor::setWakeUp()
{
    sendI2C(0x00);
    sendI2C(0x00);
    delay(500);
}

XadowMotor xadowMotor;
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
