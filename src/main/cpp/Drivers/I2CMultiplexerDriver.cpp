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
}

// 2/15/20
