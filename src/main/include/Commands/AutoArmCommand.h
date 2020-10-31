/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "../include/subsystems/ArmSubsystemBase.h"
#include "../include/subsystems/SpinSubsystemBase.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class AutoArmCommand
    : public frc2::CommandHelper<frc2::CommandBase, AutoArmCommand> {
 public:
  AutoArmCommand(ArmSubsystemBase *pArm, SpinSubsystemBase *pSpin, double speed, /*ArmSubsystemBase::ArmPositions*/int wantedPos);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  private:
    //Subsystem Variables
    ArmSubsystemBase *m_pArm;
    SpinSubsystemBase *m_pSpin;
    
    //Sim Variables
    int upNum = 0;
    int downNum = 0;

    //Needed Variables
    int m_wantedPos;
    double m_speed;
    bool m_isFinished = false;

    //Timer STuff
    frc::Timer m_timer;
    double m_startTime = 0.0;

};