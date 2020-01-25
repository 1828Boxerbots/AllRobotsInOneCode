/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/InstantCommand.h>
#include "Constants.h"
#include "subsystems/DriveTrainSubsystemBase.h"
#include "subsystems/LoaderSubsystemBase.h"
#include "subsystems/ShooterSubsystemBase.h"
#include "subsystems/Rocky/TurretSubsystemRocky.h"
//#include "subsystems/TurretSubsystemBase.h"

class RobotContainerBase {
 public:
  RobotContainerBase();

  protected:
    //Creating the controllers
    frc::XboxController m_controller{USB_CONTROLLER_ONE};
    frc::XboxController m_controller2{USB_CONTROLLER_TWO};

    //DriveTrain subsystem commands
    DriveTrainSubsystemBase *m_pDrive = nullptr;
    frc2::RunCommand m_driveTrainMoveTank   {[this] { if(m_pDrive != nullptr) m_pDrive->MoveTank(m_controller.GetY(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kRightHand)); }, {m_pDrive}};
    frc2::RunCommand m_driveTrainMoveArcade {[this] { if(m_pDrive != nullptr) m_pDrive->MoveArcade(m_controller.GetX(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kLeftHand)); }, {m_pDrive}};

    // Loader subsystem commands
    LoaderSubsystemBase *m_pLoader = nullptr;
    frc2::RunCommand m_loaderEject          {[this] { if(m_pLoader!=nullptr) m_pLoader->LoadXY(m_controller.GetAButton(), m_controller.GetBButton());}, {m_pLoader}};
    frc2::RunCommand m_loaderLoad           {[this] { if(m_pLoader!=nullptr) m_pLoader->LoadXY(m_controller.GetAButton(), m_controller.GetBButton());}, {m_pLoader}};
    frc2::RunCommand m_loaderStop           {[this] { if(m_pLoader!=nullptr) m_pLoader->LoadXY(false, false);}, {m_pLoader}};

    // Shooter subsystem commands
    ShooterSubsystemBase *m_pShooter = nullptr;
    frc2::RunCommand m_shooterSpin          {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(1.0);}, {m_pShooter}};
    frc2::RunCommand m_shooterEject         {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(-1.0);}, {m_pShooter}};
    frc2::RunCommand m_shooterStop          {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(0.0);}, {m_pShooter}};

    //TurretSubsystemBase *m_*pTurret = nullptr;
    TurretSubsystemRocky *m_pTurret = nullptr;
    frc2::RunCommand m_turretTurnLeft       {[this] { if (m_pTurret!=nullptr) m_pTurret->Turn(m_controller.GetAButton(), m_controller.GetBButton());}, {m_pTurret}};
    frc2::RunCommand m_turretTurnRight      {[this] { if (m_pTurret!=nullptr) m_pTurret->Turn(m_controller.GetAButton(), m_controller.GetBButton());}, {m_pTurret}};
    frc2::RunCommand m_turretStop           {[this] { if (m_pTurret!=nullptr) m_pTurret->Turn(false, false);}, {m_pTurret}};

};
