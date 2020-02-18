/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemRobot2020 : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemRobot2020();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 
  void Init() override;
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_ROBOT2020};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_ROBOT2020};
  #endif

  double speedLimit = 0.5;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
