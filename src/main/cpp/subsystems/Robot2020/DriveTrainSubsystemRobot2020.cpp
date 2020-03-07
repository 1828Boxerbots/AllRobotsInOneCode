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
  m_leftMotor.Set(speed * speedLimit);
  #endif
}


void DriveTrainSubsystemRobot2020::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor.Set(speed * speedLimit);
  #endif
}


void DriveTrainSubsystemRobot2020::Init()
{
  #ifndef NOHW
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);

  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  m_leftEncoder.SetReverseDirection(true);
  m_rightEncoder.SetReverseDirection(true);
  m_leftEncoder.SetDistancePerPulse( ( 1.0 / GetPulsesPerRevolution() ) * Util::PI * WHEELDIAMETER);
  m_rightEncoder.SetDistancePerPulse( ( 1.0 / GetPulsesPerRevolution() ) * Util::PI * WHEELDIAMETER);
  #endif
}


// Function for getting the current angle of the robot relative to its starting position
double DriveTrainSubsystemRobot2020::IMUGetAngle()
{
  // If this isn't giving you the correct angle, try .GetAngleZ() or .GetAngleX()
  m_imuAngle = m_imu.GetAngleY();
  Util::Log("IMU Angle", m_imuAngle, "DriveTrainSubsystemRobot2020");
  return m_gyroAngle;
}


void DriveTrainSubsystemRobot2020::IMUInit()
{
  Util::Log("GyroInit", true, "DriveTrainSubsystemRobot2020");
  m_imu.ResetAngles();
  m_imu.CalibrateIMU();
}


double DriveTrainSubsystemRobot2020::GetLeftEncoderInch()
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

double DriveTrainSubsystemRobot2020::GetRightEncoderInch()
{
  m_rightEncoderSim++;
  #ifndef NOHW
  m_rightEncoderSim = m_rightEncoder.GetDistance();
  Util::Log("RightEncoder Raw", m_rightEncoder.Get(), "DriveTrainSubsystemRobot2020");
  Util::Log("RightEncoder Direction", m_rightEncoder.GetDirection(), "DriveTrainSubsystemRobot2020");
  Util::Log("RightEncoder Running", m_rightEncoder.GetStopped(), "DriveTrainSubsystemRobot2020");
  #endif
  LogEncoder();
  return m_rightEncoderSim;
}

void DriveTrainSubsystemRobot2020::ResetEncoder()
{
  #ifndef NOHW
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  #endif

  m_rightEncoderSim = 0.0;
  m_leftEncoderSim = 0.0;
  LogEncoder();
}

// Currently using IMU
double DriveTrainSubsystemRobot2020::GyroGetAngle()
{
  double m_gyroAngle = m_imu.GetAngleX();
  m_imu.LogAllValues();
  return m_gyroAngle;
}


// Currently using IMU
void DriveTrainSubsystemRobot2020::GyroInit()
{
  m_imu.IMUGyroInit(true);
}
double DriveTrainSubsystemRobot2020::GetDetectionDistance()
{
  double val = m_lidar.GetDistanceInInches();
   frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
}


//Makes is so that the robot doesn't run into things head on
void DriveTrainSubsystemRobot2020::DetectionSoftware(double detectionDistance)
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


//Sets up dead zone in lidar
void DriveTrainSubsystemRobot2020::PrecisionMovementLidar(double wantedDistance)
{
  const double DEAD_ZONE = 5.0;
  double currentDistance = m_lidar.GetDistanceInInches();
  while(wantedDistance <  (currentDistance + DEAD_ZONE) && wantedDistance > (currentDistance - DEAD_ZONE))
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


/*
//Gets Detection distance; used for debugging
double DriveTrainSubsystemRocky::GetDetectionDistance()
{
  double val = m_lidar.GetDistanceInInches();
   frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
}


//Makes is so that the robot doesn't run into things head on
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


//Sets up dead zone in lidar
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
*/