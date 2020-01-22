/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Laika/DriveTrainSubsystemLaika.h"

DriveTrainSubsystemLaika::DriveTrainSubsystemLaika() {}

void DriveTrainSubsystemLaika::SetMotorL(double speed) 
{
  #ifndef NOHW
  m_leftMotor1.Set(speed);
  m_leftMotor2.Set(speed);
  #endif
}

void DriveTrainSubsystemLaika::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor1.Set(speed);
  m_rightMotor2.Set(speed);
  #endif
}

void DriveTrainSubsystemLaika::Init()
{
  #ifndef NOHW
  m_leftMotor1.SetInverted(true);
  m_leftMotor2.SetInverted(true);
  m_rightMotor1.SetInverted(false);
  m_rightMotor2.SetInverted(false);
  #endif
}