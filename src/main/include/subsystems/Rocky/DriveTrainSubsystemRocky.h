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

class DriveTrainSubsystemRocky : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemRocky();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 
  virtual void Init();
  virtual double GetLeftEncoderInch();
  virtual double GetRightEncoderInch();
  virtual void ResetEncoder();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_ROCKY};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_ROCKY};
  frc::Encoder m_leftEncoder{DIO_ENCODERLEFT_ROCKY_ONE, DIO_ENCODERLEFT_ROCKY_TWO};
  frc::Encoder m_rightEncoder{DIO_ENCODERRIGHT_ROCKY_ONE, DIO_ENCODERRIGHT_ROCKY_TWO};
  #endif
  const double WHEELDIAMETER = 8.0;
  double m_scaleRocky = 0.2;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
