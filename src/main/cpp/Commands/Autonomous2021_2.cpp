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
	case 5: //also case 5 because we need to move forward a little bit there as well
      loop2();
      break;
    case 3:
      loop3();
      break;
    case 4:
      loop4();
	case 6:
	  
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
  //No state check because this function is shared by other cases

  int timer;
  double speed;

  if (timer < 30)
  {
    speed = 0.2;
    Util::DelayInSeconds(0.016 / 2);
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
  //Rotate right until color1 is on the right side
  m_center = 0.75;

  if (m_state != 0)
  {
    return;
  }

  double direction;
  if (m_result < -2.0 || m_result < 0.0)
  {
    direction = -0.2;
  }
  else
  {
    direction = 0.0;
    m_state = 1;
  }
  m_pDrive->MoveTank(-direction, direction);
}

void Autonomous2021_2::loop4()
{
  //Move forward until I can't see Color1
  //Color1 should be on the right
  m_center = 0.75;
  double speed = 0.0;
  
  if(m_result >= 0)
  {
    speed = 0.3;
  }
  else
  {
    speed = 0.0;
  }
  m_pDrive->Forward(speed); 
}

void Autonomous2021_2::loop6()
{
  //Rotate until Color2 on left side

  m_center = 0.25;

  if (m_state != 0)
  {
    return;
  }

  double direction;
  if (m_result < -2.0 || m_result < 0.0)
  {
    direction = -0.2;
  }
  else if (m_result > 0.0)
  {
    direction = 0.2;
  }
  else
  {
    direction = 0.0;
    m_state = 1;
  }
  m_pDrive->MoveTank(-direction, direction);
}

void Autonomous2021_2::SwitchColor(DriveTrainSubsystemBase::Colors color)
{
}