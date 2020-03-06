/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/I2CMultiplexerDriver.h"


I2CMultiplexerDriver::I2CMultiplexerDriver(frc::I2C::Port i2cPort, int breakoutAddress) 
{
    m_pDevice = new frc::I2C(i2cPort, breakoutAddress);
    m_current_channel = 0;
}


// Communicate which channel the mux should be on
//          [x,x,x,x,x,x,x,x]
// channel   7,6,5,4,3,2,1,0
bool I2CMultiplexerDriver::SetChannel(uint8_t channel, bool log)
{
    bool retVal = true;

    if(m_current_channel != channel)
    {
        m_current_channel = channel;
        retVal = m_pDevice->WriteBulk(&channel, 1);
        if (retVal) {Util::SendErrorAndCode("Write to Mux failed!", 151, "I2CMultiplexerDriver.cpp");}
        else if (log) {Util::Log("Current Mux Channel", GetChannelName(channel), "Mux Driver");}
    }

    return retVal;
}


uint8_t I2CMultiplexerDriver::GetChannel()
{
    return m_current_channel;
}


std::string I2CMultiplexerDriver::GetChannelName(uint8_t channel)
{
    std::string name;

    if (channel == U8T_LINE_COLORSENSOR_ROBOT2020)         {name = "Color Sensor";}
    if (channel == U8T_LINE_LEFTDISTANCESENSOR_ROBOT2020)  {name = "Left Distance Sensor";}
    if (channel == U8T_LINE_RIGHTDISTANCESENSOR_ROBOT2020) {name = "Right Distance Sensor";}
    if (channel == U8T_LINE_LIDAR_ROBOT2020)               {name = "Lidar";}

    return name;
}

// 3/3/2020
