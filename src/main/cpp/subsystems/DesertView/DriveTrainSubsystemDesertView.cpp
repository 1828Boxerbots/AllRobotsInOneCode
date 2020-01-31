/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DesertView/DriveTrainSubsystemDesertView.h"
#include "frc/smartdashboard/SmartDashboard.h"

DriveTrainSubsystemDesertView::DriveTrainSubsystemDesertView() {}

void DriveTrainSubsystemDesertView::SetMotorL(double speed) 
{
  #ifndef NOHW
  m_leftMotor.Set(speed);
  PhotoTrigger();
  GetAnalogPhotoDiode();
  GetAnalogHallEffect();
  GetHallEffectSwitch();
  GetHallEffectLatch();
  #endif
}

void DriveTrainSubsystemDesertView::SetMotorR(double speed) 
{
  #ifndef NOHW
  m_rightMotor.Set(speed);
  #endif
}

void DriveTrainSubsystemDesertView::PhotoTrigger()
{
  #ifndef NOHW
  bool triggered = m_photogate.Get();
  frc::SmartDashboard::PutBoolean("Triggered?", triggered);
  #endif
}

void DriveTrainSubsystemDesertView::GetAnalogHallEffect()
{
  #ifndef NOHW
  double sensorval = m_analogHallEffect.GetVoltage();
  frc::SmartDashboard::PutNumber("Raw AnalogHallEffect", sensorval);
  if (sensorval >= 1.50)
  {
    frc::SmartDashboard::PutString("Detected Pole:", "Strong North");
  }
  else if (sensorval <= 0.5)
  {
    frc::SmartDashboard::PutString("Detected Pole:", "Strong South");
  }
  else
  {
    frc::SmartDashboard::PutString("Detected Pole:", "None");
  }
  #endif
}

void DriveTrainSubsystemDesertView::GetAnalogPhotoDiode()
{
  #ifndef NOHW
  double sensorval = m_analogPhotoDiode.GetVoltage();
  frc::SmartDashboard::PutNumber("Raw Analog PhotoDiode", sensorval);
  #endif
}

void DriveTrainSubsystemDesertView::GetHallEffectSwitch()
{
  #ifndef NOHW
  bool state = !(m_hallEffectSwitch.Get());
  frc::SmartDashboard::PutBoolean("Last Near South?", state);
  #endif
}

void DriveTrainSubsystemDesertView::GetHallEffectLatch()
{
  #ifndef NOHW
  bool state = !(m_hallEffectLatch.Get());
  frc::SmartDashboard::PutBoolean("Last Near North?", state);
  #endif
}

void DriveTrainSubsystemDesertView::Init()
{
  #ifndef NOHW
  m_leftMotor.SetInverted(false);
  m_rightMotor.SetInverted(true);
  #endif
}