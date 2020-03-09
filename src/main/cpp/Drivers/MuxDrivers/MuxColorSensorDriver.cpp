/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/MuxDrivers/MuxColorSensorDriver.h"


MuxColorSensorDriver::MuxColorSensorDriver(frc::I2C::Port i2cPort, I2CMultiplexerDriver& breakout, uint8_t breakoutChannel):
    m_breakout(breakout),
    m_breakoutChannel(breakoutChannel)
{
    SetActive();
    m_colorSensor = new ColorSensorDriver(i2cPort);
}

 
/**
 *  This sets the multiplexer to whichever channel you want.
 * 
 *  The channels are defined as U8T_LINE... in Constants.
 * 
 *  This is called in every function of the Color sensor so
 *  you do not need to do it manually.
 */
void MuxColorSensorDriver::SetActive()
{
    m_breakout.SetChannel(1 << m_breakoutChannel);
}


SpinSubsystemBase::FMSColors MuxColorSensorDriver::GetColor()
{
    SetActive();
    return m_colorSensor->GetColor();
}


std::string MuxColorSensorDriver::GetColorString()
{
    SetActive();
    return m_colorSensor->GetColorString();
}


bool MuxColorSensorDriver::StatusIsFatal()
{
    SetActive();
	return m_colorSensor->StatusIsFatal();
}

// Completed 3/3/2020 , untested
