/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "Util.h"
#include "Constants.h"

class ArmSubsystemBase : public frc2::SubsystemBase {
 public:
  ArmSubsystemBase();

  void LiftArmUp();
  void LiftArmDown();
  virtual void ResetToZero() {}
  virtual double GetOneDegree() {return 1.0;}
  virtual double GetScale() {return 0.0;}
  virtual double GetMinLimit() {return 0.0;}
  virtual double GetMaxLimit() {return 180.0;}
  virtual void MoveArmStop() {}
  virtual void Init() {}
  virtual void LiftMotor(double angle) {}

  protected:
  double m_armAngle = 0.0;
};
