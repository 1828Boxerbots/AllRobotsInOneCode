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
    GyroGetAngle();
    leftY = Util::Limit(leftY);
    rightY = Util::Limit(rightY);
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

    if (GetDetectionDistance() > 5.0 && m_hasAntiCollision == true )
    {
        if(leftY < -0.1 || rightY < -0.1)
        {
            SetMotorL(leftY);
            SetMotorR(rightY);
        }
        else if (GetDetectionDistance() < m_collisionBuffer)
        {
            if(leftY < -0.1 || rightY < -0.1)
            {
                SetMotorL(leftY);
                SetMotorR(rightY);
            }
            else
            {
                SetMotorL(0.0);
                SetMotorR(0.0);
            }
                
        }   
        else
        {
            SetMotorL(leftY);
            SetMotorR(rightY);
        }
    }
    else
    {
        SetMotorL(leftY);
        SetMotorR(rightY);
    }
    
}

void DriveTrainSubsystemBase::MoveArcade(double X, double Y)
{
    double leftY = X + Y;
    double rightY = X - Y;
    MoveTank(leftY, rightY);
}


void DriveTrainSubsystemBase::TurnRight(double speed)
{
    MoveTank(-speed, speed);
}


void DriveTrainSubsystemBase::TurnLeft(double speed)
{
    MoveTank(speed, -speed);
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

bool DriveTrainSubsystemBase::MoveAlignPID(double targetDistance, double heading, double maxSpeed)
{
    //
    //Distance
    //

    // Get Encoder values [Inches]
    double leftEncoder = GetLeftEncoderInch();
    double rightEncoder = GetRightEncoderInch();

    // If an encoder fails, we assume that it stops generating pulses
    // so use the larger of the two (absolute distance)
    double encoderDistance;
    if (std::abs(leftEncoder) > std::abs(rightEncoder))
    {
        encoderDistance = leftEncoder;
    } 
    else
    {
        encoderDistance = rightEncoder;
    }

    // Get Control Loop Period
    double loopTime = LOOPTIME;
    
    double error = targetDistance - encoderDistance;
    
    // Linear-Proportional control
    
    // Linear-Integral control
    if (error < m_deadZone) 
    {
        m_sumError += error / loopTime;
    } 
    else
    {
        m_sumError = 0;
    }

    // Linear-Derivative control
    double dError = (error - m_preError) / loopTime;

    double lin = (m_kP * error) + (m_kI * m_sumError) + (m_kD * dError);

    m_preError = error;

    // Ramp up to speed to reduce wheel slippage
    double max_ramp_up = 0.075;
    if (lin > m_preLin + max_ramp_up)
    {
        lin = m_preLin + max_ramp_up;
    }
    m_preLin = lin;

    // Limit max speed
    lin = Util::AbsMax(lin, maxSpeed);

    //
    // Rotation
    //

    m_kP_rot = maxSpeed / m_slowAngle; //Start slowing down at X degree
    double errorRotation = heading - GyroGetAngle();
    double rotation = errorRotation * m_kP_rot;

    //Max Rotation Speed
    rotation = Util::AbsMax(rotation, maxSpeed);

    //Nothing left but to fo it...
    MoveArcade(lin, rotation);

    //Determine if the robot made it to the target
    //and then wait a bit so that it can be correct any overshoot.
    if(error > 2 || errorRotation > 3.0)
    {
        m_autoTimer.Reset();
    }
    else if(m_autoTimer.Get() > 0.75)
    {
        return true;
    }

    //Keep trying...
    return false;
}

void DriveTrainSubsystemBase::ForwardInInch(double inch, double angle, double speed)
{
    double currentDistance = GetLeftEncoderInch();
    while(currentDistance < inch)
    {
        MoveTank(speed, speed);
        currentDistance = GetLeftEncoderInch();
        //Util::DelayInSeconds(1.0);
    }
    if(currentDistance > inch)
    {
        ResetEncoder();
    }
    Stop();
    
/*
    //Creates and Starts Timer
    frc::Timer timer;
    timer.Reset();
    timer.Start();

    //Checks to see if Robot has made it to destination
    while(MoveAlignPID(inch, angle, speed) != true)
    {
        //Checks what time it is
        frc::SmartDashboard::PutNumber("MoveAlignPID Timer", timer.Get());

        if(m_isColliding == true)
        {
            break;
        }
    }

    //Stops Timer and Motors
    timer.Stop();
    Stop();
    */
}


void DriveTrainSubsystemBase::TurnInDegrees(double relativeAngle)
{
    frc::SmartDashboard::PutNumber("Current Angle", relativeAngle);
    frc::SmartDashboard::PutBoolean("In Place", true);
    double startAngle = GyroGetAngle();
    double currentAngle = GyroGetAngle();
    if(relativeAngle > 0)
    {
        TurnLeft(.75);
        while (currentAngle-startAngle < relativeAngle)
        {
            currentAngle = GyroGetAngle();
        }
    }
    if(relativeAngle < 0)
    {
        TurnRight(.75);
        while (currentAngle-startAngle > relativeAngle)
        {
            currentAngle = GyroGetAngle();
        }
    }
}


void DriveTrainSubsystemBase::Init()
{
    GyroInit();
    Init();
}


void DriveTrainSubsystemBase::ForwardInSeconds(double goalTime)
{
    /*m_time.Reset();
    m_time.Start();
    Util::TimeInSeconds(goalTime);
    Stop();*/
}

