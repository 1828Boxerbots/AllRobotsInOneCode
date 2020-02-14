/*----------------------------------------------------------------------------*/	
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */	
/* Open Source Software - may be modified and shared by FRC teams. The code   */	
/* must be accompanied by the FIRST BSD license file in the root directory of */	
/* the project.                                                               */	
/*----------------------------------------------------------------------------*/	

#include "subsystems/ArmSubsystemBase.h"	

ArmSubsystemBase::ArmSubsystemBase() {}	

// This method will be called once per scheduler run	

/*
void ArmSubsystemBase::LiftArmUp()	
{	
    m_armAngle += GetOneDegree() * GetScale();	
    m_armAngle = Util::Limit(m_armAngle, GetMinLimit(), GetMaxLimit());	
    LiftMotor(m_armAngle);	
}	

void ArmSubsystemBase::LiftArmDown()	
{	
    m_armAngle -= GetOneDegree() * GetScale();	
    m_armAngle = Util::Limit(m_armAngle, GetMinLimit(), GetMaxLimit());	
    LiftMotor(m_armAngle);	
}*/

//
//LiftSubsystem
//

void ArmSubsystemBase::Lift(double armSpeed)
{
    armSpeed = Util::Limit(armSpeed);
    frc::SmartDashboard::PutNumber("Lift Power", armSpeed);
    LiftMotor(armSpeed);
}

/*
void ArmSubsystemBase::Raise(bool bump)
{
    if(bump == true)
    {
        LimitedLift(m_liftSpeed);
    }
    else
    {
        Lift(0.0);
    }
    
}

void ArmSubsystemBase::Lower(bool bump)
{
    if(bump == true)
    {
        LimitedLift(-m_liftSpeed);
    }
    else
    {
        Lift(0.0);
    }
    
}

void ArmSubsystemBase::LimitedLift(double speed)
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
}*/