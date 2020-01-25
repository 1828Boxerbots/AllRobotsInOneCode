/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/SLAL/DriveTrainSubsystemSLAL.h"
#include "subsystems/SLAL/LiftSubsystemSLAL.h"
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

 private:
  // The robot's subsystems and commands are defined here...

  //Controller
  DriveTrainSubsystemSLAL m_drive;
  LiftSubsystemSLAL m_lift;

  frc2::RunCommand m_armLift  {[this] {m_lift.Raise(true) ;}, {&m_lift}};
  frc2::RunCommand m_armLower {[this] {m_lift.Lower(true) ;}, {&m_lift}};
  frc2::RunCommand m_armStop  {[this] {m_lift.Raise(false);}, {&m_lift}};

  void ConfigureButtonBindings();
};
