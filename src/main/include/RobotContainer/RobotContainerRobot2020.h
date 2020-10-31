/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Robot2020/DriveTrainSubsystemRobot2020.h"
#include "subsystems/Robot2020/LoaderSubsystemRobot2020.h"
#include "subsystems/Robot2020/ShooterSubsystemRobot2020.h"
#include "subsystems/Robot2020/SpinSubsystemRobot2020.h"
#include "subsystems/Robot2020/ArmSubsystemRobot2020.h"
#include "subsystems/CameraSubsystemBase.h"
#include "RobotContainerBase.h"
#include "../Commands/ShootLoadCommand.h"
#include "../Commands/SpinWithArm.h"
#include "subsystems/SpinSubsystemBase.h"
#include "../include/Drivers/RevDistanceSensorDriver.h"
#include "../Commands/AutoArmCommand.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerRobot2020 : public RobotContainerBase {
 public:
  RobotContainerRobot2020();

  void Init() override;
  void DisableInit() override;
  void TeleopPeriodic() override;
  void AutonomousPeriodic() override;

  void SetButtonA() override;
  void SetButtonB() override;
  void SetButtonX() override;
  void SetButtonY() override;
  void SetRightTrigger() override;
  void SetLeftBumper() override;
  void SetRightBumper() override;
  void SetStartButton() override;
  void SetBackButton() override;
  int ReadDioSwitch();

  frc2::Command* GetAutonomousCommand();

  static SpinSubsystemRobot2020::FMSColors givenColor;

 private:

//ShootLoadCommand
  ShootLoadCommand* m_pShootLoad = nullptr;
  double m_encoderSpeedWanted = -5500;
  double m_motorSpeed = 1.0;

//SpinWithArm
  SpinWithArm* m_pSpinMotor = nullptr;
  SpinWithArm* m_pSpinWithColor = nullptr;
  SpinWithArm* m_pSpinToColor = nullptr;
  SpinWithArm* m_pSpinMotorOpp = nullptr;
  SpinWithArm* m_pSpinStop = nullptr;
  SpinWithArm* m_pArmUp = nullptr;
  SpinWithArm* m_pArmDown = nullptr;

//AutoArmCommands
  AutoArmCommand* m_pAutoArmUp = nullptr;
  AutoArmCommand* m_pAutoArmDown = nullptr;

  // Pulling a pointer variable to access distance sensor driver
  MuxDistanceSensorDriver* m_pMuxLeftDistance = nullptr;
  I2CMultiplexerDriver* m_pMultiplexerDriver = nullptr;
  MuxDistanceSensorDriver* m_pMuxRightDistance = nullptr;

  double m_speed = 1.0;
  int m_wantedRotation = 7;
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();

};
