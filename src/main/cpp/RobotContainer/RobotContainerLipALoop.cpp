/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerLipALoop.h"
#include <frc2/command/button/JoystickButton.h>	

RobotContainerLipALoop::RobotContainerLipALoop()
 {
  m_pDrive = new DriveTrainSubsystemLipALoop;
  m_pCamera = new CameraSubsystemBase;
  m_pArm = new ArmSubsystemLipALoop;
  m_pWrist = new WristSubsystemLipALoop;
  m_pHand = new HandSubsystemLipALoop;
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pCamera->Init();
  m_pDrive->Init();
  SetDrive();
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
