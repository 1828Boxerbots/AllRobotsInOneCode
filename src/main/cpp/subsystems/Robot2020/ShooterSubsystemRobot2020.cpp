/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Robot2020/ShooterSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemRobot2020::ShooterSubsystemRobot2020() {Init();}

// This method will be called once per scheduler run

void ShooterSubsystemRobot2020::SetShootMotor(double speed)
{
    #ifndef NOHW
    m_shooterMotor.Set(speed);
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder", m_shooterEncoder.GetDistance());
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder RAW", m_shooterEncoder.GetRaw());
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder RATE", m_shooterEncoder.GetRate());

    #endif
}
void ShooterSubsystemRobot2020::Init()
{
    m_shooterEncoder.SetDistancePerPulse(1/256);
}
