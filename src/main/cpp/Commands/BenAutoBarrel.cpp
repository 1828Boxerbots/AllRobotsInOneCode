// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/BenAutoBarrel.h"

BenAutoBarrel::BenAutoBarrel(DriveTrainSubsystemBase* pDrive)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  AddRequirements(m_pDrive);
}

// Called when the command is initially scheduled.
void BenAutoBarrel::Initialize() 
{
  m_isFinished = false;

  int height;
  int width;
  m_pDrive->GetVisionSize(&height, &width);
  m_pDrive->SetVisionCrop(0, height*0.75, width, height*0.25);
}

// Called repeatedly when this Command is scheduled to run
void BenAutoBarrel::Execute() 
{
  Util::Log("ChallengeOnefinished", m_isFinished);
  if(m_isFinished == false)
  {
    //Going around first cone
    m_pDrive->ForwardInInchGyro(85, 0.3);
    m_pDrive->IMUArcade(0.6, 0.17, -300);
    m_pDrive->ForwardInInchGyro(36, 0.3);
    m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_A);
    m_pDrive->AlignWithVision(-0.5, 30, true);
    m_pDrive->ForwardInInchGyro(18, 0.6);
    //Going around second cone
    m_pDrive->IMUArcade(0.6, -0.17, 330);
    m_pDrive->ForwardInInchGyro(24, 0.6);
    m_pDrive->SetLookingColorV(OldCameraVision::PURPLE_BOTTLE_A);
    m_pDrive->AlignWithVision(-0.75, 30, true);
    m_pDrive->ForwardInInchGyro(24, 0.6);
    //Going around third cone
    m_pDrive->IMUArcade(0.6, -0.16, 150);
    m_pDrive->ForwardInInchGyro(24, 0.4);
    m_pDrive->IMUArcade(0.6, -0.16, 130);
    m_pDrive->ForwardInInchGyro(24,0.6);
    m_pDrive->RotateToDegreeAbsolute(180, 0.2, 2);
    m_pDrive->ForwardInInchGyro(100, 0.5, 2);
    // m_pDrive->SetLookingColorV(OldCameraVision::RED_CONE_A);
    // m_pDrive->AlignWithVision(1.0, 30, true);
    // m_pDrive->ForwardInInchGyro(25, 0.5);
    // //Coming back to start zone 
    // m_pDrive->SetLookingColorV(OldCameraVision::ORANGE_CONE);
    // m_pDrive->AlignWithVision(-1.0, 30, false);
    // m_pDrive->ForwardInInchGyro(25, 0.5);
    // m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
    m_pDrive->AlignWithVision(0.0, 30, true);
    //m_pDrive->ForwardInInch(60,0.0,0.7);
    //m_pDrive->ForwardInInch(240, 0.0, 0.4);
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void BenAutoBarrel::End(bool interrupted) {}

// Returns true when the command should end.
bool BenAutoBarrel::IsFinished() 
{
  return m_isFinished;
}
