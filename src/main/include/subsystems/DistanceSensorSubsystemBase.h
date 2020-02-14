/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/I2C.h>
#include "DriveTrainSubsystemBase.h"

class DistanceSensorSubsystemBase : public frc2::SubsystemBase {
 public:
  DistanceSensorSubsystemBase();

  virtual void Init() {}
  virtual double GetDistanceInInch() {return -1.0;}
  virtual double GetDistanceInCM() {return -1.0;}

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 protected:
 double m_distance = 0.0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
