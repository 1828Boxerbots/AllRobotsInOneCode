/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerLipALoop.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerLipALoop::RobotContainerLipALoop()
 {

  // Configure the button bindings
  ConfigureButtonBindings();

  //Initializing all Subsystems
  m_drive.Init();
  m_camera.Init();
  //TeleOp Drive
  m_drive.SetDefaultCommand(frc2::RunCommand(
    [this] 
    {
      m_drive.MoveTank(m_controller.GetY(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kRightHand));
    }
    ,{&m_drive}));

}

void RobotContainerLipALoop::ConfigureButtonBindings()
{
  
    //Arm Controlls
    frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
    bumperR.WhenHeld(&m_armDown);
    bumperR.WhenReleased(&m_armStop);
    frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
    bumperL.WhenHeld(&m_armUp);
    bumperL.WhenReleased(&m_armStop);

    //Wrist Controlls
    frc2::Button buttonA{[this] {return m_controller.GetAButton();}};
    buttonA.WhenHeld(&m_wristUp);
    buttonA.WhenReleased(&m_wristStop);
    frc2::Button buttonB{[this] {return m_controller.GetBButton();}};
    buttonB.WhenHeld(&m_wristDown);
    buttonB.WhenReleased(&m_wristStop);

    //Hand Controlls
    frc2::Button buttonX{[this] {return m_controller.GetXButton();}};
    buttonX.WhenHeld(&m_handUp);
    buttonX.WhenReleased(&m_handStop);
    frc2::Button buttonY{[this] {return m_controller.GetYButton();}};
    buttonY.WhenHeld(&m_handDown);
    buttonY.WhenReleased(&m_handStop);

    //Allign Control
    frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
    startButton.WhenPressed(&m_follower);
}

frc2::Command* RobotContainerLipALoop::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}
