/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoArmCommand.h"

AutoArmCommand::AutoArmCommand(ArmSubsystemBase *pArm, SpinSubsystemBase *pSpin, double speed, ArmSubsystemBase::ArmPositions wantedPos)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pArm = pArm;
  m_pSpin = pSpin;
  AddRequirements(pArm);
  AddRequirements(pSpin);
  m_speed = speed;
  m_wantedPos = wantedPos;
}

// Called when the command is initially scheduled.
void AutoArmCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AutoArmCommand::Execute() 
{
  m_pSpin->SetSpinMotor(0);

  switch (m_wantedPos)
  {
  case ArmSubsystemBase::ArmPositions::HIGHEST_POS:
    if(m_pArm->GetPosition() == ArmSubsystemBase::ArmPositions::HIGHEST_POS)
    {
      m_pArm->LiftArmUp(0, 0);
    }
    else
    {
      m_pArm->LiftArmUp(m_speed, m_speed);
    }
    
    m_isFinished = true;
    break;
  case ArmSubsystemBase::ArmPositions::LOWEST_POS:
    if(m_pArm->GetPosition() == ArmSubsystemBase::ArmPositions::LOWEST_POS)
    {
      m_pArm->LiftArmDown(0, 0);
    }
    else
    {
      m_pArm->LiftArmDown(m_speed, m_speed);
    }
    
    m_isFinished = true;
    break;
  
  default:
    m_pArm->LiftArmDown(0, 0);
    break;
  }
}

// Called once the command ends or is interrupted.
void AutoArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmCommand::IsFinished() { return m_isFinished; }
