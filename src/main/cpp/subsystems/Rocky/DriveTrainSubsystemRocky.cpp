/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rocky/DriveTrainSubsystemRocky.h"
#include <frc/smartdashboard/SmartDashboard.h>

DriveTrainSubsystemRocky::DriveTrainSubsystemRocky() {}

void DriveTrainSubsystemRocky::SetMotorL(double speed) 
{
  #ifndef NOHW
  m_leftMotor.Set(speed);
  #endif
}

void DriveTrainSubsystemRocky::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor.Set(speed);
  #endif
}

double DriveTrainSubsystemRocky::GyroGetAngle()
{
  return m_gyro.GetAngle();
  frc::SmartDashboard::PutNumber("GetAngle", m_gyro.GetAngle());
}

void DriveTrainSubsystemRocky::GyroInit()
{
  frc::SmartDashboard::PutBoolean("GyroInit", true);
  m_gyro.Reset();
  m_gyro.Calibrate();
}

double DriveTrainSubsystemRocky::GetLeftEncoderInch()
{
  m_leftEncoderSim++;
  #ifndef NOHW
  m_leftEncoderSim = m_leftEncoder.GetDistance();
  frc::SmartDashboard::PutNumber("LeftEncoder Raw", m_leftEncoder.Get());
  frc::SmartDashboard::PutBoolean("LeftEncoder Direction", m_leftEncoder.GetDirection());
  frc::SmartDashboard::PutBoolean("LeftEncoder Running", m_leftEncoder.GetStopped());
  #endif
  LogEncoder();
  return m_leftEncoderSim;
}

double DriveTrainSubsystemRocky::GetRightEncoderInch()
{
  m_rightEncoderSim++;
  #ifndef NOHW
  m_rightEncoderSim = m_rightEncoder.GetDistance();
  frc::SmartDashboard::PutNumber("RightEncoder Raw", m_rightEncoder.Get());
  frc::SmartDashboard::PutBoolean("RightEncoder Direction", m_rightEncoder.GetDirection());
  frc::SmartDashboard::PutBoolean("RightEncoder Running", m_rightEncoder.GetStopped());
  #endif
  LogEncoder();
  return m_rightEncoderSim;
}

void DriveTrainSubsystemRocky::Init()
{
  #ifndef NOHW
  m_leftMotor.SetInverted(true);
  m_rightMotor.SetInverted(false);
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  m_leftEncoder.SetReverseDirection(true);
  m_rightEncoder.SetReverseDirection(true);
  m_leftEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
  m_rightEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
  #endif
}

void DriveTrainSubsystemRocky::ResetEncoder()
{
  #ifndef NOHW
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  #endif

  m_rightEncoderSim = 0.0;
  m_leftEncoderSim = 0.0;
  LogEncoder();
}