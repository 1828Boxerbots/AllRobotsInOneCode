/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/C418/DriveTrainSubsystemC418.h"

DriveTrainSubsystemC418::DriveTrainSubsystemC418(I2CMultiplexerDriver *pMultiplexerDriver)
{
  m_pMultiplexerDriver = pMultiplexerDriver;

#ifdef M_LIDAR
  m_pLidar = new MuxLidarDriver(I2C_PORT_MULTIPLEXER_C418, I2C_ADDR_LIDAR_C418, *m_pMultiplexerDriver, U8T_LINE_LIDAR_C418);
#endif

#ifdef M_DISTANCE_LEFT
  m_pMuxLeftDistance = new MuxDistanceSensorDriver(DISTANCESENSOR_PORT_C418, I2C_ADDR_LEFTDISTANCESENSOR_C418, *m_pMultiplexerDriver, U8T_LINE_LEFTDISTANCESENSOR_C418);
#endif

#ifdef M_DISTANCE_RIGHT
  m_pMuxRightDistance = new MuxDistanceSensorDriver(DISTANCESENSOR_PORT_C418, I2C_ADDR_RIGHTDISTANCESENSOR_C418, *m_pMultiplexerDriver, U8T_LINE_RIGHTDISTANCESENSOR_C418);
#endif
}

void DriveTrainSubsystemC418::SetMotorL(double speed)
{
#ifndef NOHW
  m_leftMotor.Set(speed * speedLimit);
#endif

  m_camera.Tick();
}

void DriveTrainSubsystemC418::SetMotorR(double speed)
{
#ifndef NOHW
  m_rightMotor.Set(speed * speedLimit);
#endif

}

void DriveTrainSubsystemC418::Init()
{
#ifndef NOHW
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);

  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
  m_leftEncoder.SetReverseDirection(true);
  m_rightEncoder.SetReverseDirection(true);
  m_leftEncoder.SetDistancePerPulse((1.0 / GetPulsesPerRevolution()) * Util::PI * WHEELDIAMETER);
  m_rightEncoder.SetDistancePerPulse((1.0 / GetPulsesPerRevolution()) * Util::PI * WHEELDIAMETER);

  m_camera.Init();

  /*#ifdef M_DISTANCE_RIGHT
    m_pMuxRightDistance->Init(true);
  #endif

  #ifdef M_DISTANCE_LEFT
    m_pMuxLeftDistance->Init(true);
  #endif*/

#endif
}

void DriveTrainSubsystemC418::InitRight()
{
#ifdef M_DISTANCE_RIGHT
  m_pMuxRightDistance->Init(true);
#endif
}

void DriveTrainSubsystemC418::InitLeft()
{
#ifdef M_DISTANCE_LEFT
  m_pMuxLeftDistance->Init(true);
#endif
}

// Function for getting the current angle of the robot relative to its starting position
double DriveTrainSubsystemC418::IMUGetAngle()
{
// If this isn't giving you the correct angle, try .GetAngleZ() or .GetAngleX()
#ifdef M_IMU
  m_imuAngle = m_imu.GetAngleY();
  Util::Log("IMU Angle", m_imuAngle, "DriveTrainSubsystemC418");
  return m_gyroAngle;
#else
  return 0;
#endif
}

void DriveTrainSubsystemC418::IMUInit()
{
#ifdef M_IMU
  Util::Log("GyroInit", true, "DriveTrainSubsystemC418");
  m_imu.IMUGyroInit(true);
#endif
}

double DriveTrainSubsystemC418::GetLeftEncoderInch()
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

double DriveTrainSubsystemC418::GetRightEncoderInch()
{
  m_rightEncoderSim++;
#ifndef NOHW
  m_rightEncoderSim = m_rightEncoder.GetDistance();
  Util::Log("RightEncoder Raw", m_rightEncoder.Get(), "DriveTrainSubsystemC418");
  Util::Log("RightEncoder Direction", m_rightEncoder.GetDirection(), "DriveTrainSubsystemC418");
  Util::Log("RightEncoder Running", m_rightEncoder.GetStopped(), "DriveTrainSubsystemC418");
#endif
  LogEncoder();
  return m_rightEncoderSim;
}

void DriveTrainSubsystemC418::ResetEncoder()
{
#ifdef M_IMU
  m_leftEncoder.Reset();
  m_rightEncoder.Reset();
#endif

  m_rightEncoderSim = 0.0;
  m_leftEncoderSim = 0.0;
  LogEncoder();
}

// Currently using IMU
double DriveTrainSubsystemC418::GyroGetAngle()
{
#ifdef M_IMU
  double m_gyroAngle = m_imu.GetAngleX();
  //m_imu.LogAllValues(); //causes lag
  return m_gyroAngle;
#else
  return 0;
#endif
}

// Currently using IMU
void DriveTrainSubsystemC418::GyroInit()
{
#ifdef M_IMU
  m_imu.IMUGyroInit(true);
#endif
}

double DriveTrainSubsystemC418::GetDistanceSensorDetectionDistanceLeft()
{
  //------------------------------------
  double val = -1;
#ifndef NOHW
#ifdef M_DISTANCE_LEFT

  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  m_pMuxLeftDistance->Init(true);
  val = m_pMuxLeftDistance->GetDistance();
#endif
  Util::Log("DriveTrain Distance Left", val);
  Util::DelayInSeconds(1);
#endif
  return val;
}

double DriveTrainSubsystemC418::GetDistanceSensorDetectionDistanceRight()
{
  //-------------------------------------
  double val = -1;
#ifndef NOHW
#ifdef M_DISTANCE_RIGHT

  /*if(m_hasAntiCollision == false)
  {
    return 1;
  }*/
  m_pMuxRightDistance->Init(true);
  val = m_pMuxRightDistance->GetDistance();
#endif
  Util::Log("DriveTrain Distance Right", val);
  Util::DelayInSeconds(1);
#endif
  return val;
}

double DriveTrainSubsystemC418::GetLidarDetectionDistance()
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
void DriveTrainSubsystemC418::DetectionSoftware(double detectionDistance)
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
void DriveTrainSubsystemC418::PrecisionMovementLidar(double wantedDistance)
{
#ifdef M_LIDAR
  const double DEAD_ZONE = 5.0;
  double currentDistance = m_pLidar->GetDistanceInInches();
  while (wantedDistance < (currentDistance + DEAD_ZONE) && wantedDistance > (currentDistance - DEAD_ZONE))
  {
    if (currentDistance < wantedDistance)
    {
      MoveTank(-.5, -.5);
    }
    if (currentDistance > wantedDistance)
    {
      MoveTank(.5, .5);
    }
    currentDistance = m_pLidar->GetDistanceInInches();
  }
#endif
}

//Used to disable and enable anticollision
void DriveTrainSubsystemC418::EnableAnticollision(bool enable)
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
