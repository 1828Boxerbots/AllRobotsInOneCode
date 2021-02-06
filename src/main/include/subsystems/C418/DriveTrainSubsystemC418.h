/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//Motor inclusions
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <frc/drive/DifferentialDrive.h>

#include "../DriveTrainSubsystemBase.h"
//Util and constants
#include "Util.h"
#include "Constants.h"
//sensors
#include "Drivers/ADIS16448_IMUDriver.h"
#include "Drivers/MuxDrivers/MuxLidarDriver.h"
#include "Drivers/MuxDrivers/MuxDistanceSensorDriver.h"
#include "Drivers/RevDistanceSensorDriver.h"

#include "Drivers/CameraDrivers/RobotVision.h"
#include "Drivers/CameraDrivers/OldCameraVision.h"
#include "Drivers/CameraDrivers/CameraVision.h"

class DriveTrainSubsystemC418 : public DriveTrainSubsystemBase
{
public:
  DriveTrainSubsystemC418(I2CMultiplexerDriver *pMultiplexerDriver);

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed);

  void GoAroundCone(bool turnRight) override;

  double IMUGetAngle() override;

  double GetLeftEncoderInch() override;
  double GetRightEncoderInch() override;

  double GyroGetAngle() override;
  void GyroInit() override;

  double GetLidarDetectionDistance() override;
  double GetDistanceSensorDetectionDistanceLeft() override;
  double GetDistanceSensorDetectionDistanceRight() override;
  //void DetectionSoftware(double detectionDistance) override;
  void PrecisionMovementLidar(double wantedDistance) override;
  void EnableAnticollision(bool enable) override;
  void InitRight() override;
  void InitLeft() override;
  // void MoveArcade(double X, double Y) override;
  void SetVisionFMSColor(OldCameraVision::VisionColors colors) override;

#ifdef M_DISTANCE_LEFT
  //bool IsDistanceLeftActive() override {return true;}
#endif
#ifdef M_DISTANCE_RIGHT
  //bool IsDistanceRightActive() override {return true;}
#endif

  void Init() override;
  void IMUInit() override;

  void ResetEncoder() override;
  double GetPulsesPerRevolution() override { return PULSE_PER_REVOLUTION; }

  double WhereToTurnVision( double deadZoneLocation = 0.0, int deadZoneRange = 100) override;

  void SetHSVHigh(int HSV, int value) override;
  void SetHSVLow(int HSV, int value) override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

private:
#ifndef NOHW
  frc::Victor m_leftMotor{PWM_LEFTMOTOR_C418};
  frc::Victor m_rightMotor{PWM_RIGHTMOTOR_C418};
  //frc::DifferentialDrive m_difDrive{m_leftMotor, m_rightMotor};

  frc::Encoder m_leftEncoder{DIO_LEFTENCODER_A_C418, DIO_LEFTENCODER_B_C418};
  frc::Encoder m_rightEncoder{DIO_RIGHTENCODER_A_C418, DIO_RIGHTENCODER_B_C418};

  OldCameraVision m_camera{0};

#ifdef M_IMU
  ADIS16448_IMUDriver m_imu{};
#endif

  I2CMultiplexerDriver *m_pMultiplexerDriver = nullptr;

#ifdef M_LIDAR
  MuxLidarDriver *m_pLidar = nullptr; // Paramaters: {I2C_PORT_MULTIPLEXER_C418, I2C_ADDR_LIDAR_C418, m_i2cBreakout, U8T_LINE_LIDAR_C418};
#endif

//For both distance sensors on C418
#ifdef M_DISTANCE_LEFT
  MuxDistanceSensorDriver *m_pMuxLeftDistance = nullptr; // Paramaters: {DISTANCESENSOR_PORT_C418, I2C_ADDR_LEFTDISTANCESENSOR_C418, m_i2cBreakout, U8T_LINE_LEFTDISTANCESENSOR_C418};
#endif

#ifdef M_DISTANCE_RIGHT
  MuxDistanceSensorDriver *m_pMuxRightDistance = nullptr; // Paramaters: {DISTANCESENSOR_PORT_C418, I2C_ADDR_RIGHTDISTANCESENSOR_C418, m_i2cBreakout, U8T_LINE_RIGHTDISTANCESENSOR_C418};
#endif

#endif

  double speedLimit = 0.5;
  const double PULSE_PER_REVOLUTION = 240;
  const double WHEELDIAMETER = 6.0;

  int m_beat = 0;
  int distance_beatR = 0;
  int distance_beatL = 0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
