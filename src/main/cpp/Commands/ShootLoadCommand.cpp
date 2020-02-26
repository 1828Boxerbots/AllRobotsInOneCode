/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ShootLoadCommand.h"
#include <frc/SmartDashboard/SmartDashboard.h>

ShootLoadCommand::ShootLoadCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, 
  double encoderSetting, double motorSpeed) 
{
  m_pLoader = pLoader;
  m_pShooter = pShooter;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pLoader);
  AddRequirements(pShooter);
  m_encoderSetting = encoderSetting;
  m_motorSpeed = motorSpeed;
}

// Called when the command is initially scheduled.
void ShootLoadCommand::Initialize() 
{

}

// Called repeatedly when this Command is scheduled to run
void ShootLoadCommand::Execute() 
{
  // set shooter motor
  if (m_motorSpeed != 0.0)
  {
    m_pShooter->SetShootMotor(m_motorSpeed);
  } 
  else
  {
    m_pShooter->SetShootMotor(1.0);
  }
  
  // wait until encoder speed is valid
  double encoderSpeed = m_pShooter->GetEncoderSpeed();
  if (encoderSpeed != 0.0) // if an encoder exists
  {
    while (encoderSpeed < m_encoderSetting)
    {
      frc::SmartDashboard::PutNumber("ShootLoadCommand- encoder", encoderSpeed);
      encoderSpeed = m_pShooter->GetEncoderSpeed();
    }
  }
  /*
  while (m_pLoader->HasBallLoaded())
  {
    frc::SmartDashboard::PutBoolean("ShootLoadCommand- HasBallLoaded", false);
  }
  frc::SmartDashboard::PutBoolean("ShootLoadCommand- HasBallLoaded", true);
  */
  m_pLoader->SetLoadMotor(0.0);
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void ShootLoadCommand::End(bool interrupted) 
{
  m_pLoader->SetLoadMotor(0.0);
  m_pShooter->SetShootMotor(0.0);
}

// Returns true when the command should end.
bool ShootLoadCommand::IsFinished() 
{ 
  return m_isFinished; 
}
