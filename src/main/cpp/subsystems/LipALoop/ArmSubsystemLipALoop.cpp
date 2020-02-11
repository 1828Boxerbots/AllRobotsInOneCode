/*----------------------------------------------------------------------------*/	
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */	
/* Open Source Software - may be modified and shared by FRC teams. The code   */	
/* must be accompanied by the FIRST BSD license file in the root directory of */	
/* the project.                                                               */	
/*----------------------------------------------------------------------------*/	
#include "subsystems/LipALoop/ArmSubsystemLipALoop.h"


ArmSubsystemLipALoop::ArmSubsystemLipALoop() {}


void ArmSubsystemLipALoop::Init()
{	
    ResetToZero();	
    #ifndef NOHW	
    m_armAngle = m_armServo.Get();	
    #endif	
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);	
}	

void ArmSubsystemLipALoop::DisableInit()
{
    ResetToZero();	
    #ifndef NOHW	
    m_armAngle = m_armServo.Get();	
    #endif	
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);
}

void ArmSubsystemLipALoop::LiftServo(double angle)	
{	
    m_armAngle = angle;	
    #ifndef NOHW	
    m_armServo.Set(m_armAngle);	
    #endif	
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);	
}	

void ArmSubsystemLipALoop::LiftArmUp()
{
    m_armAngle += GetOneDegree() * GetScale();	
    m_armAngle = Util::Limit(m_armAngle, GetMinLimit(), GetMaxLimit());	
    LiftMotor(m_armAngle);	
}

void ArmSubsystemLipALoop::LiftArmDown()
{
    m_armAngle -= GetOneDegree() * GetScale();	
    m_armAngle = Util::Limit(m_armAngle, GetMinLimit(), GetMaxLimit());	
    LiftMotor(m_armAngle);	
}

void ArmSubsystemLipALoop::MoveArmStop()	
{	
    LiftMotor(m_armAngle);	
}	

void ArmSubsystemLipALoop::ResetToZero()	
{	
    #ifndef NOHW	
    m_armServo.Set(0.0);	
    m_armAngle = m_armServo.Get();	
    #else	
    m_armAngle = 0.0;	
    #endif	
    frc::SmartDashboard::PutNumber("Arm Servo", m_armAngle);	
}	

double ArmSubsystemLipALoop::GetOneDegree()	
{	
    return m_oneDegree;	
}	

double ArmSubsystemLipALoop::GetScale()	
{	
    return m_motorScale;	
}	

double ArmSubsystemLipALoop::GetMaxLimit()	
{	
    return ARM_MAX;	
}	

double ArmSubsystemLipALoop::GetMinLimit()	
{	
    return ARM_MIN;	
}	
