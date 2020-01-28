/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class SpinSubsystemBase : public frc2::SubsystemBase {
 public:
  SpinSubsystemBase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void SpinSomeTimes(double R, double r, double revolutions = 4.0);
  void SpinSomeTimesEncoders(double R, double r, double revolutions = 4.0);
  virtual void SetSpinMotor (double speed = 1.0) {}
  virtual double GetMotorVoltage () {return 1.0;}

 protected:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  const double MOTORVELOCITY = 1;
};
