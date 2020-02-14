/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../ArmSubsystemBase.h"
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include "../../Drivers/HallEffectOmnipolarDriver.h"

class ArmSubsystemRobot2020 : public ArmSubsystemBase {
 public:
  ArmSubsystemRobot2020();

  virtual void Init();
  virtual void SetMotor(double speed);
  virtual double GetMotor();
  virtual void DisableInit();
  virtual void SetPosition(int pos);
  virtual int GetPosition();
  virtual void Raise(double speed = 1.0);
  virtual void Lower(double speed = 1.0);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
 #ifndef NOHW
  frc::Victor m_armMotor{PWM_ARMMOTOR_ROBOT2020};
  frc::Encoder m_armEncoder{3, 4};
  HallEffectOmnipolarDriver m_hallEffectLower{0};
  HallEffectOmnipolarDriver m_hallEffectUpper{1};
 #endif
  double m_lowValue = 0.0;
  double m_highValue = 150.0;
  
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
