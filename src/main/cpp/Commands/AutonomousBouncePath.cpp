// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "../../include/Commands/AutonomousBouncePath.h"


AutonomousBouncePath::AutonomousBouncePath(DriveTrainSubsystemBase* pDrive, double radius) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pDrive = pDrive;
  m_turnRadius = radius;
  this->AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void AutonomousBouncePath::Initialize() 
{
  m_state = 3;
}

// Called repeatedly when this Command is scheduled to run
void AutonomousBouncePath::Execute() 
{
  switch(m_state)
  {
    // case 0:
    // ProcessState0();
    // break;
    // case 1:
    // ProcessState1();
    // break;
    // case 2:
    // ProcessState2();
    // break;
    case 3:
    ProcessState3();
    break;
    case 4:
    ProcessState4();
  }
}

// Called once the command ends or is interrupted.
void AutonomousBouncePath::End(bool interrupted) 
{

}

// Returns true when the command should end.
bool AutonomousBouncePath::IsFinished() 
{
  return false;
}

void AutonomousBouncePath::ProcessState0()
{
  if(m_state == 0)
  {
    m_pDrive->ForwardInInch(10,0,0.5);
    m_pDrive->TimedArcade(0.6,-0.2,1.3);
    m_pDrive->ForwardInInch(20,0,0.5);
    m_state = 1;
  }
}

void AutonomousBouncePath::ProcessState1()
{
  if(m_state == 1)
  {
    ///m_pDrive->TurnInDegrees(165,0.5, m_turnRadius); /original
    m_pDrive->TimedArcade(-0.9,-0.08,1.85); // Back waay out of the first bottle, and to the right
    m_pDrive->TimedArcade(-0.6,-0.3,1.42); // Reverse semicircle around cone
    m_pDrive->TimedArcade(-0.7,0.05,1.67); // Straight back into the second cone
    m_pDrive->ForwardInInch(70,0.0,0.7); // Straight forward
    m_state = 2;
  }
}

void AutonomousBouncePath::ProcessState2()
{
  if(m_state == 2)
  {
    m_pDrive->TimedArcade(0.6, -0.15, 2.55); // Wide turn around cones
    m_pDrive->ForwardInInch(85,0,0.7); // Forward to third cone
    m_pDrive->TimedArcade(-0.5,-0.17, 1.2); // Reverse into end
    ///m_pDrive->ForwardInInch(90,0,0.5);
    m_state = 3;
  }
}

void AutonomousBouncePath::ProcessState3()
{
  if(m_state == 3)
  {
    m_pDrive->ForwardInInchGyro(49);
    m_pDrive->TurnInDegreesGyro(90);
    m_pDrive->ForwardInInchGyro(44);
    m_pDrive->ForwardInInchGyro(-14);
    m_pDrive->TurnInDegreesGyro(22);
    m_pDrive->ForwardInInchGyro(-80);
    m_pDrive->TurnInDegreesGyro(23);
    m_pDrive->ForwardInInchGyro(-42.5);
    m_pDrive->TurnInDegreesGyro(90);
    m_pDrive->ForwardInInchGyro(-42.5);
    m_pDrive->TurnInDegreesGyro(45);
    m_pDrive->ForwardInInchGyro(-75);
    m_pDrive->ForwardInInchGyro(75);
    m_pDrive->TurnInDegreesGyro(45);
    m_pDrive->ForwardInInchGyro(42.5);
    m_pDrive->TurnInDegreesGyro(90);
    m_pDrive->ForwardInInchGyro(42.5);
    m_pDrive->TurnInDegreesGyro(45);
    m_pDrive->ForwardInInchGyro(75);
    m_pDrive->ForwardInInchGyro(-15);
    m_pDrive->TurnInDegreesGyro(45);
    m_pDrive->ForwardInInchGyro(-42.5);
    m_state = 4;
  }
}

void AutonomousBouncePath::ProcessState4()
{
  if(m_state == 4)
  {
    m_pDrive->ForwardInInch(10,0,-0.5);
    m_pDrive->TimedArcade(-0.6,-0.2,1.3);
    m_pDrive->ForwardInInch(20,0,-0.5);
    m_pDrive->SetLookingColorV(OldCameraVision::GREEN_CONE_N);
    m_pDrive->AlignWithVision(0.75, 30, false);
    m_pDrive->ForwardInInch(10,0,0.5);
    m_pDrive->TimedArcade(0.6,-0.2,1.3);
    m_pDrive->SetLookingColorV(OldCameraVision::PURPLE_BOTTLE_N);
    int cameraImage = m_pDrive->WhereToTurn();
    while(cameraImage<-2)
    {
      m_pDrive->Forward(0.5);
    }
    while(cameraImage>-2)
    {
      if(cameraImage<0)
      {
        m_pDrive->MoveArcade(0.3, -0.05);
      }
      else if(cameraImage>0)
      {
        m_pDrive->MoveArcade(0.3, 0.05);
      }
      else
      {
        m_pDrive->MoveArcade(0.3, 0.0);
      }
      cameraImage = m_pDrive->WhereToTurn();
    }
    m_pDrive->ForwardInInchGyro(100, -0.3);
    m_pDrive->AlignWithVision();

  }
}