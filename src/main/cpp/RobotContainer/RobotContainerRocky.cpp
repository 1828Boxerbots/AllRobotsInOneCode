/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRocky.h"
#include <frc2/command/button/JoystickButton.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include "../include/Drivers/DPDTSwitchDriver.h"

RobotContainerRocky::RobotContainerRocky()
 {
  m_pDrive = new DriveTrainSubsystemRocky;
  m_pTurret = new TurretSubsystemRocky;
  m_pLoader = new LoaderSubsystemRocky;
  m_pShooter = new ShooterSubsystemRocky;
  m_pCamera = new CameraSubsystemBase(m_pDrive);

  frc::SmartDashboard::PutString("test","test");

  // Configure the button bindings
  ConfigureButtonBindings();
  m_pShooter->Init();
  m_pDrive->Init();
  m_pCamera->Init();
  
  
  
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
//SetStartButton();
  
}

int RobotContainerRocky::ReadDioSwitch()
{
   //Object hooked up to double pole double throw switch driver {Channel A, Channel B}
  DPDTSwitchDriver dpdtSwitch{2,3};
  return dpdtSwitch.Get();

}

frc2::Command* RobotContainerRocky::GetAutonomousCommand() {

  //DIO variable meant to switch the autonomous scenario
  int dioAutoSwitcher;
  dioAutoSwitcher = ReadDioSwitch();
  frc::SmartDashboard::PutBoolean("Case 1", false);
  frc::SmartDashboard::PutBoolean("Case 2", false);
  frc::SmartDashboard::PutBoolean("Case 3", false);
  frc::SmartDashboard::PutBoolean("Case Default", false);
  switch(dioAutoSwitcher)
  {
    case 1:
    frc::SmartDashboard::PutBoolean("Case 1", true);
      return &m_autoInFrontTargetZone;
      break;

    case 2:
      frc::SmartDashboard::PutBoolean("Case 2", true);
      return &m_autoBetweenTargetZoneLoadingZone;
    case 3:
      frc::SmartDashboard::PutBoolean("Case 3", true);
      return &m_autoInFrontLoadingZone;
      break;
    default:
      frc::SmartDashboard::PutBoolean("Case Default", true);
      //return &m_autoInFrontTargetZone;
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
