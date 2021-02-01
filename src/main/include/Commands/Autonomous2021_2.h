// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/commands/Command.h>
#include "subsystems/DriveTrainSubsystemBase.h"

class Autonomous2021_2 : public frc::Command {
 public:
  Autonomous2021_2(DriveTrainSubsystemBase *pDrive);
  void Initialize() override;
  void Execute() override;
  bool IsFinished() override;
  void End() override;
  void Interrupted() override;
 private:

  int m_loops = 0;
  double GetCameraState();
  void loop1();
  void loop2();
  void loop3();
  void loop4();
  void loop5();
  void loop6();
  void SwitchColor(DriveTrainSubsystemBase::Colors color);

  DriveTrainSubsystemBase *m_pDrive = nullptr;
};
