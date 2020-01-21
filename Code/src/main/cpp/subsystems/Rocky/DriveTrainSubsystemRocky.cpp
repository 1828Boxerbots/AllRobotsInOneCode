/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rocky/DriveTrainSubsystemRocky.h"

DriveTrainSubsystemRocky::DriveTrainSubsystemRocky() {}

// This method will be called once per scheduler run
void DriveTrainSubsystemRocky::Periodic() {}
 void DriveTrainSubsystemRocky::MoveTank(double leftY, double rightY)
  { 
    leftY = Util::Limit(leftY, -.7, .7);
    rightY = Util::Limit(rightY, -.7, .7);
    frc::SmartDashboard::PutNumber("Drive Left", leftY);
    frc::SmartDashboard::PutNumber("Drive Right", rightY);

    #ifndef NOHW
    m_leftMotor.Set(leftY);
    m_rightMotor.Set(rightY);
    #endif
  }


  void DriveTrainSubsystemRocky::Init()
  {
    #ifndef NOHW
    m_rightMotor.SetInverted(false);
    m_leftMotor.SetInverted(true);
    #endif
  }