/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SpinSubsystemBase.h"
#include "Util.h"
#include <frc/smartdashboard/SmartDashboard.h>

SpinSubsystemBase::SpinSubsystemBase() {}

// This method will be called once per scheduler run
void SpinSubsystemBase::Periodic() {}

void SpinSubsystemBase::SpinWithEncoders(double targetRadius, double ourRadius, double revolutions) 
{
    double limit = GetNumberOfTicks(targetRadius, revolutions, ourRadius);

    SetSpinMotor();
    do
    {
        Log();
    }
    while(GetEncoderTicks() < limit);
    SetSpinMotor(0.0);
}

double SpinSubsystemBase::GetNumberOfTicks(double targetRadius, double revolutions, double ourRadius)
{
    double value = (GetTicksPerRevolution()*revolutions*targetRadius)/ourRadius ;
    frc::SmartDashboard::PutNumber("Spin Target Number Ticks", value);
    return value;
}

void SpinSubsystemBase::Log()
{
    frc::SmartDashboard::PutNumber("Spin Encoder Value", m_encoder);
    frc::SmartDashboard::PutNumber("Current (sensor) Color", ReadColorSensor());
    frc::SmartDashboard::PutNumber("Current (field) Color", (int)MapColors(ReadColorSensor()));
}

SpinSubsystemBase::FMSColors SpinSubsystemBase::MapColors(FMSColors color)
{
    // Turns the given color into the color that the field reads
    int newcolor = (int)color;
    newcolor += 2;
    // Makes sure that the color maps correctly
    newcolor %= 4;
    FMSColors finalcolor = (FMSColors)newcolor;
    return finalcolor;
}


void SpinSubsystemBase::SpinUntilColor(FMSColors targetColor)
{
    if ( targetColor == INVALID)
    {
        targetColor = m_color;
    }
    SetSpinMotor();
    do
    {
        Log();
    }
    while(MapColors(ReadColorSensor()) != targetColor);
    SetSpinMotor(0.0);
}


void SpinSubsystemBase::InterpretFMS(std::string rawColor)
{
    if (rawColor.length() == 0)
    {
        return;
    }

    switch (rawColor[0])
    {
        case 'B' :
            m_color = BLUE;
            break;
        case 'G' :
            m_color = GREEN;
            break;
        case 'R' :
            m_color = RED;
            break;
        case 'Y' :
            m_color = YELLOW;
            break;
        default:
            m_color = INVALID; 
            break;
    }
}
