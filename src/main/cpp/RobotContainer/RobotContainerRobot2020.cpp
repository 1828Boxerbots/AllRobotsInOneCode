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
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerRobot2020::ConfigureButtonBindings()
{
  //Robot2020
  frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
  bumperL.WhenHeld(&m_shooterEject);
  bumperL.WhenReleased(&m_shooterStop);

  frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
  bumperR.WhenHeld(&m_shooterSpin);
  bumperR.WhenReleased(&m_shooterStop);

  frc2::Button buttonX{[this] {return m_controller.GetXButton();}};
  buttonX.WhenHeld(&m_loaderEject);
  buttonX.WhenReleased(&m_loaderStop);
  frc2::Button buttonY{[this] {return m_controller.GetYButton();}};
  buttonY.WhenHeld(&m_loaderLoad);
  buttonY.WhenReleased(&m_loaderStop);



}

frc2::Command* RobotContainerRobot2020::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
