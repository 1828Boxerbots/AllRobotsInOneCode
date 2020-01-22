/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/ShooterSubsystemBase.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

ShooterSubsystemBase::ShooterSubsystemBase() {}

// This method will be called once per scheduler run
void ShooterSubsystemBase::Periodic() {}

void ShooterSubsystemBase::Shoot(double shootSpeed)
{
    //The shooter shouldnt be able to shoot backwards
    shootSpeed = -Util::Limit(shootSpeed, 0.0);
    frc::SmartDashboard::PutNumber("Shoot Speed", shootSpeed);
    SetShootMotor(shootSpeed);
}

void ShooterSubsystemBase::ShootBump(bool bump)
{
    if(bump == true)
    {
        Shoot(SHOOTSPEED);
    }
    else
    {
        Shoot(0.0);
    }
    
}
