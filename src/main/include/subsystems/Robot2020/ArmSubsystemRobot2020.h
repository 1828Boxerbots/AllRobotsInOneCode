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
#include <frc/AnalogEncoder.h>
#include "../../Drivers/HallEffectOmnipolarDriver.h"

class ArmSubsystemRobot2020 : public ArmSubsystemBase {
 public:
  ArmSubsystemRobot2020();

  void Init() override;
  void SetMotor(double speed) override;
  double GetMotor() override;
  void DisableInit() override;
  void SetPosition(int pos) override;
  int GetPosition() override;
  void Raise(double speed = 1.0) override;
  void Lower(double speed = 1.0) override;
  void LiftArmUp(double scale = 0, double speed = 1.0) override;
  void LiftArmDown(double scale = 0, double speed = 1.0) override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
 #ifndef NOHW
  frc::Victor m_armMotor{PWM_ARMMOTOR_ROBOT2020};
  frc::Encoder m_armEncoder{DIO_ARM_ENCODER_ONE_ROBOT2020, false, k1X};
  HallEffectOmnipolarDriver m_hallEffectLower{DIO_HALLEFFECT_LOWER_ROBOT2020};
  HallEffectOmnipolarDriver m_hallEffectUpper{DIO_HALLEFFECT_UPPER_ROBOT2020};
 #endif
  double m_scale = 0.5;
  double m_lowValue = 0.0;
  double m_highValue = 150.0;
  
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
