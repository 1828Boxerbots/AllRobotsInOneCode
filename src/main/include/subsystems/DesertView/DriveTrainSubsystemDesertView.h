/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include <frc/DigitalInput.h>
#include <frc/AnalogInput.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemDesertView : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemDesertView();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 
  virtual void Init();
  void PhotoTrigger();
  void GetAnalogHallEffect();
  void GetAnalogPhotoDiode();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_DESERTVIEW};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_DESERTVIEW};
  frc::DigitalInput m_photogate {DIO_PHOTOGATE_DESERTVIEW};
  frc::AnalogInput m_analogHallEffect {ANG_ANALOG_HALLEFFECT_DESERTVIEW};
  frc::AnalogInput m_analogPhotoDiode {ANG_ANALOG_PHOTODIODE_DESERTVIEW};
  #endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
