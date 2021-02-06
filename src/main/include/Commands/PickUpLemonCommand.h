// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "..\subsystems\LoaderSubsystemBase.h"
#include "..\subsystems\ShooterSubsystemBase.h"
#include "..\subsystems\DriveTrainSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class PickUpLemonCommand
    : public frc2::CommandHelper<frc2::CommandBase, PickUpLemonCommand> {
 public:
  PickUpLemonCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter, DriveTrainSubsystemBase *pDrive, double cenerScreen,
  double deadzoneRange, double motorspeed);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    LoaderSubsystemBase *m_pLoader = nullptr;
    ShooterSubsystemBase *m_pShooter = nullptr;
    DriveTrainSubsystemBase *m_pDrive = nullptr;

    double m_centerScreen = 0.0;
    double m_deadzoneRange = 50;
    double m_speed = 0.4;
};
