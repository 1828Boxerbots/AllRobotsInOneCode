/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/MuxDrivers/MuxDistanceSensorDriver.h"


MuxDistanceSensorDriver::MuxDistanceSensorDriver(Rev2mDistanceSensor::Port Port,
                                                 int adr, //tito was here
					                             I2CMultiplexerDriver& breakout,
                                                 uint8_t breakoutChannel,
                                                 Rev2mDistanceSensor::DistanceUnit units,
					                             Rev2mDistanceSensor::RangeProfile profile):
                                                 m_breakout(breakout),
                                                 m_breakoutChannel(breakoutChannel)
{
    
    SetActive(false);
	m_pDistanceSensor = new RevDistanceSensorDriver(Port, units, profile);
	m_pDistanceSensor->StartMeasuring();
}


double MuxDistanceSensorDriver::GetDistance()
{
    SetActive();
    m_pDistanceSensor->GetMeasurementData();
    return m_pDistanceSensor->GetDistance(); 
}


bool MuxDistanceSensorDriver::IsRangeValid()
{
    SetActive();
    return m_pDistanceSensor->IsRangeValid();
}


void MuxDistanceSensorDriver::SetActive(bool isReady)
{
    // isChanged determines if the channel has changed. 
    // If it's true, then the sensor needs to reinitialize.
    // Otherwise, the sensor was already active and it's fine.
    
    bool isChanged = m_breakout.SetChannel(1 << (m_breakoutChannel));
    if (isReady and isChanged)
    {
       m_pDistanceSensor->StartMeasuring();
    }
}


bool MuxDistanceSensorDriver::StatusIsFatal()
{
    SetActive();
    return m_pDistanceSensor->StatusIsFatal();
}


void MuxDistanceSensorDriver::Init(bool isOn)
{
    SetActive();
    if(isOn == true)
    {
        m_pDistanceSensor->Init(true);
    }
    else if(isOn == false) 
    {
        m_pDistanceSensor->DisableInit();
    }
}


