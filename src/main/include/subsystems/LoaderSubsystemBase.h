/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "../Util.h"
#include "../Constants.h"

class LoaderSubsystemBase : public frc2::SubsystemBase {
 public:
  LoaderSubsystemBase();

  void LoadMotor(double loadSpeed);
  void Load(double loadSpeed, double ejectSpeed);
  void LoadXY(bool xButton, bool yButton);
  virtual void SetLoadMotor(double speed) {}

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
 protected:
  double m_scale = 1.0;
  const double LOADSPEED = 1.0;
  const double EJECTSPEED = -1.0;
  
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
