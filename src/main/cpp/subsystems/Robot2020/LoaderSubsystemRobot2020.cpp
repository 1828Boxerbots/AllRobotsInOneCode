/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/subsystems/Robot2020/LoaderSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../include/Util.h"

LoaderSubsystemRobot2020::LoaderSubsystemRobot2020() {}

// This method will be called once per scheduler run


void LoaderSubsystemRobot2020::SetLoadMotor(double speed)
{
    #ifndef NOHW
    m_loaderMotorTop.Set(speed);
    m_loaderMotorBottom.Set(speed);
    m_loaderMotorMiddle.Set(speed);
    #endif
}

void LoaderSubsystemRobot2020::PhotogateStop(double speed)
{
    SetLoadMotor(speed);
    while(m_photogate.Get() != true)
    {
        
    }
}