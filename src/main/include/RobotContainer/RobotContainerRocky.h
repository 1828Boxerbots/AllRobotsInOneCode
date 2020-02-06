/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Rocky/DriveTrainSubsystemRocky.h"
#include "subsystems/Rocky/TurretSubsystemRocky.h"
#include "subsystems/Rocky/LoaderSubsystemRocky.h"
#include "subsystems/Rocky/ShooterSubsystemRocky.h"
#include "RobotContainerBase.h"
#include "subsystems/CameraSubsystemBase.h"
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/InstantCommand.h>

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerRocky : public RobotContainerBase{
 public:
  RobotContainerRocky();

  frc2::Command* GetAutonomousCommand();

  virtual void Init();
  virtual void DisableInit();

 private:
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();
};
