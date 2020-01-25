/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerLaika.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerLaika::RobotContainerLaika()
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

}

void RobotContainerLaika::ConfigureButtonBindings()
{
  //Laika has no other functions than drive as of 1/21/20
}

frc2::Command* RobotContainerLaika::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
