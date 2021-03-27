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

  // int *pHeight;
  // int *pWidth;
  // m_pDrive->GetVisionSize(pHeight, pWidth);
  // m_pDrive->SetVisionCrop(0, *pHeight*0.75, *pWidth, *pHeight*0.25);
}

// Called repeatedly when this Command is scheduled to run
void BackupChallengeOne::Execute() 
{
  Util::Log("ChallengeOnefinished", m_isFinished);
  if(m_isFinished == false)
  {
    //Going around first cone
    m_pDrive->ForwardInInchGyro(100, 0.3);
    m_pDrive->IMUArcade(0.6, 0.2, -300);
    m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_N);
    m_pDrive->AlignWithVision(-0.5, 50, false);
    m_pDrive->ForwardInInchGyro(50, 0.6);
    //Going around second cone
    m_pDrive->IMUArcade(0.8, -0.2, 330);
    m_pDrive->SetLookingColorV(OldCameraVision::PURPLE_BOTTLE_N);
    m_pDrive->AlignWithVision(-0.75, 30, true);
    m_pDrive->ForwardInInchGyro(48, 0.6);
    //Going around third cone
    m_pDrive->IMUArcade(0.5, -0.17, 260);
    m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_N);
    m_pDrive->AlignWithVision(1.0, 30, true);
    m_pDrive->ForwardInInchGyro(25, 0.5);
    //Coming back to start zone 
    m_pDrive->SetLookingColorV(OldCameraVision::ORANGE_CONE);
    m_pDrive->AlignWithVision(-1.0, 30, false);
    m_pDrive->ForwardInInchGyro(25, 0.5);
    m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
    m_pDrive->AlignWithVision(0.0, 30, true);
    //m_pDrive->ForwardInInch(60,0.0,0.7);
    //m_pDrive->ForwardInInch(240, 0.0, 0.4);
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void BackupChallengeOne::End(bool interrupted) {}

// Returns true when the command should end.
bool BackupChallengeOne::IsFinished() 
{
  return m_isFinished;
}
