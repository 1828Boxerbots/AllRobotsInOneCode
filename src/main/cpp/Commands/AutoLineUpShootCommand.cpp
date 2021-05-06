// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/AutoLineUpShootCommand.h"

AutoLineUpShootCommand::AutoLineUpShootCommand(DriveTrainSubsystemBase *pDrive, double wantedDistance, ShooterSubsystemBase *pShoot, LoaderSubsystemBase *pLoad) 
{
  m_pDrive = pDrive;
  m_pShoot = pShoot;
  m_pLoad = pLoad;
    AddRequirements(m_pDrive);
    AddRequirements(m_pLoad);
    AddRequirements(m_pShoot);
  // Use addRequirements() here to declare subsystem dependencies.
    m_wantedDistance = wantedDistance;
}

// Called when the command is initially scheduled.
void AutoLineUpShootCommand::Initialize() 
{
  m_isFinished = false;
  int height;
  int width;
  m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_A);
  m_pDrive->GetVisionSize(&height, &width);
  m_pDrive->SetVisionCrop(0, height*0.75, width, height*0.25);
}

// Called repeatedly when this Command is scheduled to run
void AutoLineUpShootCommand::Execute() 
{
  if(m_isFinished == false)
  {
    m_pDrive->AlignWithVision(0.0, 50, true, false);
    //m_pDrive->PrecisionMovementLidar(m_wantedDistance);
    m_pShoot->Shoot(-1.0);
    Util::DelayInSeconds(5.0);
    m_pLoad->Load(0.5, 0.0);
    Util::DelayInSeconds(4.0);
    m_pShoot->DisableInit();
    m_pLoad->Load(0.0, 0.0);
  // m_pShoot->Shoot(0.0);
    m_isFinished = true;
  }

}

// Called once the command ends or is interrupted.
void AutoLineUpShootCommand::End(bool interrupted) 
{
  //m_pShoot->Shoot(0.0);
}

// Returns true when the command should end.
bool AutoLineUpShootCommand::IsFinished() 
{
  return m_isFinished;
}
