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

#include "../DriveTrainSubsystemBase.h"
//Util and constants
#include "Util.h"
#include "Constants.h"
//sensors
#include "Drivers/ADIS16448_IMUDriver.h"
#include "Drivers/MuxDrivers/MuxLidarDriver.h"
#include "Drivers/MuxDrivers/MuxDistanceSensorDriver.h"

class DriveTrainSubsystemRobot2020 : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemRobot2020();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 

  double IMUGetAngle();

  double GetLeftEncoderInch() override;
  double GetRightEncoderInch() override;

  double GyroGetAngle() override;
  void GyroInit() override;

  double GetLidarDetectionDistance() override;
  double GetDistanceSensorDetectionDistance() override;
  void DetectionSoftware(double detectionDistance) override;
  void PrecisionMovementLidar(double wantedDistance) override;
  void EnableAnticollision(bool enable) override;


  void Init() override;
  void IMUInit() override;

  void ResetEncoder() override;
  double GetPulsesPerRevolution() override {return PULSE_PER_REVOLUTION;}
  
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
  frc::Victor m_leftMotor{PWM_LEFTMOTOR_ROBOT2020};
  frc::Victor m_rightMotor{PWM_RIGHTMOTOR_ROBOT2020};

  frc::Encoder m_leftEncoder{DIO_LEFTENCODER_A_ROBOT2020, DIO_LEFTENCODER_B_ROBOT2020};
  frc::Encoder m_rightEncoder{DIO_RIGHTENCODER_A_ROBOT2020, DIO_RIGHTENCODER_B_ROBOT2020};

  ADIS16448_IMUDriver m_imu{};
  MuxLidarDriver m_lidar{I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_LIDAR_ROBOT2020, m_i2cBreakout, U8T_LINE_LIDAR_ROBOT2020};
  I2CMultiplexerDriver m_i2cBreakout{I2C_PORT_MULTIPLEXER_ROBOT2020};
  MuxDistanceSensorDriver m_muxDistance{};

  #endif

  double speedLimit = 0.5;
  const double PULSE_PER_REVOLUTION = 240;
  const double WHEELDIAMETER = 6.0;

  int m_beat = 0;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
