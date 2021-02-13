// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/PickUpLemonCommand.h"

PickUpLemonCommand::PickUpLemonCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, DriveTrainSubsystemBase *pDrive, double cenerScreen,
  double deadzoneRange, double motorspeed)
{
  // Use addRequirements() here to declare subsystem dependencies.
}

// Called when the command is initially scheduled.
void PickUpLemonCommand::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void PickUpLemonCommand::Execute()
 {
   m_pDrive->WhereToTurn()
 }

// Called once the command ends or is interrupted.
void PickUpLemonCommand::End(bool interrupted) {}

// Returns true when the command should end.
bool PickUpLemonCommand::IsFinished() {
  return false;
}
