/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../../subsystems/SpinSubsystemBase.h"
#include "../I2CMultiplexerDriver.h"

class MuxColorSensorDriver {
 public:
  MuxColorSensorDriver(int port1, int port2) {}

  SpinSubsystemBase::FMSColors Get() {return SpinSubsystemBase::FMSColors::INVALID;}

};
