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
#include "RobotContainerBase.h"

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
  virtual void DisableInit() {}

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...

  //Controller
  LoaderSubsystemRobot2020 m_loader;
  ShooterSubsystemRobot2020 m_shooter;
  SpinSubsystemRobot2020 m_spinner;

  void ConfigureButtonBindings();

  frc2::RunCommand m_loaderEject{[this] {m_loader.LoadXY(m_controller.GetXButton(), m_controller.GetYButton());}, {&m_loader}};
  frc2::RunCommand m_loaderLoad{[this] {m_loader.LoadXY(m_controller.GetXButton(), m_controller.GetYButton());}, {&m_loader}};
  frc2::RunCommand m_loaderStop{[this] {m_loader.LoadXY(false, false);}, {&m_loader}};

  frc2::RunCommand m_shooterSpin{[this] {m_shooter.ShootBump(false, true);}, {&m_shooter}};
  frc2::RunCommand m_shooterEject{[this] {m_shooter.ShootBump(true, false);}, {&m_shooter}};
  frc2::RunCommand m_shooterStop{[this] {m_shooter.ShootBump(false, false);}, {&m_shooter}};
};
