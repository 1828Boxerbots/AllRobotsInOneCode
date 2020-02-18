/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/RevDistanceSensorDriver.h"
#include <frc/DriverStation.h>

RevDistanceSensorDriver::RevDistanceSensorDriver(rev::Rev2mDistanceSensor::Port port, rev::Rev2mDistanceSensor::DistanceUnit unit) 
{
    m_pDevice = new rev::Rev2mDistanceSensor(port, unit);   
}

void RevDistanceSensorDriver::Init() 
{
  m_pDevice->SetAutomaticMode(true);
  m_pDevice->SetEnabled(true);
}

void RevDistanceSensorDriver::DisableInit() 
{
  m_pDevice->SetAutomaticMode(false);
  m_pDevice->SetEnabled(false);
}

double RevDistanceSensorDriver::GetDistance() 
{
  bool isValid = m_pDevice->IsRangeValid();
  if(isValid) 
  {
     //The current measured range is returned from GetRange(). By default
     // this range is returned in inches.
     return (double)m_pDevice->GetRange();
     //frc::SmartDashboard::PutNumber("Timestamp", m_distSensor.GetTimestamp());
  }
  else 
  {
      frc::DriverStation::ReportError("Distance Sensor Range Invalid");
      return -1.0;
  }
}

