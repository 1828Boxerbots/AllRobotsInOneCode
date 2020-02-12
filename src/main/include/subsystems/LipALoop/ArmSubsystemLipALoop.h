/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "../ArmSubsystemBase.h"	
#include <frc/Servo.h>	
#include <frc/smartdashboard/SmartDashboard.h>

class ArmSubsystemLipALoop : public ArmSubsystemBase {
 public:
  ArmSubsystemLipALoop();

  virtual void ResetToZero();	
  virtual double GetOneDegree();	
  virtual double GetScale();	
  virtual double GetMinLimit();	
  virtual double GetMaxLimit();	
  virtual void Init();	
  virtual void DisableInit();
  virtual void LiftMotor(double angle);	
  virtual void LiftArmUp();
  virtual void LiftArmDown();
  virtual void MoveArmStop();

  private:
  //object

  #ifndef NOHW
  frc::Servo m_armServo{PWM_ARMSERVO_LIPALOOP};
  #endif

  //Variables
  double m_oneDegree = 0.005;
  double m_motorScale = 0.5;

  const double ARM_MIN = 0.16;	
  const double ARM_MAX = 0.65;
};
