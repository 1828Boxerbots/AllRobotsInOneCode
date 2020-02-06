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
  void LogEncoder();
  void PID(double targetSpeed);
  virtual double GyroGetAngle() {return -1.0;}
  virtual void GyroInit() {}
  virtual void Init();
  virtual void SetMotorL(double speed) {}
  virtual void SetMotorR(double speed) {}
  virtual void TurnLeft(double speed = 1.0);
  virtual void TurnRight(double speed = 1.0);
  virtual double GetLeftEncoderInch() {return -1.0;}
  virtual double GetRightEncoderInch() {return -1.0;}
  virtual void ResetEncoder() {}
  virtual void ForwardInSeconds(double goalTime);
  virtual void TurnInDegrees(double relativeAngle);

 const double PULSE_PER_REVOLUTION = 256.0;
 protected:
  int m_leftEncoderSim = 0;
  int m_rightEncoderSim = 0;

  double m_preErrorL = 0.0;
  double m_sumErrorL = 0.0;
  double m_preErrorR = 0.0;
  double m_sumErrorR = 0.0;
  double m_kP = 1.0;
  double m_kD = 0.01;
  double m_kI = 0.02;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
