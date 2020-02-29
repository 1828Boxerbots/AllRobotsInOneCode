/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/SpinSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>

SpinSubsystemRobot2020::SpinSubsystemRobot2020() {}

void SpinSubsystemRobot2020::MultiplexerSelect(int position)
{
    //Put Multiplexer Stuff here
}

void SpinSubsystemRobot2020::Init()
{
    m_spinEncoder.Reset();
}


void SpinSubsystemRobot2020::SetSpinMotor (double speed)
{
    m_spinMotor.Set(speed * m_scale);
}

double SpinSubsystemRobot2020::GetNumberOfTicks(double R, double revolutions, double r) 
{
    return 0.0;
}


double SpinSubsystemRobot2020::GetEncoderTicks()
{
    return 0.0;
}

