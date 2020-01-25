/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DesertView/DriveTrainSubsystemDesertView.h"

DriveTrainSubsystemDesertView::DriveTrainSubsystemDesertView() {}

void DriveTrainSubsystemDesertView::SetMotorL(double speed) 
{
  #ifndef NOHW
  m_leftMotor.Set(speed);
  #endif
}

void DriveTrainSubsystemDesertView::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor.Set(speed);
  #endif
}

void DriveTrainSubsystemDesertView::Init()
{
  #ifndef NOHW
  m_leftMotor.SetInverted(true);
  m_rightMotor.SetInverted(false);
  #endif
}