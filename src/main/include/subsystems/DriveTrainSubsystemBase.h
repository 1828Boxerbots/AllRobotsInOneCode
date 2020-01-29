/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/Spark.h>
#include "../Util.h"
#include "../Constants.h"

class DriveTrainSubsystemBase : public frc2::SubsystemBase {
 public:
  DriveTrainSubsystemBase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void MoveTank(double leftY, double rightY);
  void MoveArcade(double X, double Y);
  void Stop();
  void Forward(double speed);
  void ForwardInInch(double speed, double inch);
  virtual void Init() {}
  virtual void SetMotorL(double speed) {}
  virtual void SetMotorR(double speed) {}
  virtual void TurnLeft(double speed = 1.0) {}
  virtual void TurnRight(double speed = 1.0) {}
  virtual double GetLeftEncoderInch() {return -1.0;}
  virtual double GetRightEncoderInch() {return -1.0;}
  virtual void ResetEncoder() {}

 const double PULSE_PER_REVOLUTION = 256.0;

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
