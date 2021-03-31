// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/NewSlalom.h"

NewSlalom::NewSlalom(DriveTrainSubsystemBase *pDrive)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void NewSlalom::Initialize()
{
  m_pDrive->GetVisionSize(&m_height, &m_width);
  m_roi = m_width;
  m_pDrive->SetVisionCrop(0, (m_height*0.75), m_roi, m_height*0.25);
}

// Called repeatedly when this Command is scheduled to run
void NewSlalom::Execute()
{
  //MOve out of start range and rotate toward front cone
  m_pDrive->ForwardInInchGyro(14, m_moveSpeed);
  RotateToDegree(10, m_moveSpeed/2);
  //Set vision color
  m_pDrive->SetLookingColorV(OldCameraVision::VisionColors::RED_CONE_A);
  //Align and move forward
  m_pDrive->AlignWithVision(1.0, m_deadZone);
  m_pDrive->ForwardInInchGyro(25, m_moveSpeed);

  //Move forward along with cones
  RotateToDegree(10, 0.15);
  m_pDrive->ForwardInInchGyro(125, m_moveSpeed, 0.2, 0.2);

  //Rotate to face end cone
  RotateToDegree(-20, m_moveSpeed/2);
  m_pDrive->AlignWithVision(-1, m_deadZone);
  //Move Forward
  //Check if we can still see cone
  int beat = 0;
  while (m_pDrive->WhereToTurn(-1, m_deadZone) > -2)
  {
    Util::DelayInSeconds(1);
    m_pDrive->Stop();
    //Align and move forward until we can no longer see end cone
    m_pDrive->AlignWithVision(-1, m_deadZone);
    m_pDrive->ForwardInInchGyro(0.1, 0.15, 0.2, 0.1);
    Util::Log("Slalom While", beat++);
    m_pDrive->Stop();
  }
  
  m_pDrive->IMUArcade(0.8, -0.2, 350);

  // m_pDrive->ForwardInInchGyro(5, m_moveSpeed);
  // RotateToDegree(-180, m_moveSpeed/2);
  // m_pDrive->ForwardInInchGyro(150, m_moveSpeed);

  // RotateToDegree(-225, m_moveSpeed/2);
  // m_pDrive->SetLookingColorV(OldCameraVision::VisionColors::GREEN_CONE_A);
  // m_pDrive->AlignWithVision(0, m_deadZone);
  // m_pDrive->ForwardInInchGyro(60);

  m_isFinished = true;
}

void NewSlalom::RotateToDegree(double degree, double speed)
{
  double currentAngle = m_pDrive->IMUGetAngle();
  
  double lowerDegree = degree - 2;
  double upperDegree = degree + 2;

  while(currentAngle > upperDegree || currentAngle < lowerDegree)
  {
    if(currentAngle > upperDegree)
    {
      m_pDrive->TurnRight(speed);
    }
    else if(currentAngle < lowerDegree)
    {
      m_pDrive->TurnLeft(speed);
    }
    currentAngle = m_pDrive->IMUGetAngle();
  }

  m_pDrive->Stop();
}

// Called once the command ends or is interrupted.
void NewSlalom::End(bool interrupted) {}

// Returns true when the command should end.
bool NewSlalom::IsFinished() {
  return m_isFinished;
}
