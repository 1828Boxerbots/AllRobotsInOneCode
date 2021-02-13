// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "../../include/Commands/AutonomousBouncePath.h"


AutonomousBouncePath::AutonomousBouncePath(DriveTrainSubsystemBase* pDrive, double radius) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_turnRadius = radius;
  this->AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void AutonomousBouncePath::Initialize() 
{

}

// Called repeatedly when this Command is scheduled to run
void AutonomousBouncePath::Execute() 
{
  switch(m_state)
  {
    case 0:
    ProcessState0();
    break;
    case 1:
    ProcessState1();
    break;
    case 2:
    ProcessState2();
    break;
    case 3:
    ProcessState3();
    break;
  }
}

// Called once the command ends or is interrupted.
void AutonomousBouncePath::End(bool interrupted) 
{

}

// Returns true when the command should end.
bool AutonomousBouncePath::IsFinished() 
{
  return false;
}

void AutonomousBouncePath::ProcessState0()
{
  if(m_state == 0)
  {
    m_pDrive->ForwardInInch(10,0,0.5);
    m_pDrive->TimedArcade(0.6,-0.2,1.3);
    m_pDrive->ForwardInInch(6,0,0.5);
    m_state = 1;
  }
}

void AutonomousBouncePath::ProcessState1()
{
  if(m_state == 1)
  {
    m_pDrive->TurnInDegrees(160,0.6, m_turnRadius);
    m_pDrive->ForwardInInch(90,0,0.5);
    m_pDrive->TimedArcade(0.5,-0.2,1.7);
    m_pDrive->ForwardInInch(80,0,0.5);
    m_state = 2;
  }
}

void AutonomousBouncePath::ProcessState2()
{
  if(m_state == 2)
  {
    m_pDrive->TurnInDegrees(180, m_turnRadius);
    m_pDrive->ForwardInInch(100,0,0.5);
    m_pDrive->TimedArcade(0.5,-0.15, 2.5);
    m_pDrive->ForwardInInch(10,0,0.5);
    m_state = 3;
  }
}

void AutonomousBouncePath::ProcessState3()
{
  if(m_state == 3)
  {
    m_pDrive->TurnInDegrees(180);
    m_pDrive->ForwardInInch(6,0,0.5);
    m_pDrive->TimedArcade(0.6,-0.2,1.3);
    m_pDrive->ForwardInInch(10,0,0.5);
    m_state = 4;
  }
}