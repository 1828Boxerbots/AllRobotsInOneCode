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
    ArmPosition(LOWER_POS);
}

void ArmSubsystemRobot2020::DisableInit()
{
    ArmPosition(LOWER_POS);
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
    //Switch Statement to check what position we want to go to
    switch (pos)
    {
    case LOWER_POS:
    //Checks if either the HallEffect or encoder is true and moves the arm up until it is
        while(m_hallEffectLower.Get() != true || m_armEncoder.Get() != m_lowValue)
        {
            LiftArmDown();
        }
        break;
    case UPPER_POS:
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
