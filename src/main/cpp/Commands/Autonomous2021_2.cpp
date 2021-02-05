// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/Autonomous2021_2.h"

Autonomous2021_2::Autonomous2021_2(DriveTrainSubsystemBase *pDrive)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_pDrive = pDrive;
  AddRequirements(pDrive); //bruh
}

// Called just before this Command runs the first time
void Autonomous2021_2::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Autonomous2021_2::Execute()
{
  if (m_pDrive != nullptr)
  {
    /*
    SwitchColor(DriveTrainSubsystemBase::BROWN);
    loop1();
    loop2();
    loop3();
    SwitchColor(DriveTrainSubsystemBase::BLUE);
    loop4();
    loop5();
    loop6();
    */

    if (m_loopsUpdate != 0)
    {
      m_state++;
      m_loopsUpdate = 0;
      //result = 0;
    }

    Util::Log("Auto2021 State", m_state);
    switch (m_state)
    {
    case 0:
      loop0();
      break;
    case 1:
      loop1();
      break;
    case 2:
      loop2();
      break;
    case 3:
      loop3();
      break;
    case 4: //loop4()
      loop4();
    default:
      break;
    }
  }
}

bool Autonomous2021_2::IsFinished()
{
  if (m_IsFinished)
  {
    Util::Log("Auto2021 Finished", "IsFinished = true");
    m_pDrive->Stop();
  }
  else
  {
    Util::Log("Auto2021 Finished", "IsFinished = false");
  }

  return m_IsFinished;
}

void Autonomous2021_2::loop0()
{
  if (m_state != 0)
  {
    return;
  }

  result = m_pDrive->WhereToTurnVision(0.75, 50);
  if (result < 0)
  {
    Util::Log("Auto2021 S1 Direction", "Turning Left");
    m_pDrive->TurnLeft(0.2);
  }
  else if (result > 0)
  {
    Util::Log("Auto2021 S1 Direction", "Turning Right");
    m_pDrive->TurnRight(0.2);
  }
  else
  {
    Util::Log("Auto2021 S1 Direction", "Stopped");
    m_state = 1;
  }
}

void Autonomous2021_2::loop1()
{
  if (m_state != 1)
  {
    return;
  }

  if (result >= -2.5)
  {
    result = m_pDrive->WhereToTurnVision(0.75, 50);
    m_pDrive->MoveTank(0.4, 0.6); //Turns left and moves forward
  }
  else
  {
    m_pDrive->TurnLeft(0.2);
  }
}

void Autonomous2021_2::loop2()
{
  if (m_state != 2)
  {
    return;
  }

  if (result >= -2.5)
  {
    result = m_pDrive->WhereToTurnVision(0.75, 50);
    if (result < 0) //Is on the left side
    {
      m_pDrive->TurnLeft(0.2); //Turn left so that its on the right side
    }
    else //if?
    {
      m_pDrive->MoveTank(0.4, 0.2); //Move forward and right
    }
  }
  else
  {
    m_loopsUpdate++;
  }
}

void Autonomous2021_2::loop3()
{
  if (result >= 0)
  {
    result = m_pDrive->WhereToTurnVision(0.75, 50);
    m_pDrive->Forward(0.3);
  }
  else
  {
    m_loopsUpdate++;
  }
}

void Autonomous2021_2::loop4()
{
  /*
  	loop4:
		  switch color to blue (done in main func)
		  move forward a little bit
		  if not blue on left
		  	rotate right until blue on left
  */
  m_pDrive->ForwardInSeconds(0.5); //Worth a shot

  //!!IMPORTANT!! The center is being changed to 0.25 because we are now rotating something around the left side
  double result = m_pDrive->WhereToTurnVision(0.25, 50);
  while (result > 0)
  {
    result = m_pDrive->WhereToTurnVision(0.25, 50);
    m_pDrive->TurnRight(0.3);
  }

  m_pDrive->Stop();
}

void Autonomous2021_2::loop5()
{
  /*
    loop5:
      move forward until no blue
      rotate left until see blue
      if not gyro == 180
        goto loop5
  */
  int gyro = 0; //TEMPORARY, WILL REPLACE WHEN I KNOW HOW TO USE GYRO LOL
  double result = 0;
  while (gyro < 180)
  {
    result = m_pDrive->WhereToTurnVision(0.25, 50);
    if (result > -2)
    {
      m_pDrive->Forward(0.3);
    }
    else //if (result < -1)
    {
      m_pDrive->TurnLeft(0.2);
    }
  }
  m_pDrive->Stop();
}

void Autonomous2021_2::loop6()
{
  /*
    if loops == 0
			move forward until no blue
			if see blue
				goto loop6
			switch color to brown
			move forward a little bit
			rotate left until brown on right
			loops++
			goto loop
		else
			move forward
			if see blue
				goto loop6
			stop
  */
  double result = 0;
  while (result > -2.5) //While it's on screen
  {
    result = m_pDrive->WhereToTurnVision(0.25, 50);
    m_pDrive->Forward(0.3);
  }
  SwitchColor(DriveTrainSubsystemBase::BROWN);
  m_pDrive->ForwardInSeconds(0.5);

  loop1();
  loop2();
  loop3();
  SwitchColor(DriveTrainSubsystemBase::BLUE);
  loop4();
  loop5();

  while (result > -2.5) //While it's on screen
  {
    result = m_pDrive->WhereToTurnVision(0.25, 50);
    m_pDrive->Forward(0.3);
  }
}

void Autonomous2021_2::SwitchColor(DriveTrainSubsystemBase::Colors color)
{
}