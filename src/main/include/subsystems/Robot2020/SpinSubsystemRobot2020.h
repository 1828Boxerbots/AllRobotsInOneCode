/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../include/subsystems/SpinSubsystemBase.h"
#include "Constants.h"
#include <frc/Victor.h>
#include "rev/ColorSensorV3.h"

class SpinSubsystemRobot2020 : public SpinSubsystemBase {
 public:
  SpinSubsystemRobot2020();

  void Init() override;
  int ReadColorSensor() override;
  void SetSpinMotor (double speed = 1.0) override;
  double GetNumberOfTicks(double R, double revolutions, double r) override; //inches
  double GetEncoderTicks() override;

 private:
 #ifndef NOHW
  frc::Victor m_spinMotor {PWM_SPINNERMOTOR_ROBOT2020};
  rev::ColorSensorV3 m_colorSensor {I2C_PORT_MULTIPLEXER_ROBOT2020};
 #endif
};
