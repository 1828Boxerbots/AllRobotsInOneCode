// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/BackupChallengeOne.h"

BackupChallengeOne::BackupChallengeOne(DriveTrainSubsystemBase* pDrive)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void BackupChallengeOne::Initialize() 
{
  m_isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void BackupChallengeOne::Execute() 
{
  if(m_isFinished == false)
  {
    m_pDrive->ForwardInInch(90, 0.0, 0.4);
    m_pDrive->TimedArcade(0.5, 0.2, 3.0);
    m_pDrive->ForwardInInch(90,0.0,0.4);
    m_pDrive->TimedArcade(0.5, 0.2, 3.0);
    m_pDrive->ForwardInInch(90, 0.0, 0.4);
    m_pDrive->TimedArcade(0.5, 0.2, 3.0);
    m_pDrive->ForwardInInch(240, 0.0, 0.4);
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void BackupChallengeOne::End(bool interrupted) {}

// Returns true when the command should end.
bool BackupChallengeOne::IsFinished() {
  return m_isFinished;
}
