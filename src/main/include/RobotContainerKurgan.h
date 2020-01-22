/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Kurgan/DriveTrainSubsystemKurgan.h"
#include "subsystems/Kurgan/LoaderSubsystemKurgan.h"
#include "subsystems/Kurgan/ShooterSubsystemKurgan.h"
#include "RobotContainerBase.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerKurgan : public RobotContainerBase{
 public:
  RobotContainerKurgan();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...

  //Controller
  DriveTrainSubsystemKurgan m_drive;
  LoaderSubsystemKurgan m_loader;
  //ShooterSubsystemKurgan m_shooter;

  frc2::RunCommand m_loaderEject{[this] {m_loader.LoadXY(m_controller.GetAButton(), m_controller.GetBButton());}, {&m_loader}};
  frc2::RunCommand m_loaderLoad{[this] {m_loader.LoadXY(m_controller.GetAButton(), m_controller.GetBButton());}, {&m_loader}};
  frc2::RunCommand m_loaderStop{[this] {m_loader.LoadXY(false, false);}, {&m_loader}};

//  frc2::RunCommand m_spinShooter{[this] {m_shooter.ShootBump(true);}, {&m_shooter}};
//  frc2::RunCommand m_shooterStop{[this] {m_shooter.ShootBump(false);}, {&m_shooter}};

  void ConfigureButtonBindings();
};
