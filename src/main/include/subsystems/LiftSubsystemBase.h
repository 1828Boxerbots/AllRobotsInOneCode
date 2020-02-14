/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "../Util.h"
#include "../Constants.h"

class LiftSubsystemBase : public frc2::SubsystemBase {
 public:
  LiftSubsystemBase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void Lift(double armSpeed);
  void Raise(bool bump);
  void Lower(bool bump);
  void StopMotor() {LiftMotor(0.0);}
  void LimitedLift(double speed);
  virtual bool UpperLimitHit() {return false;}
  virtual bool LowerLimitHit() {return false;}
  virtual void LiftMotor(double speed) {}

 private:
 protected:
 const double LIFTSPEED = 1.0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
