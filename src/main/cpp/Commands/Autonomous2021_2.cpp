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

    /*
    if (m_loopsUpdate != 0)
    {
      m_state++;
      m_loopsUpdate = 0;
      //m_result = 0;
    }
    */

    //Color 1 is Green
    //Color 2 is Red

    Util::Log("Auto2021 State", m_state);
    m_result = m_pDrive->WhereToTurnVision(m_center, 50);
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
  //Rotate until Color1 on right side

  m_center = 0.75;

  if (m_state != 0)
  {
    return;
  }

  double direction;
  if (m_result < -2.0 || m_result < 0.0)
  {
    Util::Log("Auto2021 S1 State", "Turning Left");
    direction = 0.2;
  }
  else if (m_result > 0.0)
  {
    Util::Log("Auto2021 S1 State", "Turning Right");
    direction = -0.2;
  }
  else
  {
    direction = 0.0;
    m_state = 1;
  }
  m_pDrive->MoveTank(-direction, direction);
}

void Autonomous2021_2::loop1()
{
  //Move forward until I can't see color1

  m_center = 0.75;

  if (m_state != 1)
  {
    return;
  }

  if (m_result > 3.0)
  {
    m_pDrive->Forward(0.3);
  }
}

void Autonomous2021_2::loop2()
{
  //Move forward a little bit

  int timer;
  double speed;
  m_center = 0.75;

  if (m_state != 2)
  {
    return;
  }

  if (timer < 30)
  {
    speed = 0.2;
    Util::DelayInSeconds(0.016);
    timer++;
  }
  else
  {
    speed = 0.0;
    m_state = 3;
  } 
  m_pDrive->MoveTank(-speed, speed);
}

void Autonomous2021_2::loop3()
{

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
  double m_result = m_pDrive->WhereToTurnVision(0.25, 50);
  while (m_result > 0)
  {
    m_result = m_pDrive->WhereToTurnVision(0.25, 50);
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
  double m_result = 0;
  while (gyro < 180)
  {
    m_result = m_pDrive->WhereToTurnVision(0.25, 50);
    if (m_result > -2)
    {
      m_pDrive->Forward(0.3);
    }
    else //if (m_result < -1)
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
  double m_result = 0;
  while (m_result > -2.5) //While it's on screen
  {
    m_result = m_pDrive->WhereToTurnVision(0.25, 50);
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

  while (m_result > -2.5) //While it's on screen
  {
    m_result = m_pDrive->WhereToTurnVision(0.25, 50);
    m_pDrive->Forward(0.3);
  }
}

void Autonomous2021_2::SwitchColor(DriveTrainSubsystemBase::Colors color)
{
}