/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/RevDistanceSensorDriver.h"


RevDistanceSensorDriver::RevDistanceSensorDriver(Rev2mDistanceSensor::Port port, Rev2mDistanceSensor::DistanceUnit unit, Rev2mDistanceSensor::RangeProfile profile) 
{
  m_pDevice = new Rev2mDistanceSensor(port, unit, profile);   
}


void RevDistanceSensorDriver::Init(bool log) 
{
  if (log) {Util::Log("Distance Sensor Initialized?", true, "RevdistanceSensorDriver");}
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
      Util::SendErrorAndCode("Distance Sensor Range Invalid", 133, "DistanceSensorDriver.cpp");
      return -1.0;
  }
}


bool RevDistanceSensorDriver::IsRangeValid()
{
  return m_pDevice->IsRangeValid();
}


void RevDistanceSensorDriver::StartMeasuring()
{
  m_pDevice->StartMeasurement();
}


void RevDistanceSensorDriver::GetMeasurementData()
{
  return m_pDevice->GetMeasurementData();
}


