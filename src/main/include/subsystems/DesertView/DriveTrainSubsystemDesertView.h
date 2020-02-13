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
#include <frc/I2C.h>

class DriveTrainSubsystemDesertView : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemDesertView();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 
  virtual void Init();
  void PhotoTrigger();
  void GetAnalogHallEffect();
  void GetAnalogPhotoDiode();
  void GetHallEffectSwitch();
  void GetHallEffectLatch();
  void GetHallEffectOmnipolar();
  void MultiplexerSelect(int position);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_DESERTVIEW};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_DESERTVIEW};
  frc::DigitalInput m_photogate {DIO_PHOTOGATE_DESERTVIEW};
  frc::DigitalInput m_hallEffectSwitch {DIO_HALLEFFECT_SWITCH_DESERTVIEW};
  frc::DigitalInput m_hallEffectLatch {DIO_HALLEFFECT_LATCH_DESERTVIEW};
  frc::DigitalInput m_hallEffectOmnipolar {DIO_HALLEFFECT_OMNIPOLAR_DESERTVIEW};
  frc::AnalogInput m_analogHallEffect {ANG_ANALOG_HALLEFFECT_DESERTVIEW};
  frc::AnalogInput m_analogPhotoDiode {ANG_ANALOG_PHOTODIODE_DESERTVIEW};
  frc::I2C m_multiplexer {I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_MULTIPLEXER_ROBOT2020};
  #endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
