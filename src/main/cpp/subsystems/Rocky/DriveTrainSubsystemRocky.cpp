/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rocky/DriveTrainSubsystemRocky.h"

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

double DriveTrainSubsystemRocky::GetLeftEncoderInch()
{
  double encoderDistance = m_leftEncoderSim++;
  #ifndef NOHW
  encoderDistance = m_leftEncoder.GetDistance();
  #endif
  frc::SmartDashboard::PutNumber("Left Encoder Distance", encoderDistance);
  return encoderDistance;
}

double DriveTrainSubsystemRocky::GetRightEncoderInch()
{
  double encoderDistance = m_rightEncoderSim++;
  #ifndef NOHW
  m_rightEncoder.GetDistance();
  #endif
  frc::SmartDashboard::PutNumber("Right Encoder Distance", encoderDistance);
  return encoderDistance;
}

void DriveTrainSubsystemRocky::Init()
{
  #ifndef NOHW
  m_leftMotor.SetInverted(true);
  m_rightMotor.SetInverted(false);
  m_leftEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
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
}