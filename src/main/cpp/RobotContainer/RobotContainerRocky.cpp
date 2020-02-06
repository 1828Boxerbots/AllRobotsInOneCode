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
   m_pDrive = new DriveTrainSubsystemRocky();
  // Configure the button bindings
  ConfigureButtonBindings();
   m_pDrive->Init();
   SetDrive();

}

void RobotContainerRocky::ConfigureButtonBindings()
{

  // Configure your button bindings here

  SetButtonA();
  SetButtonB();

  SetLeftBumper();
  SetRightBumper();

  SetButtonX();
  SetButtonY();

 //Allign Control
  SetStartButton();
  
}

frc2::Command* RobotContainerRocky::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return &m_autoInFrontTargetZone;
}
