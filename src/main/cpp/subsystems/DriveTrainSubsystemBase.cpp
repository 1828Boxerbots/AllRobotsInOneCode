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
    leftY = Util::Limit(leftY, -.5, .5);
    rightY = Util::Limit(rightY, -.5, .5);
    if(leftY > 0.1 || leftY < -0.1)
    {
        GetLeftEncoderInch();
    }
    if(rightY > 0.1 || rightY < -0.1)
    {
        GetRightEncoderInch();    
    }
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

void DriveTrainSubsystemBase::LogEncoder()
{
    frc::SmartDashboard::PutNumber("Right Encoder Distance", m_rightEncoderSim);
    frc::SmartDashboard::PutNumber("Left Encoder Distance", m_leftEncoderSim);
}

void DriveTrainSubsystemBase::Stop()
{
    MoveTank(0.0, 0.0);
}

void DriveTrainSubsystemBase::Forward(double speed)
{
    MoveTank(1.0, 1.0);
}

void DriveTrainSubsystemBase::ForwardInInch(double speed, double inch)
{
    MoveTank(speed, speed);
    double currentDistance = GetLeftEncoderInch();
    while(currentDistance < inch)
    {
        currentDistance = GetLeftEncoderInch();
        Util::DelayInSeconds(1.0);
    }
    if(currentDistance > inch)
    {
        ResetEncoder();
    }
    Stop();
    void DriveTrainSubsystemBase::ForwardInSeconds(double goalTime)
    {
        m_time.Reset();
        m_time.Start();
        Util::TimeInSeconds(goalTime);
        Stop();
    }
    void DriveTrainSubsystemBase::TurnRight()
    {
        MoveTank(1.0,-1.0);
    }
    void DriveTrainSubsystemBase::TurnLeft()
    {
        MoveTank(-1.0,1.0);
    }
    void DriveTrainSubsystemBase::TurnInDegrees(double relativeAngle)
    {
        double startAngle = m_gyro.GetAngle();
        double currentAngle = m_gyro.GetAngle();
        if(relativeAngle > 0)
        {
            TurnRight();
            while (currentAngle-startAngle < relativeAngle)
            {
                currentAngle = m_gyro.GetAngle();
            }
        }
        if(relativeAngle < 0)
        {
            TurnLeft();
            while (currentAngle-startAngle > relativeAngle)
            {
                currentAngle = m_gyro.GetAngle();
            }
        }
    }
    void DriveTrainSubsystemBase::Init()
    {
        m_gyro.Reset();
        m_gyro.Calibrate();
    }
}
