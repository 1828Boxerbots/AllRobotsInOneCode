/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/SLAL/DriveTrainSubsystemSLAL.h"
#include "subsystems/SLAL/ArmSubsystemSLAL.h"
#include "RobotContainerBase.h"


/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerSLAL : public RobotContainerBase{
 public:
  RobotContainerSLAL();

  frc2::Command* GetAutonomousCommand();

  void Init() override {}
  void DisableInit() override {}
  void SetLeftBumper() override;
  void SetRightBumper() override;

 private:
  // The robot's subsystems and commands are defined here...

  //Controller

  void ConfigureButtonBindings();
};
