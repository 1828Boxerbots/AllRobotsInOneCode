/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/SLAL/ArmSubsystemSLAL.h"
#include <frc/smartdashboard/SmartDashboard.h>

ArmSubsystemSLAL::ArmSubsystemSLAL() {}

// This method will be called once per scheduler run

void ArmSubsystemSLAL::LiftMotor(double speed)
{
    #ifndef NOHW
    m_liftMotorOne.Set(speed);
    m_liftMotorTwo.Set(-speed);
    #endif 
}

bool ArmSubsystemSLAL::UpperLimitHit()
{
   #ifndef NOHW
   return m_topSwitch.Get();
   #else
   return false;
   #endif
}

bool ArmSubsystemSLAL::LowerLimitHit()
{
   #ifndef NOHW
   return m_bottomSwitch.Get();
   #else
   return false;
   #endif
}