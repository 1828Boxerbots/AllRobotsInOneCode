/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../../subsystems/SpinSubsystemBase.h"
#include "../I2CMultiplexerDriver.h"
#include "../ColorSensorDriver.h"

#include <frc/I2C.h>

class MuxColorSensorDriver 
{
 public:
  MuxColorSensorDriver(frc::I2C::Port i2cPort, I2CMultiplexerDriver &breakout, uint8_t breakoutChannel);
  
  void SetActive();
	SpinSubsystemBase::FMSColors GetColor();
	bool StatusIsFatal();

  SpinSubsystemBase::FMSColors Get() {return SpinSubsystemBase::FMSColors::INVALID;}
  private:
   I2CMultiplexerDriver &m_breakout;
	 uint8_t m_breakoutChannel;
	 frc::I2C::Port m_i2cPort;
   ColorSensorDriver* m_colorSensor;
};
