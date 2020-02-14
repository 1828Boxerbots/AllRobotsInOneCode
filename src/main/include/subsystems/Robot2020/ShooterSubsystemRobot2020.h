/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include <frc/Encoder.h>
#include "../ShooterSubsystemBase.h"

class ShooterSubsystemRobot2020 : public ShooterSubsystemBase {
 public:
  ShooterSubsystemRobot2020();

  virtual void SetShootMotor(double speed);
  void Init() override;
  void DisableInit() override;
  double GetEncoderSpeed();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:

 #ifndef NOHW
 frc::Spark m_shooterMotor {PWM_SHOOTMOTOR_ROBOT2020};
 frc::Encoder m_shooterEncoder{3,5};
 #endif

  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
