/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRocky.h"
#include <frc2/command/button/JoystickButton.h>
#

RobotContainerRocky::RobotContainerRocky()
 {
  m_pDrive = new DriveTrainSubsystemRocky;
  m_pTurret = new TurretSubsystemRocky;
  m_pLoader = new LoaderSubsystemRocky;
  m_pShooter = new ShooterSubsystemRocky;
  //m_pLidar = new DistanceSensorSubsystemBase();
  // Configure the button bindings
  ConfigureButtonBindings();
  m_pShooter->Init();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerRocky::ConfigureButtonBindings()
{

  // Configure your button bindings here

  SetButtonA();
  SetButtonB();

  //SetLeftBumper();
  SetRightBumper();

  SetButtonX();
  SetButtonY();

 //Allign Control
  SetStartButton();
  
}

int RobotContainerRocky::ReadDioSwitch()
{
  return 1;
}
frc2::Command* RobotContainerRocky::GetAutonomousCommand() {
  // An example command will be run in autonomous
  int dioAutoSwitcher = 1;
  dioAutoSwitcher = ReadDioSwitch();
  switch(dioAutoSwitcher)
  {
    case 1:
      return &m_autoInFrontTargetZone;
      return &m_follower;
      break;
    case 2:
      return &m_autoBetweenTargetZoneLoadingZone;
      break;
    case 3:
      return &m_autoInFrontLoadingZone;
      break;
  }
  return nullptr;
}

void RobotContainerRocky::Init() 
{
  m_pDrive->Init();
  m_pShooter->Init();
}

void RobotContainerRocky::DisableInit() 
{
  m_pShooter->DisableInit(); 
}
