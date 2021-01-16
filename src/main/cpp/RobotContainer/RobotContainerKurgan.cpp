/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerKurgan.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerKurgan::RobotContainerKurgan()
{
  m_pDrive = new DriveTrainSubsystemKurgan;
  //This is disable due to kurgan broken loader(vail pride day 2/15/20) - Aidan Clark
  m_pLoader = new LoaderSubsystemKurgan;
  m_pShooter = new ShooterSubsystemKurgan;
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerKurgan::ConfigureButtonBindings()
{
  //Loader Controlls
  SetButtonA();
  SetButtonB();

  //Shooter Controlls
  SetLeftBumper();
  SetRightBumper();
}

frc2::Command *RobotContainerKurgan::GetAutonomousCommand()
{
  // An example command will be run in autonomous
  return 0;
}

void RobotContainerKurgan::SetButtonA()
{
  frc2::Button buttonA{[this] { return m_controller.GetAButton(); }};
  buttonA.WhenHeld(&m_loaderEject);
  buttonA.WhenReleased(&m_loaderStop);
}

void RobotContainerKurgan::SetButtonB()
{
  frc2::Button buttonB{[this] { return m_controller.GetBButton(); }};
  buttonB.WhenHeld(&m_loaderLoad);
  buttonB.WhenReleased(&m_loaderStop);
}
