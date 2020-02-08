/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRocky.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc/SmartDashboard/SmartDashboard.h>

RobotContainerRocky::RobotContainerRocky()
 {
  m_pDrive = new DriveTrainSubsystemRocky;
  m_pTurret = new TurretSubsystemRocky;
  m_pLoader = new LoaderSubsystemRocky;
  m_pShooter = new ShooterSubsystemRocky;
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
  //DIO variable meant to switch the autonomous scenario
  int dioAutoSwitcher = 1;
  dioAutoSwitcher = ReadDioSwitch();
  frc::SmartDashboard::PutBoolean("Case 1", false);
  frc::SmartDashboard::PutBoolean("Case 2", false);
  frc::SmartDashboard::PutBoolean("Case 3", false);
  frc::SmartDashboard::PutBoolean("Case Default", false);
  switch(dioAutoSwitcher)
  {
    case 1:
      return &m_autoInFrontTargetZone;
      return &m_follower;
      frc::SmartDashboard::PutBoolean("Case 1", true);
      break;
    case 2:
      return &m_autoBetweenTargetZoneLoadingZone;
      frc::SmartDashboard::PutBoolean("Case 2", true);
      break;
    case 3:
      return &m_autoInFrontLoadingZone;
      frc::SmartDashboard::PutBoolean("Case 3", true);
      break;
    default:
      return &m_autoInFrontTargetZone;
      frc::SmartDashboard::PutBoolean("Case Default", true);
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
