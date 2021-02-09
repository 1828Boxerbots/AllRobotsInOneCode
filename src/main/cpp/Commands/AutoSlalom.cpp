// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/AutoSlalom.h"

AutoSlalom::AutoSlalom(DriveTrainSubsystemBase *pDrive)
{
  // Use Requires() here to declare subsystem dependencies
  // eg. Requires(Robot::chassis.get());
  m_pDrive = pDrive;
  AddRequirements(pDrive); //bruh
}

// Called just before this Command runs the first time
void AutoSlalom::Initialize()
{
  timer.Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoSlalom::Execute()
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
    m_result = m_pDrive->WhereToTurn(m_center, 25);
    switch (m_state)
    {
    case 0:
    case 3:
    case 6: //also case 6 because we need to move forward a little bit there as well
      loop0();
      break;
    case 1:
      m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE);
      loop1();
      break;
    case 2:
      loop2();
      break;
    default:
      break;
    }
  }
}

bool AutoSlalom::IsFinished()
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

void AutoSlalom::loop0()
{
  //Move forward a little bit
  //No state check because this function is shared by other cases
  m_pDrive->ForwardInSeconds(0.25, 0.5);
}

void AutoSlalom::loop1()
{
  //Rotate until Color1 on right side

  m_center = 0.85;

  if (m_state != 0) //Return if state is not 0
  {
    return;
  }

  double direction;
  if (m_result < -2.0 || m_result < 0.0) //If I can't see the cone or it is on the left side of the center
  {
    Util::Log("Auto2021 S1 State", "Turning Left");
    //direction = -0.2;
    m_pDrive->TurnRight(0.3);
  }
  else if (m_result > 0.0) //If the cone is on the right side of the center
  {
    Util::Log("Auto2021 S1 State", "Turning Right");
    //direction = 0.2;
    m_pDrive->TurnLeft(0.3); 
  }
  else //If cone is in the center
  {
    //direction = 0.0;
    m_state = 1; //Increment state
    m_pDrive->Stop(); //Stop motors
  }
  //m_pDrive->MoveTank(direction, -direction);
}

void AutoSlalom::loop2()
{
  //Move forward until I can't see color1

  m_center = 0.50; //Center is in the center
  double speed = 0.0;

  if (m_state != 1) //Return if state is not one
  {
    return;
  }

  if (m_result > -3) //If I see the cone
  {
    if (m_result > 0) //If cone is on the right
    {
      speed = -0.2;
    }
    else if (m_result < 0) //If cone is on the left
    {
      speed = 0.2;
    }
  }
  else //If I don't see the cone
  {
    m_state = 2; //Increment state
  }

  m_pDrive->MoveArcade(0.2, speed); //Move
}

void AutoSlalom::loop4()
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