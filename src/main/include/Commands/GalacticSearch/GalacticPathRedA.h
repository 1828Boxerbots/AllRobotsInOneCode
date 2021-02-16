// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

#include "../../subsystems/DriveTrainSubsystemBase.h"
#include "../../subsystems/LoaderSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class GalacticPathRedA
    : public frc2::CommandHelper<frc2::CommandBase, GalacticPathRedA> 
{
 public:
  GalacticPathRedA(DriveTrainSubsystemBase *pDrive, LoaderSubsystemBase *pLoader, double radius);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  void GetBallOne();
  void GetBallTwo();
  void GetBallThree();
  void ToEndZone();

private:
  DriveTrainSubsystemBase* m_pDrive = nullptr;
  LoaderSubsystemBase* m_pLoader;
  int m_state = 0;
  double m_turnRadius = 11;
};
