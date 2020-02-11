/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../ArmSubsystemBase.h"
#include <frc/Victor.h>


class ArmSubsystemRobot2020 : public ArmSubsystemBase {
 public:
  ArmSubsystemRobot2020();

  virtual void Init();
  virtual void LiftMotor(double speed);
  virtual void DisableInit();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
 #ifndef NOHW
  frc::Victor m_armMotor{PWM_ARMMOTOR_ROBOT2020};
  
 #endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
