/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Robot2020/ShooterSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemRobot2020::ShooterSubsystemRobot2020() {}

// This method will be called once per scheduler run

void ShooterSubsystemRobot2020::SetShootMotor(double speed)
{
    #ifndef NOHW
    m_shooterMotor.Set(speed);
    #endif
}

void ShooterSubsystemRobot2020::Init()
{
    #ifndef NOHW
    m_shooterEncoder.Reset();
    #endif
}

void ShooterSubsystemRobot2020::DisableInit()
{

}

double ShooterSubsystemRobot2020::GetEncoderSpeed()
{
    #ifndef NOHW
    m_shooterEncoder.GetRate();
    #endif
}
