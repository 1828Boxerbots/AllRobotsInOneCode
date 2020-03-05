/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <adi/ADIS16448_imu.h>

#include "Util.h"

class ADIS16448_IMUDriver 
{
 public:
  ADIS16448_IMUDriver();

  double GetTemperature();
  double GetPressure();
  double GetAccelX();
  double GetAccelY();
  double GetAccelZ();
  double GetAngleX();
  double GetAngleY();
  double GetAngleZ();
  double GetMagX();
  double GetMagY();
  double GetMagZ();

  void ResetAngles();
  void CalibrateIMU();
  void LogAllValues();

  private:
   
  frc::ADIS16448_IMU *m_pDevice = nullptr;
};

// 3/4/2020 Completed, Untested
