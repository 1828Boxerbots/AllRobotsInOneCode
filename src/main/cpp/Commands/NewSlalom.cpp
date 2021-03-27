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
  m_pDrive->ForwardInInchGyro(3, m_moveSpeed);
  RotateToDegree(45, m_moveSpeed/2);
  m_pDrive->SetLookingColorV(OldCameraVision::VisionColors::RED_CONE_A);
  m_pDrive->AlignWithVision(0.3, m_deadZone);
  m_pDrive->ForwardInInchGyro(50, m_moveSpeed);

  RotateToDegree(0, m_moveSpeed/2);
  m_pDrive->ForwardInInchGyro(150, m_moveSpeed);

  RotateToDegree(-45, m_moveSpeed/2);
  m_pDrive->AlignWithVision(-0.5, m_deadZone);
  m_pDrive->IMUArcade(0.6, 0.2, -90);

  m_pDrive->ForwardInInchGyro(5, m_moveSpeed);
  RotateToDegree(-180, m_moveSpeed/2);
  m_pDrive->ForwardInInchGyro(150, m_moveSpeed);

  RotateToDegree(-225, m_moveSpeed/2);
  m_pDrive->SetLookingColorV(OldCameraVision::VisionColors::GREEN_CONE_A);
  m_pDrive->AlignWithVision(0, m_deadZone);
  m_pDrive->ForwardInInchGyro(60);

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
