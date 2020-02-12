/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../ArmSubsystemBase.h"
#include <frc/Victor.h>
#include "../../Drivers/HallEffectOmnipolarDriver.h"
#include "../../Drivers/AM3313HallEffectDriver.h"


class ArmSubsystemRobot2020 : public ArmSubsystemBase {
 public:
  ArmSubsystemRobot2020();

  virtual void Init();
  virtual void LiftMotor(double speed);
  virtual void DisableInit();
  virtual void ArmPosition(int pos);
  virtual void Raise(double speed = 1.0);
  virtual void Lower(double speed = 1.0);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
 #ifndef NOHW
  frc::Victor m_armMotor{PWM_ARMMOTOR_ROBOT2020};
  HallEffectOmnipolarDriver m_hallEffectLower{1};
  HallEffectOmnipolarDriver m_hallEffectUpper{2};
  AM3313HallEffectDriver m_hallEffectMiddle{3};
 #endif
enum Robot2020Positions
{
  UPPER_POS
  ,MIDDLE_POS
  ,LOWER_POS
};
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
