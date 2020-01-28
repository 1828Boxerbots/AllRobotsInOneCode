/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/DriveTrainSubsystemRobot2020.h"

DriveTrainSubsystemRobot2020::DriveTrainSubsystemRobot2020() {}

void DriveTrainSubsystemRobot2020::SetMotorL(double speed) 
{
  #ifndef NOHW
  m_leftMotor.Set(speed);
  #endif
}

void DriveTrainSubsystemRobot2020::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor.Set(speed);
  #endif
}

void DriveTrainSubsystemRobot2020::Init()
{
  #ifndef NOHW
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);
  #endif
}