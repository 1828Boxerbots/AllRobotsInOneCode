/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SpinSubsystemBase.h"
#include "Util.h"

SpinSubsystemBase::SpinSubsystemBase() {}

// This method will be called once per scheduler run
void SpinSubsystemBase::Periodic() {}

void SpinSubsystemBase::SpinSomeTimes(double R, double r, double revolutions) 
{
    /** circumference of spin wheel (c)
     * circumference of Wheel of Fortune (C)
     * target revolutions (V)
     * formula = VC/c
     */


    double seconds = (Util::PI*2*r / MOTORVELOCITY*GetMotorVoltage());

    SetSpinMotor();
    Util::DelayInSeconds(seconds);
    SetSpinMotor(0.0);
}


void SpinSubsystemBase::SpinSomeTimesEncoders(double R, double r, double revolutions) 
{
    /** circumference of spin wheel (c)
     * circumference of Wheel of Fortune (C)
     * target revolutions (V)
     * formula = VC/c
     */
    double seconds = (Util::PI*2*r / MOTORVELOCITY*GetMotorVoltage());

    SetSpinMotor();
    Util::DelayInSeconds(seconds);
    SetSpinMotor(0.0);
}
