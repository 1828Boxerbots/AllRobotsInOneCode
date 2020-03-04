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
#include "../../Drivers/ColorSensorDriver.h"

class SpinSubsystemRobot2020 : public SpinSubsystemBase {
 public:
  
  SpinSubsystemRobot2020();

  void MultiplexerSelect(int position);
  void Init() override;
  void SetSpinMotor (double speed = 1.0) override;
  double GetEncoderTicks() override;
  double GetTicksPerRevolution() override;
  void SpinWithColor(double speed = 1.0, int wantedRotation = 7) override;
  FMSColors ReadColorSensor() override;

 private:
 #ifndef NOHW
  frc::Victor m_spinMotor {PWM_SPINNERMOTOR_ROBOT2020};
  frc::Encoder m_spinEncoder {DIO_SPINNER_ENCODER_ONE_ROBOT2020, DIO_SPINNER_ENCODER_TWO_ROBOT2020};
  frc::I2C m_multiplexer {I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_MULTIPLEXER_ROBOT2020};
  //REPLACE PORTS
  ColorSensorDriver m_colorSensor {I2C_PORT_COLORSENSOR_TEST};
 #endif

 double m_scale = 1.0;
};
