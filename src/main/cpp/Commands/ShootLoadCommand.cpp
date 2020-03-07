/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/ShootLoadCommand.h"
#include <frc/SmartDashboard/SmartDashboard.h>

ShootLoadCommand::ShootLoadCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, 
double encoderWanted, double motorSpeed) 
{
  m_pLoader = pLoader;
  m_pShooter = pShooter;
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements(pLoader);
  AddRequirements(pShooter);
  m_encoderWanted = encoderWanted;
  m_motorSpeed = motorSpeed;
}

// Called when the command is initially scheduled.
void ShootLoadCommand::Initialize() 
{

}

// Called repeatedly when this Command is scheduled to run
void ShootLoadCommand::Execute() 
{
  if(m_isBusy == true)
  {
    return;
  }
  Util::Log("ShootLoad isBusy", m_isBusy);
  m_isBusy = true;
  double encoderLowTol = m_encoderWanted - m_encoderTolerance;
  double encoderHighTol = m_encoderWanted + m_encoderTolerance;
  Util::Log("ShootLoad LowTol", encoderLowTol);
  Util::Log("ShootLoad HighTol", encoderHighTol);

  //Set shooter motor
  if (m_motorSpeed != 0.0)
  {
    m_pShooter->SetShootMotor(m_motorSpeed);
  } 
  else
  {
    m_pShooter->SetShootMotor(1.0);
  }

  //Check if there isn't a ball in the Photogate
  /*
  if(m_pLoader->GetPhotogate() != true)
  {
    //If there isn't a ball there do nothing
    m_pShooter->Stop();
    m_isFinished = true;
    m_isBusy = false;
    return;
  }  */

  double shooterSpeed = m_pShooter->GetEncoderSpeed();
  while(shooterSpeed < encoderLowTol && shooterSpeed > encoderHighTol)
  {
    if(shooterSpeed < encoderLowTol)
    {
      m_motorSpeed += 0.1;
    }
    else if(shooterSpeed > encoderHighTol)
    {
      m_motorSpeed -= 0.1;
    }

    shooterSpeed = m_pShooter->GetEncoderSpeed();
  }

/*
  m_pLoader->Load(1.0);
  Util::DelayInSeconds(m_oneBallTime);
  m_pLoader->Stop();
  //Not Sure yet if we should have this
  m_pShooter->Stop();*/
  
  m_isBusy = false;
  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void ShootLoadCommand::End(bool interrupted) 
{
  m_pLoader->Stop();
  m_pShooter->Stop();
}

// Returns true when the command should end.
bool ShootLoadCommand::IsFinished() 
{ 
  return m_isFinished; 
}
