/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/DriveTrainSubsystemRobot2020.h"

DriveTrainSubsystemRobot2020::DriveTrainSubsystemRobot2020(I2CMultiplexerDriver* pMultiplexerDriver)
{
  m_pMultiplexerDriver = pMultiplexerDriver;

  #ifdef M_LIDAR
    m_pLidar = new MuxLidarDriver(I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_LIDAR_ROBOT2020, *m_pMultiplexerDriver, U8T_LINE_LIDAR_ROBOT2020);
  #endif

  #ifdef M_DISTANCE_LEFT
    m_pMuxLeftDistance = new MuxDistanceSensorDriver(DISTANCESENSOR_PORT_ROBOT2020, I2C_ADDR_LEFTDISTANCESENSOR_ROBOT2020, *m_pMultiplexerDriver, U8T_LINE_LEFTDISTANCESENSOR_ROBOT2020);
  #endif

  #ifdef M_DISTANCE_RIGHT
    m_pMuxRightDistance = new MuxDistanceSensorDriver(DISTANCESENSOR_PORT_ROBOT2020, I2C_ADDR_RIGHTDISTANCESENSOR_ROBOT2020, *m_pMultiplexerDriver, U8T_LINE_RIGHTDISTANCESENSOR_ROBOT2020);
  #endif
}


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

  #ifdef M_DISTANCE_RIGHT
    m_pMuxRightDistance->Init(true);
  #endif

  #ifdef M_DISTANCE_LEFT
    m_pMuxLeftDistance->Init(true);
  #endif

  #endif
}


// Function for getting the current angle of the robot relative to its starting position
double DriveTrainSubsystemRobot2020::IMUGetAngle()
{
  // If this isn't giving you the correct angle, try .GetAngleZ() or .GetAngleX()
  #ifndef NOHW
  m_imuAngle = m_imu.GetAngleY();
  Util::Log("IMU Angle", m_imuAngle, "DriveTrainSubsystemRobot2020");
  return m_gyroAngle;
  #else 
  return 0;
  #endif
}


void DriveTrainSubsystemRobot2020::IMUInit()
{
  #ifndef NOHW
  Util::Log("GyroInit", true, "DriveTrainSubsystemRobot2020");
  m_imu.IMUGyroInit(true);
  #endif
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
  #ifndef NOHW
  double m_gyroAngle = m_imu.GetAngleX();
  m_imu.LogAllValues();
  return m_gyroAngle;
  #else
  return 0;
  #endif
}


// Currently using IMU
void DriveTrainSubsystemRobot2020::GyroInit()
{
  #ifndef NOHW
  m_imu.IMUGyroInit(true);
  #endif
}


double DriveTrainSubsystemRobot2020::GetDistanceSensorDetectionDistanceLeft()
{

  #ifdef M_DISTANCE_LEFT

  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  double val = m_pMuxLeftDistance->GetDistance();
  frc::SmartDashboard::PutNumber("DriveTrain Distance Left", val);
  return val;

  #else
  return 1;
  #endif
}


double DriveTrainSubsystemRobot2020::GetDistanceSensorDetectionDistanceRight()
{
  #ifndef NOHW

  #ifdef M_DISTANCE_RIGHT

  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  double val = m_pMuxRightDistance->GetDistance();
  frc::SmartDashboard::PutNumber("DriveTrain Distance Right", val);
  return val;
  
  #endif

  #else
  return 1;
  #endif
}

double DriveTrainSubsystemRobot2020::GetLidarDetectionDistance()
{
  #ifdef M_LIDAR
  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  double val = m_pLidar->GetDistanceInInches();
   frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
  #else
  return 1;
  #endif
}


//Makes is so that the robot doesn't run into things head on
/*
//Don't really know what this code is doing, but considering that stop is commented out, it might be the first iteration of detection software. Meat of code found in Drive base cpp
void DriveTrainSubsystemRobot2020::DetectionSoftware(double detectionDistance)
{
  #ifndef NOHW
  frc::SmartDashboard::PutNumber("Lidar Distance", GetLidarDetectionDistance());
  double currentDetection = GetLidarDetectionDistance();
  frc::SmartDashboard::PutBoolean("DistanceDetection", false);
  frc::SmartDashboard::PutBoolean("DistanceSensor DistanceDetection", false);
    if(currentDetection < detectionDistance)
    {
        frc::SmartDashboard::PutBoolean("DistanceDetection", true);
        //Stop();
    }
    currentDetection = GetLidarDetectionDistance();
    if(currentDetection < detectionDistance)
    {
      frc::SmartDashboard::PutBoolean("DistanceSensor DistanceDetection", true);
    }
    
    #endif
}
*/


//Sets up dead zone in lidar
void DriveTrainSubsystemRobot2020::PrecisionMovementLidar(double wantedDistance)
{
  #ifdef M_LIDAR
  const double DEAD_ZONE = 5.0;
  double currentDistance = m_pLidar->GetDistanceInInches();
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
    currentDistance = m_pLidar->GetDistanceInInches();
  }
  #endif
}
//Used to disable and enable anticollision
void DriveTrainSubsystemRobot2020::EnableAnticollision(bool enable)
{
  Util::Log("EAB", m_beat++, "DriveTrain2020");
  Util::Log("enabled?", enable, "DriveTrain2020");
  m_hasAntiCollision = enable;
   /*
  if(enable == true)
  {
    #ifdef M_DISTANCE
    m_pMuxLeftDistance->Init(true);
    m_pMuxRightDistance->Init(true);
    #endif
  }
  else 
  {
    #ifdef M_DISTANCE
    m_pMuxLeftDistance->Init(false);
    m_pMuxRightDistance->Init(false);
    #endif
  }*/
}
/*
Detection code ripped from Rocky code for Robot 2020
//Gets Detection distance; used for debugging
double DriveTrainSubsystemRocky::GetLidarDetectionDistance()
{
  double val = m_pLidar->GetDistanceInInches();
   frc::SmartDashboard::PutNumber("DriveTrain Lidar", val);
  return val;
}


//Makes is so that the robot doesn't run into things head on
void DriveTrainSubsystemRocky::DetectionSoftware(double detectionDistance)
{
    frc::SmartDashboard::PutNumber("Lidar Distance", GetLidarDetectionDistance());
    double currentDetection = GetLidarDetectionDistance();
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
  double currentDistance = m_pLidar->GetDistanceInInches();
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
    currentDistance = m_pLidar->GetDistanceInInches();
  }
}
*/

