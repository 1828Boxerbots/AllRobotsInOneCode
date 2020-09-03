/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "subsystems/Robot2020/DriveTrainSubsystemRobot2020.h"
#include "subsystems/Robot2020/LoaderSubsystemRobot2020.h"
#include "subsystems/Robot2020/ShooterSubsystemRobot2020.h"
#include "subsystems/Robot2020/SpinSubsystemRobot2020.h"
#include "subsystems/Robot2020/ArmSubsystemRobot2020.h"
#include "subsystems/CameraSubsystemBase.h"
#include "RobotContainerBase.h"
#include "../Commands/ShootLoadCommand.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainerRobot2020 : public RobotContainerBase {
 public:
  RobotContainerRobot2020();

  void Init() override;
  void DisableInit() override;
  void TeleopPeriodic() override;

  void SetButtonA() override;
  void SetButtonB() override;
  void SetButtonX() override;
  void SetButtonY() override;
  void SetRightTrigger() override;
  void SetLeftBumper() override;
  void SetRightBumper() override;
  void SetStartButton() override;
  void SetBackButton() override;
  int ReadDioSwitch();

  frc2::Command* GetAutonomousCommand();

 private:
  ShootLoadCommand* m_pShootLoad = nullptr;

  double m_encoderSpeedWanted = -5500;
  double m_motorSpeed = 1.0;
  // The robot's subsystems and commands are defined here...

  void ConfigureButtonBindings();

};
