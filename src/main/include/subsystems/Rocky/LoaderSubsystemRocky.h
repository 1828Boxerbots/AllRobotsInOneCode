/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include "../LoaderSubsystemBase.h"

class LoaderSubsystemRocky : public LoaderSubsystemBase {
 public:
  LoaderSubsystemRocky();

  virtual void SetLoadMotor(double speed);
  bool AutoLoaderRunTime() override;
  void WaitLoader(double waitTime) override;
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
  #ifndef NOHW
  frc::Spark m_loaderMotor {PWM_LOADMOTOR_ROCKY};
  #endif
  
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
