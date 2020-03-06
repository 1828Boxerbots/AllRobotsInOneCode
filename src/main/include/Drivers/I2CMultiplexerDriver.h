/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/I2C.h>

#include "Util.h"
#include "Constants.h"

class I2CMultiplexerDriver 
{
 public:
  I2CMultiplexerDriver(frc::I2C::Port i2cPort, int breakoutAddress = breakoutAddress_base);

  bool SetChannel(uint8_t channel, bool log = true);
  uint8_t GetChannel();

  bool StatusIsFatal() {return m_pDevice->StatusIsFatal();}

  private:

  static const uint8_t breakoutAddress_base = 0x70;
  uint8_t m_current_channel; 
  
  frc::I2C *m_pDevice = nullptr;

  std::string GetChannelName(uint8_t channel);

  uint8_t MIN_PORT = 1;
  uint8_t MAX_PORT = 8;
};

// 2/14/20
