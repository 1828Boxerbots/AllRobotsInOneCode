/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "rev/ColorSensorv3.h"
#include "Constants.h"
#include "../subsystems/SpinSubsystemBase.h"

class ColorSensorDriver 
{
 public:
  ColorSensorDriver(frc::I2C::Port port);

  void Init() {}

  SpinSubsystemBase::FMSColors GetColor();
  std::string GetColorString();

  uint32_t GetProximity();

  static bool IsRed(double R, double G, double B);
  static bool IsGreen(double R, double G, double B);
  static bool IsBlue(double R, double G, double B);
  static bool IsYellow(double R, double G, double B);
  
  bool StatusIsFatal();

  private:

  rev::ColorSensorV3 *m_pDevice = nullptr;
};

// 3/5/2020
