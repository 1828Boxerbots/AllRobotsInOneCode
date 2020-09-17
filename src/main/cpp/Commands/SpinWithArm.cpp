/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/SpinWithArm.h"

SpinWithArm::SpinWithArm(ArmSubsystemBase *pArm, SpinSubsystemBase *pSpinner, enum SpinSelector selector, double speed,
int wantedRotation)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pArm = pArm;
  m_pSpinner = pSpinner;
  AddRequirements(pArm);
  AddRequirements(pSpinner);
  m_speed = speed;
  m_selector = selector;
  m_wantedRotation = wantedRotation;
}

// Called when the command is initially scheduled.
void SpinWithArm::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void SpinWithArm::Execute() 
{
  Util::Log("SpinWithArm Selection", m_selector);

  //Checks if we are in the up arm position
  if(m_pArm->GetPosition() == 1)
  {
    //if we are not do not do anything
    return;
  }

  //Checks which function from spin we are using
  switch (m_selector)
  {
  case UseSpinMotor:
    m_pSpinner->SetSpinMotor(m_speed);
    Util::Log("SpinWithArm", 1);
    break;
  case UseSpinToColor:
    m_pSpinner->SpinToColor();
    Util::Log("SpinWithArm", 2);
    break;
  case UseSpinWithColor:
    m_pSpinner->SpinWithColor(m_speed, m_wantedRotation);
    Util::Log("SpinWithArm", 3);
    break;
  default:
    m_pSpinner->Stop();
    Util::Log("SpinWithArm", 4);
    break;
  }

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void SpinWithArm::End(bool interrupted) {}

// Returns true when the command should end.
bool SpinWithArm::IsFinished() { return m_isFinished; }