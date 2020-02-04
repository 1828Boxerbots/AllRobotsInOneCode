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

void SpinSubsystemBase::SpinWithEncoders(double R, double r, double revolutions) 
{
    double limit = GetNumberOfTicks(R, revolutions, r);

    SetSpinMotor();
    do
    {
        Log();
    }
    while(GetEncoderTicks() < limit);
    SetSpinMotor(0.0);
}

double SpinSubsystemBase::GetNumberOfTicks(double R, double revolutions, double r)
{
    double value = (256*revolutions*R)/r ;
    return value;
}

void SpinSubsystemBase::Log()
{
<<<<<<< Updated upstream
    /* circumference of spin wheel (c)
     * circumference of Wheel of Fortune (C)
     * target revolutions (V)
     * formula = VC/c
     */
    double seconds = (Util::PI*2*r / MOTORVELOCITY*GetMotorVoltage());
=======
    frc::SmartDashboard::PutNumber("Spin Encoder Value", m_encoder);
    frc::SmartDashboard::PutNumber("Current (sensor) Color", ReadColorSensor());
    frc::SmartDashboard::PutNumber("Current (field) Color", Map(ReadColorSensor()));
}
>>>>>>> Stashed changes

int SpinSubsystemBase::Map(int color)
{
    // Turns the given color into the color that the field reads
    color += 2;
    // Makes sure that the color maps correctly
    color %= 4;
    return color;
}

void SpinSubsystemBase::SpinUntilColor(int targetColor)
{
    SetSpinMotor();
    do
    {
        Log();
    }
    while(Map(ReadColorSensor()) != targetColor);
    SetSpinMotor(0.0);
}
