/*----------------------------------------------------------------------------*/	
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */	
/* Open Source Software - may be modified and shared by FRC teams. The code   */	
/* must be accompanied by the FIRST BSD license file in the root directory of */	
/* the project.                                                               */	
/*----------------------------------------------------------------------------*/	

#pragma once	

#include <frc2/command/SubsystemBase.h>	
#include <frc/smartdashboard/SmartDashboard.h>
#include "Util.h"	
#include "Constants.h"	

class ArmSubsystemBase : public frc2::SubsystemBase {	
 public:	
  ArmSubsystemBase();	

//From LipALoop
  virtual void LiftArmUp() {}
  virtual void LiftArmDown() {}
  virtual void ResetToZero() {}	
  virtual double GetOneDegree() {return 1.0;}	
  virtual double GetScale() {return 0.0;}	
  virtual double GetMinLimit() {return 0.0;}	
  virtual double GetMaxLimit() {return 180.0;}	
  virtual void MoveArmStop() {}	
  virtual void Init() = 0;
  virtual void LiftServo(double angle) {}	
  virtual void DisableInit() = 0;

//From SLAL
  void Lift(double armSpeed);
  virtual void Raise(bool bump);
  virtual void Lower(bool bump);
  void StopMotor() {LiftMotor(0.0);}
  virtual void LimitedLift(double speed);
  virtual bool UpperLimitHit() {return false;}
  virtual bool LowerLimitHit() {return false;}
  virtual void LiftMotor(double speed) {}

  protected:	
  double m_armAngle = 0.0;	
  double m_liftSpeed = 1.0;
};