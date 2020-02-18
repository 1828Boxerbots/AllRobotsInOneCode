/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "rev/Rev2mDistanceSensor.h"

class RevDistanceSensorDriver {
 public:
  RevDistanceSensorDriver(rev::Rev2mDistanceSensor::Port port = rev::Rev2mDistanceSensor::Port::kOnboard, rev::Rev2mDistanceSensor::DistanceUnit unit = rev::Rev2mDistanceSensor::DistanceUnit::kInches);
  void Init();
  void DisableInit();
  double GetDistance();
  private:
  rev::Rev2mDistanceSensor *m_pDevice = nullptr;
};

// Finished 2/17/20. Untested
