/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/C418/DriveTrainSubsystemC418.h"
#include "subsystems/C418/LoaderSubsystemC418.h"
#include "subsystems/C418/ShooterSubsystemC418.h"
#include "subsystems/C418/SpinSubsystemC418.h"
#include "subsystems/C418/ArmSubsystemC418.h"
#include "subsystems/CameraSubsystemBase.h"
#include "RobotContainerBase.h"
#include "../Commands/ShootLoadCommand.h"
#include "../Commands/SpinWithArm.h"
#include "subsystems/SpinSubsystemBase.h"
#include "../include/Drivers/RevDistanceSensorDriver.h"
#include "../Commands/AutoArmCommand.h"
#include "Commands/Autonomous2021_2.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerC418 : public RobotContainerBase
{
public:
  RobotContainerC418();

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

  frc2::Command *GetAutonomousCommand() override;

  static SpinSubsystemC418::FMSColors givenColor;

private:
  //ShootLoadCommand
  ShootLoadCommand *m_pShootLoad = nullptr;
  double m_encoderSpeedWanted = -2000; //REAL ENCODER SPEED = -5500
  double m_driveSpeed = 0.5;
  double m_shootSpeed = 1.0;

  //SpinWithArm
  SpinWithArm *m_pSpinMotor = nullptr;
  SpinWithArm *m_pSpinWithColor = nullptr;
  SpinWithArm *m_pSpinToColor = nullptr;
  SpinWithArm *m_pSpinMotorOpp = nullptr;
  SpinWithArm *m_pSpinStop = nullptr;
  SpinWithArm *m_pArmUp = nullptr;
  SpinWithArm *m_pArmDown = nullptr;

  //AutoArmCommands
  AutoArmCommand *m_pAutoArmSetup = nullptr;
  AutoArmCommand *m_pAutoArmDown = nullptr;
  AutoArmCommand *m_pAutoArmUp = nullptr;

  // Pulling a pointer variable to access distance sensor driver
  I2CMultiplexerDriver *m_pMultiplexerDriver = nullptr;

  double m_speed = 1.0;
  int m_wantedRotation = 7;
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();
  void ConfigureAutonomousCommands();

  frc2::SequentialCommandGroup *m_pAutoHouse = nullptr;
  frc2::SequentialCommandGroup *m_pAutoFollowRed = nullptr;
  frc2::SequentialCommandGroup *m_pAutoChallengeOne = nullptr;

  Autonomous2021_2 *m_pScenario2 = nullptr;
};
