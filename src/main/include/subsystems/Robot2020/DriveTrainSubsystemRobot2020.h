/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Spark.h>
#include "../DriveTrainSubsystemBase.h"

class DriveTrainSubsystemRobot2020 : public DriveTrainSubsystemBase {
 public:
  DriveTrainSubsystemRobot2020();

  virtual void SetMotorL(double speed);
  virtual void SetMotorR(double speed); 
  virtual void Init();
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */

 private:
 #ifndef NOHW
<<<<<<< Updated upstream
  frc::Spark m_leftMotor{PWM_LEFTMOTOR_ROBOT2020};
  frc::Spark m_rightMotor{PWM_RIGHTMOTOR_ROBOT2020};
=======
  frc::Victor m_leftMotor{PWM_LEFTMOTOR_ROBOT2020};
  frc::Victor m_rightMotor{PWM_RIGHTMOTOR_ROBOT2020};

  frc::Encoder m_leftEncoder{DIO_LEFTENCODER_A_ROBOT2020, DIO_LEFTENCODER_B_ROBOT2020};
  frc::Encoder m_rightEncoder{DIO_RIGHTENCODER_A_ROBOT2020, DIO_RIGHTENCODER_B_ROBOT2020};

  ADIS16448_IMUDriver m_imu{};
  MuxLidarDriver m_lidar{I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_LIDAR_ROBOT2020, m_i2cBreakout, U8T_LINE_LIDAR_ROBOT2020};
  I2CMultiplexerDriver m_i2cBreakout{I2C_PORT_MULTIPLEXER_ROBOT2020};

  //For both distance sensors on c418(Robot2020)
  #ifdef M_DISTANCE
  MuxDistanceSensorDriver m_muxLeftDistance{I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_LEFTDISTANCESENSOR_ROBOT2020, m_i2cBreakout, U8T_LINE_LEFTDISTANCESENSOR_ROBOT2020};
  MuxDistanceSensorDriver m_muxRightDistance{I2C_PORT_MULTIPLEXER_ROBOT2020, I2C_ADDR_RIGHTDISTANCESENSOR_ROBOT2020, m_i2cBreakout, U8T_LINE_RIGHTDISTANCESENSOR_ROBOT2020};
>>>>>>> Stashed changes
  #endif
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
