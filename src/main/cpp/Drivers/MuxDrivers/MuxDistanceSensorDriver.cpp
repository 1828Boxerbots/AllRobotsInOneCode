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
    SetActive();
	m_pDistanceSensor = new RevDistanceSensorDriver(Port, units, profile);
	m_pDistanceSensor->Init();
}


double MuxDistanceSensorDriver::GetDistance()
{
    SetActive();
    m_pDistanceSensor->GetMeasurementData();

    double retVal = m_pDistanceSensor->GetDistance();

    //m_pDistanceSensor->DisableInit();

    return retVal; 
}


bool MuxDistanceSensorDriver::IsRangeValid()
{
    SetActive();
    bool retVal = m_pDistanceSensor->IsRangeValid();

    //m_pDistanceSensor->DisableInit();

    return retVal; 
}


void MuxDistanceSensorDriver::SetActive()
{
    // isChanged determines if the channel has changed. 
    // If it's true, then the sensor needs to reinitialize.
    // Otherwise, the sensor was already active and it's fine.

    m_breakout.SetChannel(1 << (m_breakoutChannel));
<<<<<<< HEAD
    if (isReady)
    {
    m_pDistanceSensor->Init();
    }
=======
>>>>>>> parent of 912717e... Simultaneous distance sensors!
}


bool MuxDistanceSensorDriver::StatusIsFatal()
{
    SetActive();
    bool retVal = m_pDistanceSensor->StatusIsFatal();

    //m_pDistanceSensor->DisableInit();

    return retVal;
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


