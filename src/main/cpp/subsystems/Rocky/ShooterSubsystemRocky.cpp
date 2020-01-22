/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Rocky/ShooterSubsystemRocky.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemRocky::ShooterSubsystemRocky() {}

// This method will be called once per scheduler run

void ShooterSubsystemRocky::SetShootMotor(double speed)
{
    #ifndef NOHW
    m_shooterMotor.Set(speed);
    #endif
}
