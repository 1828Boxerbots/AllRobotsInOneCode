/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/LipALoop/DriveTrainSubsystemLipALoop.h"
#include "subsystems/LipALoop/ArmSubsystemLipALoop.h"
#include "subsystems/LipALoop/WristSubsystemLipALoop.h"
#include "subsystems/LipALoop/HandSubsystemLipALoop.h"
#include "RobotContainerBase.h"
#include "subsystems/CameraSubsystemBase.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerLipALoop : public RobotContainerBase
{
 public:
  RobotContainerLipALoop();

  frc2::Command* GetAutonomousCommand();

 private:
  // The robot's subsystems and commands are defined here...

  //Controller
  DriveTrainSubsystemLipALoop m_drive;
  CameraSubsystemBase m_camera;

  //Arm Control
  ArmSubsystemLipALoop m_arm;
  frc2::RunCommand m_armUp{[this] {m_arm.LiftArmUp();}, {&m_arm}};
  frc2::RunCommand m_armDown{[this] {m_arm.LiftArmDown();}, {&m_arm}};
  frc2::RunCommand m_armStop{[this] {m_arm.MoveArmStop();}, {&m_arm}};

  //Wrist Control
  WristSubsystemLipALoop m_wrist;
  frc2::RunCommand m_wristUp{[this] {m_wrist.MoveWristUp();}, {&m_wrist}};
  frc2::RunCommand m_wristDown{[this] {m_wrist.MoveWristDown();}, {&m_wrist}};
  frc2::RunCommand m_wristStop{[this] {m_wrist.MoveWristStop();}, {&m_wrist}};

  //Hand Control
  HandSubsystemLipALoop m_hand;
  frc2::RunCommand m_handUp{[this] {m_hand.MoveHandOpen();}, {&m_hand}};
  frc2::RunCommand m_handDown{[this] {m_hand.MoveHandClose();}, {&m_hand}};
  frc2::RunCommand m_handStop{[this] {m_hand.MoveHandStop();}, {&m_hand}};

  //Align Control
  void ConfigureButtonBindings();
  frc2::SequentialCommandGroup m_align = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand {[this] {m_camera.Init();}, {&m_camera}},
    frc2::InstantCommand{[this]
    {
      int direction = m_camera.WhereToTurn(); 
      while(direction != 0)
      {
        m_camera.Tick();
        if (direction == 1)
        {
          m_drive.TurnRight(0.1);
          direction = m_camera.WhereToTurn(); 
        }
        else if (direction == -1)
        {
          m_drive.TurnLeft(0.1);
          direction = m_camera.WhereToTurn(); 
        }
        direction = m_camera.WhereToTurn(); 
      }
      m_drive.Stop();
    }, {&m_camera, &m_drive}}
  };

  frc2::SequentialCommandGroup m_follower = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand {[this] {m_camera.Init();}, {&m_camera}},
    frc2::InstantCommand{[this]
    {
      int direction = m_camera.WhereToTurn(); 
      while(true)
      {
        m_camera.Tick();
        if (direction == 1)
        {
          m_drive.TurnRight(0.3);
          direction = m_camera.WhereToTurn(); 
        }
        else if (direction == -1)
        {
          m_drive.TurnLeft(0.3);
          direction = m_camera.WhereToTurn(); 
        }
        else
        {
          m_drive.Stop();
        }
        direction = m_camera.WhereToTurn(); 
      }
    }, {&m_camera, &m_drive}}
  };
};
