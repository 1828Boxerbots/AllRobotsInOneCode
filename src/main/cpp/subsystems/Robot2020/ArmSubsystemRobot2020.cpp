/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/ArmSubsystemRobot2020.h"

ArmSubsystemRobot2020::ArmSubsystemRobot2020() {}

// This method will be called once per scheduler run
void ArmSubsystemRobot2020::Periodic() {}
<<<<<<< HEAD

void ArmSubsystemRobot2020::Init()
{
    SetPosition(LOWEST_POS);
}

void ArmSubsystemRobot2020::DisableInit()
{
    SetPosition(LOWEST_POS);
}

void ArmSubsystemRobot2020::SetMotor(double speed)
{
    #ifndef NOHW
    m_armMotor.Set(speed);
    #endif
}

double ArmSubsystemRobot2020::GetMotor()
{
    #ifndef NOHW
    return m_armMotor.Get();
    #else
    return 0.0;
    #endif
}

void ArmSubsystemRobot2020::Raise(double speed)
{
    SetMotor(speed);
}

void ArmSubsystemRobot2020::Lower(double speed)
{
    SetMotor(-speed);
}

int ArmSubsystemRobot2020::GetPosition()
{
    if(m_hallEffectLower.Get() == true || m_armEncoder.Get() == m_lowValue)
    {
        return LOWEST_POS;
    }
    if(m_hallEffectUpper.Get() == true || m_armEncoder.Get() == m_highValue)
    {
        return HIGHEST_POS;
    }
    return INVALID_POS;
}

void ArmSubsystemRobot2020::SetPosition(int pos)
{
    //Switch Statement to check what position we want to go to
    switch (pos)
    {
    case LOWEST_POS:
    //Checks if either the HallEffect or encoder is true and moves the arm up until it is
        while(m_hallEffectLower.Get() != true || m_armEncoder.Get() != m_lowValue)
        {
            LiftArmDown();
        }
        break;
    case HIGHEST_POS:
    //Checks if either the HallEffect or encoder is true and moves the arm down until it is
        while(m_hallEffectUpper.Get() != true || m_armEncoder.Get() != m_highValue)
        {
            LiftArmUp();
        }
        break;
    default:
        //If position is not 0 or 1 the arm motor will stop
        StopMotor();
        break;
    }
}
=======
>>>>>>> c7c9617f0c5954d55d533c1af7ed69617e1556af
