/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include "../LoaderSubsystemBase.h"

class LoaderSubsystemRobot2020 : public LoaderSubsystemBase {
 public:
  LoaderSubsystemRobot2020();

  virtual void SetLoadMotor(double speed);

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
  #ifndef NOHW
  frc::Spark m_loaderMotorBottom {PWM_LOADMOTORBOTTOM_ROBOT2020};
  frc::Spark m_loaderMotorMiddle {PWM_LOADMOTORMIDDLE_ROBOT2020};
  frc::Spark m_loaderMotorTop {PWM_LOADMOTORTOP_ROBOT2020};
  #endif
  
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};