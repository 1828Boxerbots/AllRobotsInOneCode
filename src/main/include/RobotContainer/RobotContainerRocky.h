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
  int ReadDioSwitch();

 private:
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();




  frc2::SequentialCommandGroup m_autoTestOne = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand{[this]
    { if(m_pDrive != nullptr && m_pDistance != nullptr) 
      {
        double travelDistance = 60.0;
        double tolerance = 2.0;
        double currentDistance = m_pDistance->GetDistanceInInch();
        while(currentDistance < travelDistance-tolerance || currentDistance > travelDistance+tolerance)
        {
          if(currentDistance > travelDistance)
          {
            m_pDrive->Forward(1.0);
          }
          else
          {
            m_pDrive->Forward(-1.0);
          }
          currentDistance = m_pDistance->GetDistanceInInch();
        }
        m_pDrive->Stop();
      }
    }, {m_pDrive, m_pDistance}}
  };

  frc2::SequentialCommandGroup m_follower = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand {[this] {if(m_pCamera != nullptr)m_pCamera->Init();}, {m_pCamera}},
    frc2::InstantCommand{[this]
    {
      if(m_pCamera == nullptr || m_pDrive == nullptr)
      {
        return; 
      }
      int direction = m_pCamera->WhereToTurn(); 
      while(true)
      {
        m_pCamera->Tick();
        if (direction == 1)
        {
          m_pDrive->TurnRight(0.3);
          direction = m_pCamera->WhereToTurn(); 
        }
        else if (direction == -1)
        {
          m_pDrive->TurnLeft(0.3);
          direction = m_pCamera->WhereToTurn(); 
        }
        else
        {
          m_pDrive->Stop();
        }
        direction = m_pCamera->WhereToTurn(); 
      }
    }, {m_pCamera, m_pDrive}}
  };

  frc2::SequentialCommandGroup m_autoTitoTest = frc2::SequentialCommandGroup
  {
    m_driveInit,
    m_driveForward12In0Deg,
    m_driveStop
  };


};
