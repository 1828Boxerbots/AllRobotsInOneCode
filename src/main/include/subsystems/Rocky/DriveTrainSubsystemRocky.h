/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include <frc/Encoder.h>
#include "../DriveTrainSubsystemBase.h"
#include <frc/ADXRS450_Gyro.h>
#include "../../Drivers/AM3313HallEffectDriver.h"

class DriveTrainSubsystemRocky : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemRocky();

  void SetMotorL(double speed) override;
  void SetMotorR(double speed) override; 
  double GyroGetAngle() override;
  void GyroInit() override;
  void Init() override;
  double GetLeftEncoderInch() override;
  double GetRightEncoderInch() override;
  void ResetEncoder() override;
  void GetHallEffect();
  void Periodic() override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_ROCKY};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_ROCKY};
  frc::Encoder m_leftEncoder{DIO_LEFTENCODER_ROCKY_ONE, DIO_LEFTENCODER_ROCKY_TWO};
  frc::Encoder m_rightEncoder{DIO_RIGHTENCODER_ROCKY_ONE, DIO_RIGHTENCODER_ROCKY_TWO};
  frc::ADXRS450_Gyro m_gyro;

  AM3313HallEffectDriver m_hallEffect{6};
  #endif
  const double WHEELDIAMETER = 8.0;
  double m_scale = 0.7;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
