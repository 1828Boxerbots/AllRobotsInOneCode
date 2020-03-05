/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/MuxDrivers/MuxDistanceSensorDriver.h"

MuxDistanceSensorDriver::MuxDistanceSensorDriver(Rev2mDistanceSensor::Port Port,
					                             I2CMultiplexerDriver& breakout,
                                                 uint8_t breakoutChannel,
                                                 Rev2mDistanceSensor::DistanceUnit units,
					                             Rev2mDistanceSensor::RangeProfile profile):
                                                 m_breakout(breakout),
                                                 m_breakoutChannel(breakoutChannel)
{
    SetActive();
	m_distanceSensor = new RevDistanceSensorDriver(Port, units, profile);
	m_distanceSensor->StartMeasuring();
}


double MuxDistanceSensorDriver::GetDistance()
{
    SetActive();
    m_distanceSensor->GetMeasurementData();
    return m_distanceSensor->GetDistance(); 
}


bool MuxDistanceSensorDriver::IsRangeValid()
{
    SetActive();
    return m_distanceSensor->IsRangeValid();
}


void MuxDistanceSensorDriver::SetActive()
{
    m_breakout.SetChannel(1 << m_breakoutChannel);
}


bool MuxDistanceSensorDriver::StatusIsFatal()
{
    SetActive();
    return m_distanceSensor->StatusIsFatal();
}


