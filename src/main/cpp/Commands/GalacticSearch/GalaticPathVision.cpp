// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/GalacticSearch/GalaticPathVision.h"


GalaticPathVision::GalaticPathVision(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_pLoader = pLoader;

  AddRequirements(pLoader);
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void GalaticPathVision::Initialize()
{
  Util::Log("GV Shadow", "InitS");
  m_pDrive->SetLookingColorV(m_color);
  m_pDrive->GetVisionSize(&m_height, &m_width);
  
  m_gyroAngle = m_pDrive->IMUGetAngle();

  Util::Log("GV Shadow", "InitE");
}

// Called repeatedly when this Command is scheduled to run
void GalaticPathVision::Execute()
{
  m_pDrive->SetVisionCrop((m_width/2) - (rioW/2), (m_height*0.75), rioW, m_height*0.25);
  m_pDrive->WhereToTurn(0, m_deadZone);

  Util::Log("GV Shadow", "ExeS");
  if(m_isFinished == false)
  {
    switch(CheckRun())
    {
      case RED_ONE:
        Util::Log("GV Shadow", "ExeRed1");
        RunRedOne();
        break;
      case RED_TWO:
        Util::Log("GV Shadow", "ExeRed2");
        RunRedTwo();
        break;
      case BLUE_ONE:
        Util::Log("GV Shadow", "ExeBlue1");
        RunBlueOne();
        break;
      case BLUE_TWO:
        Util::Log("GV Shadow", "ExeBlue2");
        RunBlueTwo();
        break;
      default:
        Util::Log("GV Shadow", "DEFAULT-ERROR");
        break;
    }
  }
}

int GalaticPathVision::CheckRun()
{
  Util::Log("GV Shadow", "CheckRunCrop");
  //Set Crop to Center
	m_pDrive->SetVisionCrop((m_width/2) - (rioW/2), (m_height*0.75), rioW, m_height*0.25);
  // m_pDrive->WhereToTurn(0, m_deadZone);
  // Util::DelayInSeconds(1);
  //Can find Image return Red1
  Util::Log("GV Shadow", "CheckRun Where");
  if(m_pDrive->WhereToTurn(0, m_deadZone) > -2)
  {
    m_iteration = RED_ONE;
    return RED_ONE;
  }

  //Turn Left
  Util::Log("GV Shadow", "CheckRun Turn");
  Util::DelayInSeconds(0.1);
	m_pDrive->TurnInDegrees(-7, m_moveSpeed);
  //Can Find Image Return Red2
  m_pDrive->WhereToTurn(0, m_deadZone);
  Util::DelayInSeconds(1);
  Util::Log("GV Shadow", "CheckRun Where");
  if(m_pDrive->WhereToTurn(-1, m_deadZone) > -2)
  {
    m_iteration = RED_TWO;
    return RED_TWO;
  }

  m_pDrive->TurnInDegrees(7, m_moveSpeed);
  //Move 15 feet
  Util::Log("GV Shadow", "CheckRun Forward");
  m_pDrive->ForwardInInch(180, 0.0, m_moveSpeed);
  //Can find Image return Blue1 and if cant find image return Blue2
  Util::Log("GV Shadow", "CheckRun Where");
  if(m_pDrive->WhereToTurn(0, 50) > -2)
  {
    m_iteration = BLUE_ONE;
    return BLUE_ONE;
  }
  else
  {
    m_iteration = BLUE_TWO;
    return BLUE_TWO;
  }
  
}

void GalaticPathVision::RunRedOne()
{

  //GetBallOne
  Util::Log("GV Shadow", "R1 Ball1");
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(60, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //GetBallTwo
  Util::Log("GV Shadow", "R1 Ball2");
  m_pDrive->TurnInDegrees(47,m_moveSpeed); // 42.5 at dying battery
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(53, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //GetBallThree
  Util::Log("GV Shadow", "R1 Ball3");
  m_pDrive->SetLookingColorV(OldCameraVision::YELLOW_LEMON_N);
  m_pDrive->TurnInDegrees(-50,m_moveSpeed); // Turn -97.130 degrees toward the third ball

  double result = m_pDrive->WhereToTurn(0, m_deadZone);

  while(result != 0)
  {
    if(result > 0)
    {
      m_pDrive->TurnRight(m_moveSpeed/2);
      Util::DelayInSeconds(0.045);
      m_pDrive->Stop();
    }
    else if(result < -2)
    {
      m_pDrive->TurnRight(m_moveSpeed/2);
      Util::DelayInSeconds(0.045);
      m_pDrive->Stop();
    }
    else if(result < 0)
    {
      m_pDrive->TurnLeft(m_moveSpeed/2);
      Util::DelayInSeconds(0.045);
      m_pDrive->Stop();
    }
    else if(result == 0)
    {
      break;
    }

    result = m_pDrive->WhereToTurn(0, m_deadZone);
  }

  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(20, 0, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(39, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();

  //ToEndZone
  Util::Log("GV Shadow", "R1 Endzone");
  m_pDrive->TurnInDegrees(110, m_moveSpeed);
  m_pDrive->ForwardInInch(102, 0, m_moveSpeed);

  Util::Log("GV Shadow", "R1 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunRedTwo()
{
  //Get First Ball
  Util::Log("GV Shadow", "R2 Ball1");
  m_pDrive->TurnInDegrees(7, m_moveSpeed);  //Turn back to normal
  m_pDrive->ForwardInInch(60, 0.0, m_moveSpeed); //Move forward
  m_pDrive->TurnInDegrees(-90, m_moveSpeed);  //Turn to face ball
  FindBall(true);
  MoveBall();
  //Get Second Ball
  Util::Log("GV Shadow", "R2 Ball2");
  m_pDrive->TurnInDegrees(45, m_moveSpeed); //Turn towards Ball
  FindBall(false);
  MoveBall();
  //Get Third Ball
  Util::Log("GV Shadow", "R2 Ball3");
  m_pDrive->TurnInDegrees(-45, m_moveSpeed); //Turn Towards ball
  FindBall(true);
  MoveBall();
  //Move towards end zone
  Util::Log("GV Shadow", "R2 EndZone");
  MoveToEnd();

  Util::Log("GV Shadow", "R2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunBlueOne()
{
  //Get ball one
  Util::Log("GV Shadow", "B1 Ball1");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball
  FindBall(false);
  MoveBall();
  //Get Ball two
  Util::Log("GV Shadow", "B1 Ball2");
  m_pDrive->TurnInDegrees(-161.6, m_moveSpeed);  //Turn toward ball
  FindBall(true);
  MoveBall();
  //GetBall 3
  Util::Log("GV Shadow", "B1 Ball3");
  m_pDrive->TurnInDegrees(88.2, m_moveSpeed); //Turn toward ball and end
  FindBall(false);
  MoveBall();
  //Go to End
  Util::Log("GV Shadow", "B1 End");
  m_pDrive->TurnInDegrees(-20, m_moveSpeed);
  m_pDrive->ForwardInInch(60, 0, m_moveSpeed);

  Util::Log("GV Shadow", "B1 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunBlueTwo()
{
  //Get first ball
  Util::Log("GV Shadow", "B2 Ball1");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball
  FindBall(false);
  MoveBall();
  //Get Second ball
  Util::Log("GV Shadow", "B2 Ball2");
  m_pDrive->TurnInDegrees(-135, m_moveSpeed);  //Turn toward ball
  FindBall(true);
  MoveBall();
  //Get third ball and go to end zone
  Util::Log("GV Shadow", "B2 Ball1 3 & end");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball and end
  FindBall(false);
  MoveBall();
  m_pLoader->Stop(); //Stop Loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move toward ball and past end

  Util::Log("GV Shadow", "B2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::FindBall(bool defLeftTurn)
{
  Util::Log("GV Shadow", "FindBall Begin");
  double result = m_pDrive->WhereToTurn(0, m_deadZone);
  while (result < -2)
  {
    if(result < 0)
    {
      Util::Log("GV Shadow", "Turn Left-Ball on left side");
      m_pDrive->TurnLeft(m_moveSpeed/4);
      result = m_pDrive->WhereToTurn(0, m_deadZone);
    }
    else if(result > 0)
    {
      Util::Log("GV Shadow", "Turn Right-Ball on right side");
      m_pDrive->TurnRight(m_moveSpeed/4);
      result = m_pDrive->WhereToTurn(0, m_deadZone);
    }
    else
    {
      Util::Log("GV Shadow", "Default cant see");
      if(defLeftTurn)
      {
        Util::Log("GV Shadow", "Cant See-Left");
        m_pDrive->TurnLeft(m_moveSpeed/4);
        result = m_pDrive->WhereToTurn(0, m_deadZone);
      }
      else
      {
        Util::Log("GV Shadow", "Cant See-Right");
        m_pDrive->TurnRight(m_moveSpeed/4);
        result = m_pDrive->WhereToTurn(0, m_deadZone);
      }
    }
    result = m_pDrive->WhereToTurn(0, m_deadZone);
  }
  Util::Log("GV Shadow", "Found!");
  //m_pDrive->Stop();
  return;
}

void GalaticPathVision::MoveBall()
{
  Util::Log("GV Shadow", "MoveBall Begin");
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  double result = m_pDrive->WhereToTurn(0, m_deadZone);
  Util::DelayInSeconds(1);
  Util::Log("Move Ball Result", result);
  while (result < -2)
  {
    if(result > 0)
    {
      Util::Log("GV Shadow", "MoveBall Turn Right-Ball on left side");
      m_pDrive->MoveArcade(m_moveSpeed, -0.1);
    }
    else if(result < 0)
    {
      Util::Log("GV Shadow", "MoveBall Turn Left-Ball on right side");
      m_pDrive->MoveArcade(m_moveSpeed, 0.1);
    }
    else
    {
      Util::Log("GV Shadow", "MoveBall - Found!");
      m_pDrive->MoveArcade(m_moveSpeed, 0);
    }
    result = m_pDrive->WhereToTurn(0, m_deadZone);
    Util::DelayInSeconds(1);
  }
  Util::Log("GV Shadow", "No Longer see much be under");
  Util::DelayInSeconds(1);
  m_pDrive->Stop();
  m_pLoader->Stop();
  
  Util::Log("GV Shadow", "MoveBall Finished");
  return;
}

void GalaticPathVision::MoveToEnd()
{
  double currentAngle = m_pDrive->IMUGetAngle();
  double time = 0;

  switch(m_iteration)
  {
    case RED_ONE:
      time = 5;
      break;
    case RED_TWO:
      time = 4.5;
      break;
    case BLUE_ONE:
      time = 2;
      break;
    case BLUE_TWO:
      time = 1.5;
      break;
    default:
      time = 3;
      break;
  }

  if(currentAngle < m_gyroAngle)
  {
    m_pDrive->TimedArcade(m_moveSpeed, m_turnSpeed, time);
  }
  else if(currentAngle > m_gyroAngle)
  {
    m_pDrive->TimedArcade(m_moveSpeed, -m_turnSpeed, time);
  }
  else
  {
    m_pDrive->TimedArcade(m_moveSpeed, 0, time);
  }
  
}

// Called once the command ends or is interrupted.
void GalaticPathVision::End(bool interrupted) {}

// Returns true when the command should end.
bool GalaticPathVision::IsFinished() 
{
  if(m_isFinished == true)
  {
    m_pDrive->Stop();
    m_pLoader->Stop();
  }
  return m_isFinished;
}
