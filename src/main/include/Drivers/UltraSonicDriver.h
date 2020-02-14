/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/AnalogInput.h>

class UltraSonicDriver {
 public:
  UltraSonicDriver(int port);

  double GetDistanceInCM();
  double GetDistanceInInch();
  void SetCalibration(double value) {m_calibration = value;}

  private:
    frc::AnalogInput *m_pDevice = nullptr;
    const double CMtoIN = 0.393701;
    double m_calibration = 1.0;
};
