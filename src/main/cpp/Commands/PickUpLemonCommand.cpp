// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/PickUpLemonCommand.h"

PickUpLemonCommand::PickUpLemonCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, DriveTrainSubsystemBase *pDrive, double moveSpeed,
double loadSpeed, double centerScreen, double deadzoneRange, OldCameraVision::VisionColors color)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_pLoader = pLoader;
  m_pShooter = pShooter;
  AddRequirements(pDrive);
  AddRequirements(pLoader);
  AddRequirements(pShooter);

  m_centerScreen = centerScreen;
  m_deadzoneRange = deadzoneRange;
  m_motorSpeed = moveSpeed;
  m_loaderSpeed = loadSpeed;
  m_color = color;
}

// Called when the command is initially scheduled.
void PickUpLemonCommand::Initialize() 
{
  Util::Log("LemonShadow", "Init");
  m_pDrive->SetLookingColorV(m_color);
}

// Called repeatedly when this Command is scheduled to run
void PickUpLemonCommand::Execute() 
{
  m_result = m_pDrive->WhereToTurn(m_centerScreen, m_deadzoneRange);
  Util::Log("LemonWhereToTurn", m_result);
  switch (m_state)
  {
  case 0:
    Util::Log("LemonCase", m_state);
    stateZero();
    break;
  case 1:
    Util::Log("LemonCase", m_state);
    stateOne();
    break;
  case 2:
    Util::Log("LemonCase", m_state);
    stateTwo();
    break;
  case 3:
    Util::Log("LemonCase", m_state);
    stateThree();
    break;
  case 4:
    Util::Log("LemonCase", m_state);
    stateFour();
    break;
  default:
    Util::Log("LemonCase", m_state);
    stateZero();
    break;
  }
}

void PickUpLemonCommand::stateZero()
{
  Util::Log("LemonShadow", "ZeroB");
  m_pDrive->ForwardInInch(60, 0.0, m_motorSpeed);
  m_state = 1;
  Util::Log("LemonShadow", "ZeroE");
}

void PickUpLemonCommand::stateOne()
{
  Util::Log("LemonShadow", "OneB");
  if(m_result < -2.0) //Not seen
  {
    Util::Log("LemonShadow", "1NoSee-Right");
    m_pDrive->TurnRight(m_motorSpeed);
  }
  else if(m_result > 0.0) //Right Side
  {
    Util::Log("LemonShadow", "1See-Left");
    m_pDrive->TurnLeft(m_motorSpeed - 0.1);
  }
  else if(m_result < 0.0) //Left Side
  {
    Util::Log("LemonShadow", "1See-Right");
    m_pDrive->TurnRight(m_motorSpeed);
  }
  else if(m_result == 0.0) //Center
  {
    Util::Log("LemonShadow", "1See-Forward");
    m_pDrive->Forward(m_motorSpeed);
    Util::Log("LemonShadow", "OneE");
    m_state = 2;
  }
}

void PickUpLemonCommand::stateTwo()
{
  Util::Log("LemonShadow", "TwoB");
  if(m_result < -2.0) //Not Seen
  {
    Util::Log("LemonShadow", "2NoSee-Stop");
    m_pDrive->Stop();
    Util::Log("LemonShadow", "TwoE");
    m_state = 3;
  }
  else if(m_result > 0.0) //Right Side
  {
    Util::Log("LemonShadow", "2See-Left");
    m_pDrive->TurnLeft(m_motorSpeed - 0.1);
  }
  else if(m_result < 0.0) //Left Side
  {
    Util::Log("LemonShadow", "2See-Right");
    m_pDrive->TurnRight(m_motorSpeed);
  }
  else if(m_result == 0.0) //Center
  {
    Util::Log("LemonShadow", "2See-Forward");
    m_pDrive->Forward(m_motorSpeed);
  }
}

void PickUpLemonCommand::stateThree()
{
  Util::Log("LemonShadow", "ThreeB");
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  Util::Log("LemonShadow", "Forward Start");
  m_pDrive->ForwardInInch(12, 0.0, m_motorSpeed);
  Util::Log("LemonShadow", "Forward End");

  m_pLoader->LoadToPhoto();
  while(m_pLoader->IsLoaded() == true)
  {
    Util::Log("LemonShadow", "3InWhile");
    m_pLoader->SetLoadMotor(m_loaderSpeed);
  }

  m_pLoader->Stop();

  Util::Log("LemonShadow", "ThreeE");
  m_state = 4;
}

void PickUpLemonCommand::stateFour()
{
  Util::Log("LemonShadow", "FourB");
  m_isFinished = true;
  Util::Log("LemonShadow", "FourE");
}

// Called once the command ends or is interrupted.
void PickUpLemonCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool PickUpLemonCommand::IsFinished() 
{
  return m_isFinished;
}
