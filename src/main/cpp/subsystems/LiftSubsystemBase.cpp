/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/LiftSubsystemBase.h"
#include <frc/smartdashboard/SmartDashboard.h>

LiftSubsystemBase::LiftSubsystemBase() {}

// This method will be called once per scheduler run
void LiftSubsystemBase::Periodic() {}

void LiftSubsystemBase::Lift(double armSpeed)
{
    armSpeed = Util::Limit(armSpeed);
    frc::SmartDashboard::PutNumber("Lift Power", armSpeed);
    LiftMotor(armSpeed);
}

void LiftSubsystemBase::Raise(bool bump)
{
    if(bump == true)
    {
        LimitedLift(LIFTSPEED);
    }
    else
    {
        Lift(0.0);
    }
    
}

void LiftSubsystemBase::Lower(bool bump)
{
    if(bump == true)
    {
        LimitedLift(-LIFTSPEED);
    }
    else
    {
        Lift(0.0);
    }
    
}

void LiftSubsystemBase::LimitedLift(double speed)
{
    if(speed < 0.0)
    {
        if(LowerLimitHit() == true)
        {
            StopMotor();
        } 
        else
        {
            Lift(speed);
        }
    }
    else 
    {
        if(UpperLimitHit() == true)
        {
            StopMotor();
        }
        else
        {
           Lift(speed); 
        }
    }
}
