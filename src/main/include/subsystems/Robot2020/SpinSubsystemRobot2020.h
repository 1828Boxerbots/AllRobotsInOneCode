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
#include <frc/Encoder.h>
#include <frc/I2C.h>
#include "../../Drivers/MuxDrivers/MuxColorSensorDriver.h"
#include "../../Drivers/I2CMultiplexerDriver.h"

class SpinSubsystemRobot2020 : public SpinSubsystemBase {
 public:
  
  SpinSubsystemRobot2020();

  void Periodic() override;

  void Init() override;
  void SetSpinMotor (double speed = 1.0) override;
  double GetTicksPerRevolution() override;
  void SpinWithColor(double speed = 1.0, int wantedRotation = 7) override;
  std::string GetColor() override; 
  FMSColors ReadColorSensor() override;

 private:
 #ifndef NOHW
  frc::Victor m_spinMotor {PWM_SPINNERMOTOR_ROBOT2020};
  I2CMultiplexerDriver m_multiplexer{I2C_PORT_MULTIPLEXER_ROBOT2020};
  MuxColorSensorDriver m_colorSensor{I2C_PORT_MULTIPLEXER_ROBOT2020, m_multiplexer, U8T_LINE_COLORSENSOR_ROBOT2020};
 #endif

 double m_scale = 0.5;

 int m_beatColorRead = 0;
};
