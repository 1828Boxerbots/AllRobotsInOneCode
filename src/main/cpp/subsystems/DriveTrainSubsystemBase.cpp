/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainSubsystemBase.h"

DriveTrainSubsystemBase::DriveTrainSubsystemBase() {}

// This method will be called once per scheduler run
void DriveTrainSubsystemBase::Periodic() {}
void DriveTrainSubsystemBase::MoveTank(double leftY, double rightY)
{ 
    leftY = Util::Limit(leftY, -.7, .7);
    rightY = Util::Limit(rightY, -.7, .7);
    frc::SmartDashboard::PutNumber("Drive Left", leftY);
    frc::SmartDashboard::PutNumber("Drive Right", rightY);

    SetMotorL(leftY);
    SetMotorR(rightY);
}

void DriveTrainSubsystemBase::MoveArcade(double X, double Y)
{
    double leftY = X + Y;
    double rightY = X - Y;
    MoveTank(leftY, rightY);
}

void DriveTrainSubsystemBase::Stop()
{
    MoveTank(0.0, 0.0);
}

void DriveTrainSubsystemBase::Forward(double speed)
{
    MoveTank(1.0, 1.0);
}
<<<<<<< HEAD
void DriveTrainSubsystemBase::ForwardInSeconds(double time)
{
    m_timeVariable.Reset();
    m_timeVariable.Start();
   double startTime = m_timeVariable.Get();
   double currentTime = m_timeVariable.Get();
   if(time < 0) {Stop();}
   Forward();
   while(currentTime-startTime < time)
   {
       currentTime = m_timeVariable.Get();
   }
   m_timeVariable.Stop();
   Stop();
}
void DriveTrainSubsystemBase::TurnRight(double speed)
{

}
void DriveTrainSubsystemBase::TurnLeft(double speed)
{
    
}
void DriveTrainSubsystemBase::TurnInDegress(double relativeAngle)
{
    double startAngle = m_gyro.GetAngle();
    double currentAngle = m_gyro.GetAngle();
    if(relativeAngle > 0)
    {
        while(currentAngle - startAngle < relativeAngle)
        {
            TurnRight();
        }
    }
    if(relativeAngle < 0)
    {
        while(currentAngle - startAngle > relativeAngle)
        {
            TurnLeft();
        }
    }
}
void DriveTrainSubsystemBase::Init()
{
    m_gyro.Calibrate();
    m_gyro.Reset();
=======

void DriveTrainSubsystemBase::GoDistanceInch(double speed, double inch)
{
    MoveTank(speed, speed);
    double currentDistance = GetLeftEncoderInch();
    while(currentDistance < inch)
    {
        currentDistance = GetLeftEncoderInch();
    }
    Stop();
>>>>>>> 2a1bb3b6c66214e1f29e0f12e0a9072ff059e274
}
