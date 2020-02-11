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
  m_pDrive = new DriveTrainSubsystemSLAL;
  m_pArm = new ArmSubsystemSLAL;
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerSLAL::ConfigureButtonBindings()
{
  SetLeftBumper();
  SetRightBumper();
}

void RobotContainerSLAL::SetLeftBumper()
{
  frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
  bumperL.WhenHeld(&m_armLower_Motor);
  bumperL.WhenReleased(&m_armStop_Motor);
}

void RobotContainerSLAL::SetRightBumper()
{
  frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
  bumperR.WhenHeld(&m_armLift_Motor);
  bumperR.WhenReleased(&m_armStop_Motor); 
}

frc2::Command* RobotContainerSLAL::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
