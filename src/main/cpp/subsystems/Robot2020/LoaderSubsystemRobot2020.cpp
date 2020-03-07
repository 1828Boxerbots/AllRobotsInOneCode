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
void LoaderSubsystemRobot2020::Periodic()
{
    #ifndef NOHW
    Util::Log("Load Photogate", m_photogate.Get());
    if (m_photogate.Get())
    {
        m_spike.TurnSpikeOn();
    }
    else
    {
        m_spike.TurnSpikeOff();
    }
    #endif
}

void LoaderSubsystemRobot2020::SetLoadMotor(double speed, int motorNumber)
{
    #ifndef NOHW
    switch (motorNumber)
    {
    case MOTOR_TOP:
        m_loaderMotorTop.Set(speed);
        break;
    
    case MOTOR_BOTTOM:
        m_loaderMotorBottom.Set(speed);
        break;
        

    case MOTOR_INTAKE:
        m_loaderMotorIntake.Set(speed);
        break;

    default:
        m_loaderMotorTop.Set(speed);
        m_loaderMotorIntake.Set(speed);
        m_loaderMotorBottom.Set(speed);
        break;
    }
    #endif
}

void LoaderSubsystemRobot2020::PhotogateStop(double speed)
{
    int count = 0;
    SetLoadMotor(speed);
    //Continue spining motor until photogate is set.
    while(m_photogate.Get() != true)
    {
        Util::Log("Spinning Loader", count++, GetName());
    }
    SetLoadMotor(0.0);
}

void LoaderSubsystemRobot2020::Init()
{
    #ifndef NOHW
    m_loaderMotorTop.SetInverted(true);
    m_loaderMotorIntake.SetInverted(true);
    m_loaderMotorBottom.SetInverted(false);
    #endif
}