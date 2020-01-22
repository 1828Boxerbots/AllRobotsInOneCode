/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Victor.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemKurgan : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemKurgan();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 
  virtual void Init();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Victor m_leftMotor1{PWM_LEFTMOTOR_KURGAN_ONE};
  frc::Victor m_leftMotor2{PWM_LEFTMOTOR_KURGAN_TWO};
  frc::Victor m_rightMotor1{PWM_RIGHTMOTOR_KURGAN_ONE};
  frc::Victor m_rightMotor2{PWM_RIGHTMOTOR_KURGAN_TWO};
  #endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
