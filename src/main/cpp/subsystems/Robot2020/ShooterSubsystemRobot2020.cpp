/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Robot2020/ShooterSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemRobot2020::ShooterSubsystemRobot2020() 
{
    Init();
    m_timer.Start();
    m_timer.Reset();
    m_shooterEncoder.Reset();
    m_startTime = m_timer.Get();
    m_encoderRawStart = m_shooterEncoder.GetRaw();
}

// This method will be called once per scheduler run
void ShooterSubsystemRobot2020::Periodic()
{
    EncoderSpeed();
}

double ShooterSubsystemRobot2020::EncoderSpeed()
{
    double difTime = m_timer.Get() -  m_startTime;
    double difRaw = m_shooterEncoder.GetRaw() - m_encoderRawStart;
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Time Dif", difTime);
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Raw Dif", difRaw);
    double speed = difRaw / difTime;
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Speed", speed);
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder", m_shooterEncoder.GetDistance());
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder RAW", m_shooterEncoder.GetRaw());
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder RATE", m_shooterEncoder.GetRate());
    m_encoderRawStart = m_shooterEncoder.GetRaw();
    m_startTime = m_timer.Get();
    return speed;
}

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
    #ifndef NOHW
    m_shooterEncoder.Reset();
    m_shooterEncoder.SetDistancePerPulse(1/PULSES_PER_ROTATION);
    m_shooterEncoder.SetReverseDirection(true);
    m_shooterMotor.SetInverted(true);
    #endif
}

void ShooterSubsystemRobot2020::ResetEncoder()
{
    #ifndef NOHW
    m_shooterEncoder.Reset();
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder", m_shooterEncoder.GetDistance());
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder RAW", m_shooterEncoder.GetRaw());
    frc::SmartDashboard::PutNumber("Robot2020 Shooter Encoder RATE", m_shooterEncoder.GetRate());
    #endif
}
