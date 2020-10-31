/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Commands/AutoArmCommand.h"

AutoArmCommand::AutoArmCommand(ArmSubsystemBase *pArm, SpinSubsystemBase *pSpin, double speed, /*ArmSubsystemBase::ArmPositions*/int wantedPos)
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
  //Timer
  double time = m_timer.Get() - m_startTime;
  Util::Log("Arm Timer", time);
  m_startTime = m_timer.Get();

  m_pSpin->SetSpinMotor(0);

  Util::Log("Auto Arm Stuff", "1");

  switch (m_wantedPos)
  {
  case 1:
    if(m_pArm->GetPosition() == 1)
    {
      m_pArm->StopMotor();
      Util::Log("Auto Arm Stuff", "Up Over");
    }
    else
    {
      m_pArm->SetMotor(m_speed);
      char str[200];
      sprintf(str, "Up Going %d", upNum);
      Util::Log("Auto Arm Stuff", str);
      upNum++;
    }
    break;

  case 2:
    if(m_pArm->GetPosition() == 0)
    {
      m_pArm->StopMotor();
      Util::Log("Auto Arm Stuff", "Down Over");
    }
    else
    {
      m_pArm->SetMotor(-m_speed);
      char str[200];
      sprintf(str, "Down Going %d", downNum);
      Util::Log("Auto Arm Stuff", str);
      downNum++;
    }
    break;

  default:
    m_pArm->StopMotor();
    Util::Log("Auto Arm Stuff", "Failure");
    break;
  }
}

// Called once the command ends or is interrupted.
void AutoArmCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool AutoArmCommand::IsFinished() { return m_isFinished; }
