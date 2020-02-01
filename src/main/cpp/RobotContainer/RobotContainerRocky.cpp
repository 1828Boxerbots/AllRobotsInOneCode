/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRocky.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerRocky::RobotContainerRocky()
 {
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

/*
  frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
  startButton.WhenPressed(&m_encoderTest);
  frc2::Button leftTrigger{[this] {return m_controller.GetTriggerAxis(frc::GenericHID::kLeftHand);}};
  leftTrigger.WhenPressed(&m_resetEncoder);
  */

 //Allign Control
  frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
  startButton.WhenPressed(&m_follower);
  
}

frc2::Command* RobotContainerRocky::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autoTestOne;
}
