/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/AnalogInput.h>

class PhotodiodeAnalogDriver {
 public:
  PhotodiodeAnalogDriver(int port);

  /**
  * Analog Hall Effect Example
  * This sensor outputs a voltage based on the brighness shone on the sensor. 0V for little light. 5v for high intensity
  */
  double Get();
  void Init();

  private:
  frc::AnalogInput *m_pDevice = nullptr;
};