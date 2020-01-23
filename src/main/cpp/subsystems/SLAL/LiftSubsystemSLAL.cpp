/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SLAL/LiftSubsystemSLAL.h"
#include <frc/smartdashboard/SmartDashboard.h>

LiftSubsystemSLAL::LiftSubsystemSLAL() {}

// This method will be called once per scheduler run

void LiftSubsystemSLAL::LiftMotor(double speed)
{
    #ifndef NOHW
    m_liftMotorOne.Set(speed);
    m_liftMotorTwo.Set(-speed);
    #endif
}
