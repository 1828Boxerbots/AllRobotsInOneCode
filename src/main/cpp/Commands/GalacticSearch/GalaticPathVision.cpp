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
  
  m_startAngle = m_pDrive->IMUGetAngle();

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
	m_pDrive->TurnInDegrees(-5.5, m_moveSpeed);
  //Can Find Image Return Red2
  Util::Log("GV Shadow", "CheckRun Where");
  double result = m_pDrive->WhereToTurn(-1, m_deadZone);
  Util::DelayInSeconds(1.7);
  if(result > -2)
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

  FaceBall();

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
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(70, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //Get Second Ball
  Util::Log("GV Shadow", "R2 Ball2");
  m_pDrive->TurnInDegrees(50, m_moveSpeed); //Turn towards Ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(80, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //Get Third Ball
  Util::Log("GV Shadow", "R2 Ball3");
  m_pDrive->TurnInDegrees(-50, m_moveSpeed); //Turn Towards ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 2);
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //Move towards end zone
  Util::Log("GV Shadow", "R2 EndZone");
  //m_pDrive->TurnInDegrees(90, m_moveSpeed);
  RotateToEnd();
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);
  
  Util::Log("GV Shadow", "R2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunBlueOne()
{
  //Get ball one
  Util::Log("GV Shadow", "B1 Ball1");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(60, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //Get Ball two
  Util::Log("GV Shadow", "B1 Ball2");
  m_pDrive->TurnInDegrees(-161.6, m_moveSpeed);  //Turn toward ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(100, 0,m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();
  //GetBall 3
  Util::Log("GV Shadow", "B1 Ball3");
  m_pDrive->TurnInDegrees(88.2, m_moveSpeed); //Turn toward ball and end
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 2);
  m_pDrive->ForwardInInch(50, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();

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
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();

  //Get Second ball
  Util::Log("GV Shadow", "B2 Ball2");
  m_pDrive->TurnInDegrees(-135, m_moveSpeed);  //Turn toward ball
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 3);
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();

  //Get third ball and go to end zone
  Util::Log("GV Shadow", "B2 Ball1 3 & end");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball and end
  FaceBall();
  m_pLoader->SetLoadMotor(m_loaderSpeed, 2);
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);
  Util::DelayInSeconds(0.5);
  m_pLoader->Stop();

  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move toward ball and past end

  Util::Log("GV Shadow", "B2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::FaceBall()
{
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
}

void GalaticPathVision::RotateToEnd()
{
  double currentAngle = m_pDrive->IMUGetAngle();
  
  double lowerStart = m_startAngle - m_angleDed;
  double upperStart = m_startAngle + m_angleDed;

  while(currentAngle > upperStart || currentAngle < lowerStart)
  {
    if(currentAngle > upperStart)
    {
      m_pDrive->TurnRight(m_turnSpeed);
    }
    else if(currentAngle < lowerStart)
    {
      m_pDrive->TurnLeft(m_turnSpeed);
    }
    currentAngle = m_pDrive->IMUGetAngle();
  }

  m_pDrive->Stop();
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
