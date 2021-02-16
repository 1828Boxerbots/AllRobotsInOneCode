// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/GalacticSearch/GalacticPathRedA.h"

GalacticPathRedA::GalacticPathRedA(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader, double radius) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_turnRadius = radius;
  this->AddRequirements(pDrive);
  this->AddRequirements(pLoader);
}

// Called when the command is initially scheduled.
void GalacticPathRedA::Initialize() 
{

}

// Called repeatedly when this Command is scheduled to run
void GalacticPathRedA::Execute() 
{
  switch(m_state)
  {
    case 0:
    
    break;
    case 1:
    
    break;
    case 2:
    
    break;
    case 3:
    
    break;
  }
}

// Called once the command ends or is interrupted.
void GalacticPathRedA::End(bool interrupted) 
{

}

// Returns true when the command should end.
bool GalacticPathRedA::IsFinished() 
{
  return false;
}

void GalacticPathRedA::GetBallOne(){}

void GalacticPathRedA::GetBallTwo(){}

void GalacticPathRedA::GetBallThree(){}

void GalacticPathRedA::ToEndZone(){}
