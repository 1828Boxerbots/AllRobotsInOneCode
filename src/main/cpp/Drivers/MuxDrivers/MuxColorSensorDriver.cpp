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

void MuxColorSensorDriver::SetActive()
{
    m_breakout.SetChannel(1 << m_breakoutChannel);
}

SpinSubsystemBase::FMSColors MuxColorSensorDriver::GetColor()
{
    SetActive();
    return m_colorSensor->GetColor();
}

bool MuxColorSensorDriver::StatusIsFatal()
{
    SetActive();
	return m_colorSensor->StatusIsFatal();
}

// Completed 3/3/2020 , untested
