/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Victor.h>
#include "../LoaderSubsystemBase.h"
#include "../../Drivers/PhotogateDriver.h"
#include "../../Drivers/SpikeDriver.h"

class LoaderSubsystemRobot2020 : public LoaderSubsystemBase {
 public:
  LoaderSubsystemRobot2020();

  enum LoaderMotors
  {
    INVALID_MOTOR = -1, MOTOR_TOP, MOTOR_BOTTOM, MOTOR_INTAKE
  };

  void SetLoadMotor(double speed = 1.0, int motorNumber = INVALID_MOTOR) override;
  void PhotogateStop(double speed) override;
  void Init() override;
  void Periodic() override;
  bool IsLoaded() override;

 private:
  #ifndef NOHW
  frc::Victor m_loaderMotorIntake {PWM_LOADMOTOR_INTAKE_ROBOT2020};
  frc::Victor m_loaderMotorBottom {PWM_LOADMOTOR_BOTTOM_ROBOT2020};
  frc::Victor m_loaderMotorTop {PWM_LOADMOTOR_TOP_ROBOT2020};

  PhotogateDriver m_photogate{DIO_PHOTOGATE_ROBOT2020};
  SpikeDriver m_spike{RLY_SPIKE_ROBOT2020};
  #endif

  int m_photoCount = 100;
  
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
