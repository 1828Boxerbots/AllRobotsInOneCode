/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "..\subsystems\LoaderSubsystemBase.h"
#include "..\subsystems\ShooterSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ShootLoadCommand
    : public frc2::CommandHelper<frc2::CommandBase, ShootLoadCommand> {
 public:
  ShootLoadCommand(LoaderSubsystemBase *pLoader, ShooterSubsystemBase *pShooter
  , double encoderSetting, double motorSpeed = 0.0);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

private:
  LoaderSubsystemBase *m_pLoader = nullptr;
  ShooterSubsystemBase *m_pShooter = nullptr;
  double m_encoderSetting = 0.0;
  double m_motorSpeed = 0.0;
};
