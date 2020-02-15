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
  m_leftMotor.Set(speed * m_scale);
  #endif
  frc::SmartDashboard::PutNumber("Drive Left", speed);
}

void DriveTrainSubsystemRocky::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor.Set(speed * m_scale);
  #endif
  frc::SmartDashboard::PutNumber("Drive Right", speed);
}

double DriveTrainSubsystemRocky::GyroGetAngle()
{
  m_gyroAngle = m_gyro.GetAngle();
  frc::SmartDashboard::PutNumber("GyroAngle", m_gyroAngle);
  return m_gyroAngle;
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
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  m_leftEncoder.SetReverseDirection(true);
  m_rightEncoder.SetReverseDirection(true);
  //m_leftEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
  //m_rightEncoder.SetDistancePerPulse((WHEELDIAMETER*Util::PI)/PULSE_PER_REVOLUTION);
  m_leftEncoder.SetDistancePerPulse( 1.0 / PULSE_PER_REVOLUTION * 2.0 * Util::PI * (WHEELDIAMETER/2));
  m_rightEncoder.SetDistancePerPulse( 1.0 / PULSE_PER_REVOLUTION * 2.0 * Util::PI * (WHEELDIAMETER/2));
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
void DriveTrainSubsystemRocky::GetHallEffect()
{
  frc::SmartDashboard::PutBoolean("Detecting Magnet?", m_hallEffect.Get());
}

void DriveTrainSubsystemRocky::Periodic()
{
  GetHallEffect();  
}
double DriveTrainSubsystemRocky::GetDetectionDistance()
{
  double val = m_lidar.GetDistanceInInches();
   frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
}
void DriveTrainSubsystemRocky::DetectionSoftware(double detectionDistance)
{
    frc::SmartDashboard::PutNumber("Lidar Distance", GetDetectionDistance());
    double currentDetection = GetDetectionDistance();
    frc::SmartDashboard::PutBoolean("DistanceDetection", false);
        if(currentDetection < detectionDistance)
        {
            frc::SmartDashboard::PutBoolean("DistanceDetection", true);
            //Stop();
        }
}
void DriveTrainSubsystemRocky::PrecisionMovementLidar(double wantedDistance)
{
  const double DEAD_ZONE = 5.0;
  double currentDistance = m_lidar.GetDistanceInInches();
  while(wantedDistance <  currentDistance + DEAD_ZONE && wantedDistance > currentDistance - DEAD_ZONE)
  {
    if(currentDistance < wantedDistance)
    {
      MoveTank(-.5,-.5);
    }
    if(currentDistance > wantedDistance)
    {
      MoveTank(.5,.5);
    }
    currentDistance = m_lidar.GetDistanceInInches();
  }
}