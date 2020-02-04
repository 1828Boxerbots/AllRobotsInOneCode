/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Rocky/DriveTrainSubsystemRocky.h"
#include "subsystems/Rocky/TurretSubsystemRocky.h"
#include "subsystems/Rocky/LoaderSubsystemRocky.h"
#include "subsystems/Rocky/ShooterSubsystemRocky.h"
#include "RobotContainerBase.h"
#include "subsystems/CameraSubsystemBase.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/InstantCommand.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerRocky : public RobotContainerBase{
 public:
  RobotContainerRocky();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...

  //Controller
  DriveTrainSubsystemRocky m_drive;
  TurretSubsystemRocky m_turret;
  LoaderSubsystemRocky m_loader;
  ShooterSubsystemRocky m_shooter;
  CameraSubsystemBase m_camera;

  frc2::RunCommand m_turretTurnLeft{[this] {m_turret.Turn(m_controller.GetAButton(), m_controller.GetBButton());}, {&m_turret}};
  frc2::RunCommand m_turretTurnRight{[this] {m_turret.Turn(m_controller.GetAButton(), m_controller.GetBButton());}, {&m_turret}};
  frc2::RunCommand m_turretStop{[this] {m_turret.Turn(false, false);}, {&m_turret}};

  frc2::RunCommand m_loaderEject{[this] {m_loader.LoadXY(m_controller.GetXButton(), m_controller.GetYButton());}, {&m_loader}};
  frc2::RunCommand m_loaderLoad{[this] {m_loader.LoadXY(m_controller.GetXButton(), m_controller.GetYButton());}, {&m_loader}};
  frc2::RunCommand m_loaderStop{[this] {m_loader.LoadXY(false, false);}, {&m_loader}};

  frc2::RunCommand m_shooterSpin{[this] {m_shooter.ShootBump(false, true);}, {&m_shooter}};
  frc2::RunCommand m_shooterEject{[this] {m_shooter.ShootBump(true, false);}, {&m_shooter}};
  frc2::RunCommand m_shooterStop{[this] {m_shooter.ShootBump(false, false);}, {&m_shooter}};

  frc2::InstantCommand m_encoderTest{[this] {m_drive.ForwardInInch(1.0, 30.0);}, {&m_drive}};
  frc2::InstantCommand m_resetEncoder{[this] {m_drive.ResetEncoder();}, {&m_drive}};

  void ConfigureButtonBindings();

  frc2::SequentialCommandGroup m_align = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand {[this] {m_camera.Init();}, {&m_camera}},
    frc2::InstantCommand{[this]
    {
      int direction = m_camera.WhereToTurn(); 
      while(direction != 0)
      {
        m_camera.Tick();
        if (direction == 1)
        {
          m_drive.TurnRight(0.1);
          direction = m_camera.WhereToTurn(); 
        }
        else if (direction == -1)
        {
          m_drive.TurnLeft(0.1);
          direction = m_camera.WhereToTurn(); 
        }
        direction = m_camera.WhereToTurn(); 
      }
      m_drive.Stop();
    }, {&m_camera, &m_drive,}},
    //A function is used to get the correct Lidar Distance
    //m_drive.MoveDistance(100);

    frc2::InstantCommand {[this] {m_shooter.Shoot(ShooterSubsystemRocky::SHOOTER_SPEED_HIGH_TARGET);}, {&m_shooter}},
    frc2::WaitUntilCommand {[this] {return m_shooter.AtSetpoint(ShooterSubsystemRocky::SHOOTER_SPEED_HIGH_TARGET);}},
    frc2::InstantCommand {[this] {m_loader.LoadXY(false, true);}, {&m_loader}},
    frc2::InstantCommand {[this] {Util::DelayInSeconds(3.0);}, {}},
    frc2::InstantCommand {[this] {m_shooter.Shoot(0.0);}, {&m_shooter}},
    frc2::InstantCommand {[this] {m_loader.LoadXY(false, false);}, {&m_loader}},
  };

  frc2::SequentialCommandGroup m_follower = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand {[this] {m_camera.Init();}, {&m_camera}},
    frc2::InstantCommand{[this]
    {
      int direction = m_camera.WhereToTurn(); 
      while(true)
      {
        m_camera.Tick();
        if (direction == 1)
        {
          m_drive.TurnRight(0.3);
          direction = m_camera.WhereToTurn(); 
        }
        else if (direction == -1)
        {
          m_drive.TurnLeft(0.3);
          direction = m_camera.WhereToTurn(); 
        }
        else
        {
          m_drive.Stop();
        }
        direction = m_camera.WhereToTurn(); 
      }
    }, {&m_camera, &m_drive}}
  };
};
