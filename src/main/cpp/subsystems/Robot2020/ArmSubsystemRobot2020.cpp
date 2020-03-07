/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/ArmSubsystemRobot2020.h"

ArmSubsystemRobot2020::ArmSubsystemRobot2020() {}

// This method will be called once per scheduler run
void ArmSubsystemRobot2020::Periodic() 
{
    //Log the Halleffects
    Log("Lower HallEffect", m_hallEffectLower.Get());
    Log("Upper HallEffect", m_hallEffectUpper.Get());
}

void ArmSubsystemRobot2020::Init()
{
    //SetPosition(LOWEST_POS);
}

void ArmSubsystemRobot2020::DisableInit()
{
    //SetPosition(LOWEST_POS);
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

void ArmSubsystemRobot2020::LiftArmUp(double scale, double speed)
{
    SetMotor(speed * scale);
}

void ArmSubsystemRobot2020::LiftArmDown(double scale, double speed)
{
    SetMotor(-speed * scale);
}

void ArmSubsystemRobot2020::Raise(double speed)
{
    SetMotor(speed * m_scale);
}

void ArmSubsystemRobot2020::Lower(double speed)
{
    SetMotor(-speed * m_scale);
}

int ArmSubsystemRobot2020::GetPosition()
{
    if(m_hallEffectLower.Get() == true)
    {
        return LOWEST_POS;
    }
    if(m_hallEffectUpper.Get() == true)
    {
        return HIGHEST_POS;
    }
    return INVALID_POS;
}

void ArmSubsystemRobot2020::SetPosition(int pos)
{
    Log("Pos", pos);
    Log("Lower HallEffect", m_hallEffectLower.Get());
    Log("Upper HallEffect", m_hallEffectUpper.Get());
    //Switch Statement to check what position we want to go to
    switch (pos)
    {
    case LOWEST_POS:
    //Checks if either the HallEffect or encoder is true and moves the arm up until it is
        while(m_hallEffectLower.Get() == true /*|| m_armEncoder.Get() != m_lowValue*/)
        {
            LiftArmDown(m_scale);
            frc::SmartDashboard::PutString("Condition", "Moving Down");
        }
        StopMotor();
        frc::SmartDashboard::PutString("Condition", "Done");
        break;
    case LOWEST_POS_TIME:
    //Starts Lowering the arm and waits X number of secounds then stops
        LiftArmDown(m_scale);
        //Util::DelayInSeconds(m_armDownTime);
        StopMotor();
        break;
    case HIGHEST_POS:
    //Checks if either the HallEffect or encoder is true and moves the arm down until it is
        while(m_hallEffectUpper.Get() == true /*|| m_armEncoder.Get() != m_highValue*/)
        {
            LiftArmUp(m_scale);
            frc::SmartDashboard::PutString("Condition", "Moving Up");
        }
        //Util::DelayInSeconds(.15);
        StopMotor();
        frc::SmartDashboard::PutString("Condition", "Done");
        break;
    default:
        //If position is not 0 or 1 the arm motor will stop
        StopMotor();
        break;
    }
}
