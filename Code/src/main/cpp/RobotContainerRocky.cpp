/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainerRocky.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerRocky::RobotContainerRocky()
 {
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  m_drive.Init();
  m_drive.SetDefaultCommand(frc2::RunCommand(
    [this] 
    {
      m_drive.MoveTank(m_controller.GetY(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kRightHand));
    }
    ,{&m_drive}));

    frc::SmartDashboard::PutNumber("Turret Angle", m_turret.m_turretAngle);

    /*m_turret.SetDefaultCommand(frc2::RunCommand(
    [this] 
    {
      m_turret.Turn(m_controller.GetAButton(), m_controller.GetBButton());
    }
    ,{&m_turret}));

    m_loader.SetDefaultCommand(frc2::RunCommand(
    [this] 
    {
      m_loader.Load(m_controller.GetTriggerAxis(frc::GenericHID::kLeftHand), m_controller.GetTriggerAxis(frc::GenericHID::kRightHand));
    }
    ,{&m_loader}));

    m_loader.SetDefaultCommand(frc2::RunCommand(
    [this] 
    {
      m_loader.LoadXY(m_controller.GetXButton(), m_controller.GetYButton());
    }
    ,{&m_loader}));

    m_shooter.SetDefaultCommand(frc2::RunCommand(
    [this] 
    {
      m_shooter.ShootBump(m_controller.GetBumper(frc::GenericHID::kLeftHand) || m_controller.GetBumper(frc::GenericHID::kRightHand));
    ,{&m_shooter}));*/
}

void RobotContainerRocky::ConfigureButtonBindings()
{
  //5 = Bumper left, 6 = Bumper right
  //frc2::JoystickButton(&m_controller, 5).WhenPressed(&m_turretTurnLeft);
  //frc2::JoystickButton(&m_controller, 6).WhenPressed(&m_turretTurnRight);

  // Configure your button bindings here
  frc2::Button buttonA{[this] {return m_controller.GetAButton();}};
  buttonA.WhileHeld(&m_turretTurnLeft);
  buttonA.WhenReleased(&m_turretStop);

  frc2::Button buttonB{[this] {return m_controller.GetBButton();}};
  buttonB.WhenHeld(&m_turretTurnRight);
  buttonB.WhenReleased(&m_turretStop);

  frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
  bumperL.WhenHeld(&m_spinShooter);
  bumperL.WhenReleased(&m_shooterStop);

  frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
  bumperR.WhenHeld(&m_spinShooter);
  bumperR.WhenReleased(&m_shooterStop);

  frc2::Button buttonX{[this] {return m_controller.GetXButton();}};
  buttonX.WhenHeld(&m_loaderEject);
  buttonX.WhenReleased(&m_loaderStop);
  frc2::Button buttonY{[this] {return m_controller.GetYButton();}};
  buttonY.WhenHeld(&m_loaderLoad);
  buttonY.WhenReleased(&m_loaderStop);

  
}

frc2::Command* RobotContainerRocky::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
