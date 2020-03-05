/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "DriverUtil/DistanceSensorSource.h"

class RevDistanceSensorDriver 
{
 public:
  RevDistanceSensorDriver(Rev2mDistanceSensor::Port port = Rev2mDistanceSensor::Port::kOnboard,
                          Rev2mDistanceSensor::DistanceUnit unit = Rev2mDistanceSensor::DistanceUnit::kInches,
                          Rev2mDistanceSensor::RangeProfile profile = Rev2mDistanceSensor::RangeProfile::kDefault);

  void Init();
  void DisableInit();
  void StartMeasuring();
  void GetMeasurementData();
  
  double GetDistance();
  
  bool IsRangeValid();
  bool StatusIsFatal();

  private:
  Rev2mDistanceSensor *m_pDevice = nullptr;
};

// Finished 2/17/20. Untested
