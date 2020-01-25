/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerSLAL.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerSLAL::RobotContainerSLAL()
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

void RobotContainerSLAL::ConfigureButtonBindings()
{
    frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
    bumperL.WhenHeld(&m_armLower);
    bumperL.WhenReleased(&m_armStop);
    frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
    bumperR.WhenHeld(&m_armLift);
    bumperR.WhenReleased(&m_armStop); 
}

frc2::Command* RobotContainerSLAL::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
