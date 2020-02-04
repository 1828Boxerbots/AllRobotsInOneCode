/*----------------------------------------------------------------------------*/	
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */	
/* Open Source Software - may be modified and shared by FRC teams. The code   */	
/* must be accompanied by the FIRST BSD license file in the root directory of */	
/* the project.                                                               */	
/*----------------------------------------------------------------------------*/	

#include "subsystems/ArmSubsystemBase.h"	

ArmSubsystemBase::ArmSubsystemBase() {}	

// This method will be called once per scheduler run	

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
}