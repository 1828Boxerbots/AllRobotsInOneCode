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
  std::string methodName = "Execute";
  std::string commandName = "ShootLoadCommand";
  Util::Log(methodName, "starting...", commandName);

  if(m_isBusy == true)
  {
    Util::Log(methodName, "busy exiting", commandName);
    return;
  }

  Util::Log(methodName, "not busy", commandName);
  m_isBusy = true;

  //Since the speed is negative this is the "largest value"
  double encoderLowTol = m_encoderWanted - m_encoderTolerance;
  //"Smallest Value"
  double encoderHighTol = m_encoderWanted + m_encoderTolerance;
  Util::Log("ShootLoad LowTol", encoderLowTol, commandName);
  Util::Log("ShootLoad HighTol", encoderHighTol, commandName);

  //Set shooter motor
  if (m_motorSpeed != 0.0)
  {
    Util::Log("motor speed 1", m_motorSpeed, commandName);
    m_pShooter->SetShootMotor(m_motorSpeed);
  } 
  else
  {
    Util::Log("motor speed 2", 1.0, commandName);
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

  double shooterSpeed = m_pShooter->EncoderSpeed();
  while(shooterSpeed < encoderLowTol || shooterSpeed > encoderHighTol)
  {
    Util::Log(methodName, "inside While", commandName);
    if(shooterSpeed < encoderLowTol)
    {
      //m_motorSpeed += 0.1;
    }
    else if(shooterSpeed > encoderHighTol)
    {
      //m_motorSpeed -= 0.1;
    }
      
    m_pShooter->SetShootMotor(m_motorSpeed);

    shooterSpeed = m_pShooter->EncoderSpeed();

    Util::Log("ShootLoad ShooterSpeed", shooterSpeed);
  }

  Util::Log(methodName, "While done", commandName);
  Util::Log("after while motorspeed", m_motorSpeed, commandName);

  Util::DelayInSeconds(0.25);

  m_pLoader->Load(1.0);
  Util::DelayInSeconds(m_oneBallTime);
  //m_pLoader->Stop();
  //Not Sure yet if we should have this
  m_pShooter->Stop();
  m_pLoader->SetLoadMotor(0.0, -1);
  
  m_isBusy = false;
  m_isFinished = true;
  Util::Log(methodName, "Done", commandName);
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
