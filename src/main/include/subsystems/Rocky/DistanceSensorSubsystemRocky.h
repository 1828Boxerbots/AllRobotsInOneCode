/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "../DistanceSensorSubsystemBase.h"


class DistanceSensorSubsystemRocky : public DistanceSensorSubsystemBase {
 public:
  DistanceSensorSubsystemRocky();
  double GetDistanceForward() override;
  double GetDistanceInInch() override;
  void Init() override;
  void ForwardDetectionSensor(double distance) override;

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  const int LIDAR_ADDRESS = 0x62;
  frc::I2C m_device {frc::I2C::Port::kOnboard, LIDAR_ADDRESS};
  const int ACQ_COMMAND = 0x00;
  const int ACQ_CONFIG_REG = 0x04;
  const int STATUS = 0x01;
  const int FULL_DELAY_HIGH = 0x0f;
  const int FULL_DELAY_LOW = 0x10;
  const double CMtoIN = 0.393701;
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
