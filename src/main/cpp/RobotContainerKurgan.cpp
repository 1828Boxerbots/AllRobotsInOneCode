/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainerKurgan.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerKurgan::RobotContainerKurgan()
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

void RobotContainerKurgan::ConfigureButtonBindings()
{
  //Loader Controlls
  frc2::Button buttonA{[this] {return m_controller.GetAButton();}};
  buttonA.WhenHeld(&m_loaderEject);
  buttonA.WhenReleased(&m_loaderStop);
  frc2::Button buttonB{[this] {return m_controller.GetBButton();}};
  buttonB.WhenHeld(&m_loaderLoad);
  buttonB.WhenReleased(&m_loaderStop);

  //Shooter Controlls
  frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
  bumperR.WhenHeld(&m_shooterSpin);
  bumperR.WhenReleased(&m_shooterStop);
  frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
  bumperL.WhenHeld(&m_shooterEject);
  bumperL.WhenReleased(&m_shooterStop);
}

frc2::Command* RobotContainerKurgan::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
