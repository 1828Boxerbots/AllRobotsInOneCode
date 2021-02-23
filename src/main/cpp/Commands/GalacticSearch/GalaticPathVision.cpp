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
  
  Util::Log("GV Shadow", "InitE");
}

// Called repeatedly when this Command is scheduled to run
void GalaticPathVision::Execute()
{
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
  m_pDrive->WhereToTurn(0, m_deadZone);
  Util::DelayInSeconds(0.5);
  //Can find Image return Red1
  Util::Log("GV Shadow", "CheckRun Where");
  if(m_pDrive->WhereToTurn(0, m_deadZone) > -2)
  {
    return RED_ONE;
  }

  //Turn Left
  Util::Log("GV Shadow", "CheckRun Turn");
	m_pDrive->TurnInDegrees(-7, m_moveSpeed);
  //Can Find Image Return Red2
  Util::Log("GV Shadow", "CheckRun Where");
  if(m_pDrive->WhereToTurn(-1, m_deadZone) > -2)
  {
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
    return BLUE_ONE;
  }
  else
  {
    return BLUE_TWO;
  }
  
}

void GalaticPathVision::RunRedOne()
{
  //Copied from Adams GalaticPathRedA Command

  //GetBallOne
  Util::Log("GV Shadow", "R1 Ball1");
  m_pDrive->ForwardInInch(60,0,m_moveSpeed); // Assume directly in front of ball, go forward to it
  m_pLoader->SetLoadMotor(0.6); // Load first ball to photogate
  Util::DelayInSeconds(1); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  //GetBallTwo
  Util::Log("GV Shadow", "R1 Ball2");
  m_pDrive->TurnInDegrees(26.565 - 14.8,m_moveSpeed); // Turn 26.565 degrees toward the second ball
  m_pDrive->ForwardInInch(67.082,0,m_moveSpeed); // Move toward the ball, 67.082 is length of hypotenuse toward ball
  m_pLoader->SetLoadMotor(0.6,3); // Pick up the second ball; 3 denotes the Bottom 2 loaders
  Util::DelayInSeconds(1); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  //GetBallThree
  Util::Log("GV Shadow", "R1 Ball3");
  m_pDrive->TurnInDegrees(-97.130 + 25.0,m_moveSpeed); // Turn -97.130 degrees toward the third ball
  m_pDrive->ForwardInInch(94.86833,0,m_moveSpeed); // Move toward the ball, 94.86833 is length of hypotenuse toward ball
  m_pLoader->SetLoadMotor(0.6,3); // Pick up the third ball; 3 denotes the Bottom 2 loaders
  Util::DelayInSeconds(1); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  //ToEndZone
  Util::Log("GV Shadow", "R1 Endzone");
  m_pDrive->TurnInDegrees(31.565,m_moveSpeed); // Turn 71.565 degrees toward the end zone
  m_pDrive->ForwardInInch(100.86833,0,m_moveSpeed); // Move toward the end zone, 180 inches away

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
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Turn on loader
  m_pDrive->ForwardInInch(36, 0, m_moveSpeed); //Move towards ball
  Util::DelayInSeconds(1); //Wait while picking up
  m_pLoader->Stop();   //Stop Loaders
  //Get Second Ball
  Util::Log("GV Shadow", "R2 Ball2");
  m_pDrive->TurnInDegrees(45, m_moveSpeed); //Turn towards Ball
  FindBall(false);
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Turn on loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move towards ball
  Util::DelayInSeconds(1); //Wait while picking up
  m_pLoader->Stop();   //Stop Loaders
  //Get Third Ball
  Util::Log("GV Shadow", "R2 Ball3");
  m_pDrive->TurnInDegrees(-45, m_moveSpeed); //Turn Towards ball
  FindBall(true);
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Start loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move towards ball
  Util::DelayInSeconds(1); //Wait while picking up
  m_pLoader->Stop();
  //Move towards end zone
  Util::Log("GV Shadow", "R2 EndZone");
  m_pDrive->TurnInDegrees(25, m_moveSpeed);   //Turn towards endzone
  m_pDrive->ForwardInInch(144, 0, m_moveSpeed); //move to end zone

  Util::Log("GV Shadow", "R2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::RunBlueOne()
{
  //Get ball one
  Util::Log("GV Shadow", "B1 Ball1");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball
  FindBall(false);
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Activate loader
  m_pDrive->ForwardInInch(60, 0, m_moveSpeed); //Move toward ball
  Util::DelayInSeconds(1);  //Wait to load
  m_pLoader->Stop();  //Stop Loader
  //Get Ball two
  Util::Log("GV Shadow", "B1 Ball2");
  m_pDrive->TurnInDegrees(-161.6, m_moveSpeed);  //Turn toward ball
  FindBall(true);
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Activate loader
  m_pDrive->ForwardInInch(100, 0, m_moveSpeed); //Move toward ball
  Util::DelayInSeconds(1);  //Wait to load
  m_pLoader->Stop();  //Stop loader
  //GetBall 3
  Util::Log("GV Shadow", "B1 Ball3");
  m_pDrive->TurnInDegrees(88.2, m_moveSpeed); //Turn toward ball and end
  FindBall(false);
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Activate Loader
  m_pDrive->ForwardInInch(72, 0, m_moveSpeed); //Move toward ball and end
  m_pLoader->Stop(); //Stop Loader
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
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Actiave loader
  m_pDrive->ForwardInInch(24, 0, m_moveSpeed);  //Move toward ball
  Util::DelayInSeconds(1);  //Wait to load
  m_pLoader->Stop();  //Stop Loader
  //Get Second ball
  Util::Log("GV Shadow", "B2 Ball2");
  m_pDrive->TurnInDegrees(-135, m_moveSpeed);  //Turn toward ball
  FindBall(true);
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Activate loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);  //Move toward ball
  Util::DelayInSeconds(1);  //Wait to load
  m_pLoader->Stop();  //Stop Loader
  //Get third ball and go to end zone
  Util::Log("GV Shadow", "B2 Ball1 3 & end");
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn toward ball and end
  FindBall(false);
  m_pLoader->SetLoadMotor(m_loaderSpeed); //Activate loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move toward ball and past end
  m_pLoader->Stop(); //Stop Loader

  Util::Log("GV Shadow", "B2 Finished");
  m_isFinished = true;
}

void GalaticPathVision::FindBall(bool defLeftTurn)
{
  Util::Log("GV Shadow", "FindBall Begin");
  double result = m_pDrive->WhereToTurn(0, m_deadZone);
  while (result != 0)
  {
    if(result < 0)
    {
      Util::Log("GV Shadow", "Turn Left-Ball on left side");
      m_pDrive->TurnLeft(m_moveSpeed/2);
    }
    else if(result > 0)
    {
      Util::Log("GV Shadow", "Turn Right-Ball on right side");
      m_pDrive->TurnRight(m_moveSpeed/2);
    }
    else
    {
      Util::Log("GV Shadow", "Default cant see");
      if(defLeftTurn)
      {
        Util::Log("GV Shadow", "Cant See-Left");
        m_pDrive->TurnLeft(m_moveSpeed/2);
      }
      else
      {
        Util::Log("GV Shadow", "Cant See-Right");
        m_pDrive->TurnRight(m_moveSpeed/2);
      }
    }
    result = m_pDrive->WhereToTurn(0, m_deadZone);
  }
  Util::Log("GV Shadow", "Found!");
  //m_pDrive->Stop();
  return;
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
