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
  m_pDrive->SetLookingColorV(m_color);
  m_pDrive->GetVisionSize(&m_height, &m_width);
}

// Called repeatedly when this Command is scheduled to run
void GalaticPathVision::Execute()
{ 
  if(m_isFinished == false)
  {
    switch(CheckRun())
    {
      case RED_ONE:
        RunRedOne();
        break;
      case RED_TWO:
        RunRedTwo();
        break;
      case BLUE_ONE:
        RunBlueOne();
        break;
      case BLUE_TWO:
        RunBlueTwo();
        break;
      default:
        break;
    }
  }
}

int GalaticPathVision::CheckRun()
{
  //Set Crop to Center
	m_pDrive->SetVisionCrop((m_width/2) - (rioW/2), (m_height*0.75), rioW, m_height*0.25);
  //Can find Image return Red1
  if(m_pDrive->WhereToTurn(0, 50) > -2)
  {
    return RED_ONE;
  }

  //Turn Left
	m_pDrive->TurnInDegrees(-7, m_moveSpeed);
  //Can Find Image Return Red2
  if(m_pDrive->WhereToTurn(-1, 50) > -2)
  {
    return RED_TWO;
  }

  //Move 15 feet
  m_pDrive->ForwardInInch(180, 0.0, m_moveSpeed);
  //Can find Image return Blue1 and if cant find image return Blue2
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
  m_pDrive->ForwardInInch(60,0,0.4); // Assume directly in front of ball, go forward to it
  m_pLoader->SetLoadMotor(0.6); // Load first ball to photogate
  Util::DelayInSeconds(1); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  //GetBallTwo
  m_pDrive->TurnInDegrees(26.565 - 6.2,0.4); // Turn 26.565 degrees toward the second ball
  m_pDrive->ForwardInInch(67.082,0,0.4); // Move toward the ball, 67.082 is length of hypotenuse toward ball
  m_pLoader->SetLoadMotor(0.6,3); // Pick up the second ball; 3 denotes the Bottom 2 loaders
  Util::DelayInSeconds(1); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  //GetBallThree
  m_pDrive->TurnInDegrees(-97.130 + 33.0,0.4); // Turn -97.130 degrees toward the third ball
  m_pDrive->ForwardInInch(94.86833,0,0.4); // Move toward the ball, 94.86833 is length of hypotenuse toward ball
  m_pLoader->SetLoadMotor(0.6,3); // Pick up the third ball; 3 denotes the Bottom 2 loaders
  Util::DelayInSeconds(1); // Wait while picking up
  m_pLoader->SetLoadMotor(0.0); // Stop loaders
  //ToEndZone
  m_pDrive->TurnInDegrees(71.565,0.4); // Turn 71.565 degrees toward the end zone
  m_pDrive->ForwardInInch(94.86833,0,0.4); // Move toward the end zone, 180 inches away

  m_isFinished = true;
}

void GalaticPathVision::RunRedTwo()
{
  //Get First Ball
  m_pDrive->TurnInDegrees(7, m_moveSpeed);  //Turn back to normal
  m_pDrive->ForwardInInch(60, 0.0, m_moveSpeed); //Move forward
  m_pDrive->TurnInDegrees(-90, m_moveSpeed);  //Turn to face ball
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Turn on loader
  m_pDrive->ForwardInInch(36, 0, m_moveSpeed); //Move towards ball
  Util::DelayInSeconds(1); //Wait while picking up
  m_pLoader->Stop();   //Stop Loaders
  //Get Second Ball
  m_pDrive->TurnInDegrees(90, m_moveSpeed); //Turn towards Ball
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Turn on loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move towards ball
  Util::DelayInSeconds(1); //Wait while picking up
  m_pLoader->Stop();   //Stop Loaders
  //Get Third Ball
  m_pDrive->TurnInDegrees(-15, m_moveSpeed); //Turn Towards ball
  m_pLoader->SetLoadMotor(m_loaderSpeed);   //Start loader
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed); //Move towards ball
  Util::DelayInSeconds(1); //Wait while picking up
  m_pLoader->Stop();
  //Move towards end zone
  m_pDrive->TurnInDegrees(15, m_moveSpeed);   //Turn towards endzone
  m_pDrive->ForwardInInch(144, 0, m_moveSpeed); //move to end zone

  m_isFinished = true;
}

void GalaticPathVision::RunBlueOne()
{
  //Get ball one
  m_pDrive->TurnInDegrees(15, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(60, 0, m_moveSpeed);
  Util::DelayInSeconds(1);
  m_pLoader->Stop();
  //Get Ball two
  m_pDrive->TurnInDegrees(-30, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(100, 0, m_moveSpeed);
  Util::DelayInSeconds(1);
  m_pLoader->Stop();
  //GetBall 3 and go to end zone
  m_pDrive->TurnInDegrees(10, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(134, 0, m_moveSpeed);

  m_isFinished = true;
}

void GalaticPathVision::RunBlueTwo()
{
  //Get first ball
  m_pDrive->TurnInDegrees(15, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(24, 0, m_moveSpeed);
  Util::DelayInSeconds(1);
  m_pLoader->Stop();  
  //Get Second ball
  m_pDrive->TurnInDegrees(-15, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(90, 0, m_moveSpeed);
  Util::DelayInSeconds(1);
  m_pLoader->Stop();
  //Get third ball and go to end zone
  m_pDrive->TurnInDegrees(15, m_moveSpeed);
  m_pLoader->SetLoadMotor(m_loaderSpeed);
  m_pDrive->ForwardInInch(132, 0, m_moveSpeed);

  m_isFinished = true;
}

// Called once the command ends or is interrupted.
void GalaticPathVision::End(bool interrupted) {}

// Returns true when the command should end.
bool GalaticPathVision::IsFinished() 
{
  if(m_isFinished == true)
  {
    m_pDrive->Stop();
  }
  return m_isFinished;
}
