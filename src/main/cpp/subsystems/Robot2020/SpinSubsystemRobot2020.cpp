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
    uint8_t arr[2];  
    m_multiplexer.Write(1 << position, 0x00);
    m_multiplexer.Read(0x01, 2, arr);
    uint16_t val = (arr[1] << 8) | arr[0];
    frc::SmartDashboard::PutNumber("Mux Value", val);
}

void SpinSubsystemRobot2020::Init()
{

}


void SpinSubsystemRobot2020::SetSpinMotor (double speed)
{

}


double SpinSubsystemRobot2020::GetNumberOfTicks(double R, double revolutions, double r) 
{
    return 0.0;
}


double SpinSubsystemRobot2020::GetEncoderTicks()
{
    return 0.0;
}

