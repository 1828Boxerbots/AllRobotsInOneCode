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

void ArmSubsystemRobot2020::Init()
{

}

void ArmSubsystemRobot2020::DisableInit()
{
    
}

void ArmSubsystemRobot2020::LiftMotor(double speed)
{
    #ifndef NOHW
    m_armMotor.Set(speed);
    #endif
}

void ArmSubsystemRobot2020::Raise(double speed)
{
    LiftMotor(speed);
}

void ArmSubsystemRobot2020::Lower(double speed)
{
    LiftMotor(-speed);
}

void ArmSubsystemRobot2020::ArmPosition(int pos)
{
    switch (pos)
    {
    case UPPER_POS:
        Raise();
        while(m_hallEffectUpper.Get() != true)
        {
        }
        StopMotor();
        break;
    case LOWER_POS:
        Lower();
        while(m_hallEffectLower.Get() != true)
        {
        }
        StopMotor();
        break;
    case MIDDLE_POS:
        /*
        while(m_hallEffectMiddle.Get() != true)
        {
            if(m_hallEffectUpper.Get() == true)
            {
                Lower();
                if(m_hallEffectLower.Get() == true)
                {
                    Raise();
                }
            }
            else if(m_hallEffectUpper.Get() != false)
            {
                Raise();
            }

        }
        */
       Raise();
       while(m_hallEffectMiddle.Get() != true)
        {
            if ( m_hallEffectUpper.Get() == true)
            {
                Lower();
            }
            if (m_hallEffectLower.Get() == true)
            {
                Raise();
            }
        }
        StopMotor();
        break;
       
    default:
        break;
    }
}
