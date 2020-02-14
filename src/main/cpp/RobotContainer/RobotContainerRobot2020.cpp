/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRobot2020.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerRobot2020::RobotContainerRobot2020()
 {
  m_pDrive = new DriveTrainSubsystemRobot2020;
  //m_pSpin = new SpinSubsystemRobot2020;
  //m_pLoader = new LoaderSubsystemRobot2020;
  //m_pShooter = new ShooterSubsystemRobot2020;
  //m_pCamera = new CameraSubsystemRobot2020;
  //m_pArm = new ArmSubsystemRobot2020;
  //m_pDistance = new DistanceSensorSubsystemRobot2020;

  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerRobot2020::ConfigureButtonBindings()
{
//Robot2020
  //Shooter
  SetLeftBumper();
  SetRightBumper();

  //Loader
  SetButtonX();
  SetButtonY();

  //Control Panel Arm
  SetButtonA();
  SetButtonB();

}

frc2::Command* RobotContainerRobot2020::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}

void RobotContainerRobot2020::Init()
{
  if(m_pSpin != nullptr) m_pSpin->InterpretFMS(ReadFMS());
  m_pDrive->Init();
}

void RobotContainerRobot2020::SetButtonA()
{
    frc2::Button buttonA{[this] {return m_controller.GetAButton();}};
    buttonA.WhileHeld(&m_armPosition0);
}

void RobotContainerRobot2020::SetButtonB()
{
    frc2::Button buttonB{[this] {return m_controller.GetBButton();}};
    buttonB.WhileHeld(&m_armPosition1);
}