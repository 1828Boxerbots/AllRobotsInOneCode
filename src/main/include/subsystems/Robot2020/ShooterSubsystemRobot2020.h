/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../ShooterSubsystemBase.h"
#include <frc/Victor.h>
#include <frc/Encoder.h>

class ShooterSubsystemRobot2020 : public ShooterSubsystemBase {
 public:
  ShooterSubsystemRobot2020();
  void Init() override;

  void SetShootMotor(double speed) override;
  void ResetEncoder() override;
  double EncoderSpeed() override;


  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic() override;
  
 private:

 #ifndef NOHW
 frc::Victor m_shooterMotor{PWM_SHOOTMOTOR_ROBOT2020};
 frc::Encoder m_shooterEncoder{DIO_SHOOTER_ENCODER_ONE_ROBOT2020, DIO_SHOOTER_ENCODER_TWO_ROBOT2020};
 #endif

 const int PULSES_PER_ROTATION = 80;

 frc::Timer m_timer;
 double m_startTime = 0.0;
 double m_encoderRawStart = 0.0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
