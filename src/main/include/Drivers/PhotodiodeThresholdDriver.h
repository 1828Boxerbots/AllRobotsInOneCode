/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>

class PhotodiodeThresholdDriver {
 public:
  PhotodiodeThresholdDriver(int port);

  /*
  * Digital Light Sensor
  * This sensor will be driven low based on light level
  */
  bool Get();
  void Init();

  private:
  frc::DigitalInput *m_pDevice = nullptr;
};