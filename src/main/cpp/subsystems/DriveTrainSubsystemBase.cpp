/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DriveTrainSubsystemBase.h"
#include <math.h>

DriveTrainSubsystemBase::DriveTrainSubsystemBase() {}

// This method will be called once per scheduler run
void DriveTrainSubsystemBase::Periodic() {}

void DriveTrainSubsystemBase::MoveTank(double leftY, double rightY)
{
    GyroGetAngle();
    GetRightEncoderInch();
    GetLeftEncoderInch();
    leftY = Util::Limit(leftY);
    rightY = Util::Limit(rightY);
    if (leftY > 0.1 || leftY < -0.1)
    {
        GetLeftEncoderInch();
    }
    if (rightY > 0.1 || rightY < -0.1)
    {
        GetRightEncoderInch();
    }
    frc::SmartDashboard::PutNumber("Drive Left", leftY);
    frc::SmartDashboard::PutNumber("Drive Right", rightY);

    //Lidar returns 0 if object is out of distance, minimum distance is to prevent an infinite loop
    //implemented solely for lidar, will change later for distance sensors
    if (GetLidarDetectionDistance() > MINIMUMDISTANCE && m_hasAntiCollision == true)
    {
        //If turning, since sensor is generally on front, keep turning
        if (leftY < -0.1 || rightY < -0.1)
        {
            SetMotorL(leftY);
            SetMotorR(rightY);
        }
        //Again, if turning,but object is within collision range, still turn, but if not turning, then set motors to stop
        else if (GetLidarDetectionDistance() < m_lidarCollisionDistance)
        {
            if (leftY < -0.1 || rightY < -0.1)
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
        // If object is not within collision range, just continue with driving
        else
        {
            SetMotorL(leftY);
            SetMotorR(rightY);
        }
    }
    //If no object is within range of lidar's distance or anti collision isn't active, then just continue with driving
    else
    {
        SetMotorL(leftY);
        SetMotorR(rightY);
    }
    //This is for distance sensor implementation, if distance sensor doesn't pick up anything, then go on with code
    if (IsDistanceLeftActive() == true && m_hasAntiCollision == true)
    {
        //Distance less than collision range
        if (GetDistanceSensorDetectionDistanceLeft() < m_distanceCollisionDistanceLeft)
        {
            //If turning right,forward, or reverse, continue moving
            if ((leftY > 0.1 && rightY < -0.1) || (leftY > 0.1 && rightY > 0.1) || (leftY < -0.1 && rightY < -0.1))
            {
                SetMotorL(leftY);
                SetMotorR(rightY);
            }
            //If not turning, set motors to 0
            else
            {
                SetMotorL(0.0);
                SetMotorR(0.0);
            }
        }
    }
    if (IsDistanceRightActive() == true && m_hasAntiCollision == true)
    {
        //Distance less than collision range
        if (GetDistanceSensorDetectionDistanceRight() < m_distanceCollisionDistanceRight)
        {
            //If turning left,moving forward, or reversing, continue moving
            if (((leftY < -0.1) && (rightY > 0.1)) || ((leftY > 0.1) && (rightY > 0.1)) || ((leftY < -0.1) && (rightY < -0.1)))
            {
                SetMotorL(leftY);
                SetMotorR(rightY);
            }
            //If not going reverse, set motors to 0
            else
            {
                SetMotorL(0.0);
                SetMotorR(0.0);
            }
        }
    }
}

void DriveTrainSubsystemBase::MoveArcade(double X, double Y)
{
    double m_scale = 1.28;
    double leftY = X + Y;
    double rightY = X - Y;
    MoveTank(leftY, rightY * m_scale);
}

void DriveTrainSubsystemBase::ArcadeVision(double x, double y, OldCameraVision::VisionColors color)
{
    double m_scale = 1.28;
    double leftY = x + y;
    double rightY = x - y;

    double deadZoneLocation = 0.75;
    double deadZoneRange = 30;

    SetLookingColorV(color);

    SetLookingColorV(OldCameraVision::VisionColors::GREEN_CONE);

    double turn =  WhereToTurn(deadZoneLocation, deadZoneRange);

    
    while(turn > -2.9)
    {
        MoveTank(leftY, rightY * m_scale);
        turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
    }
    Stop();
}
void DriveTrainSubsystemBase::TimedArcade(double x, double y, double time)
{
     m_autoTimer.Stop();
    m_autoTimer.Reset();
    m_autoTimer.Start();
    double startTime = m_autoTimer.Get();
    do
    {
        MoveArcade(x, y);
    } while (time > m_autoTimer.Get()-startTime);
    Stop();
}

void DriveTrainSubsystemBase::TurnRight(double speed)
{
    if(speed < 0)
    {
        speed = -speed;
    }
    MoveTank(speed, -speed*1.28);
}

void DriveTrainSubsystemBase::TurnLeft(double speed)
{
    if(speed < 0)
    {
        speed = -speed;
    }
    MoveTank(-speed, speed*1.28);
}

void DriveTrainSubsystemBase::LogEncoder()
{
    frc::SmartDashboard::PutNumber("Right Encoder Distance", m_rightEncoderSim);
    frc::SmartDashboard::PutNumber("Left Encoder Distance", m_leftEncoderSim);
}

//Stops robot
void DriveTrainSubsystemBase::Stop()
{
    MoveTank(0.0, 0.0);
}

//Moves robot forward
void DriveTrainSubsystemBase::Forward(double speed)
{
    MoveTank(speed , speed * 1.289);
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

    //Nothing left but to for it...
    MoveArcade(lin, rotation);

    //Determine if the robot made it to the target
    //and then wait a bit so that it can be correct any overshoot.
    if (error > 2 || errorRotation > 3.0)
    {
        m_autoTimer.Reset();
    }
    else if (m_autoTimer.Get() > 0.75)
    {
        return true;
    }

    //Keep trying...
    return false;
}

void DriveTrainSubsystemBase::FixRotation(double wantedAngle, double speed)
{
    double currentAngle = GyroGetAngle();
    while (currentAngle != wantedAngle)
    {
        currentAngle = GyroGetAngle();
        if (currentAngle > wantedAngle)
        {
            TurnRight(speed);
        }
        else
        {
            TurnLeft(speed);
        }
    }
    Stop();
}
//Pretty buggy, two versions of it: PIDS control and regular control. PIDS makes sure the robot is straight, regular just moves forward
void DriveTrainSubsystemBase::ForwardInInch(double inch, double angle, double speed)
{
    //This is Regular
    double startDistance = GetRightEncoderInch();
    double currentDistance = GetRightEncoderInch();
    while (currentDistance - startDistance < inch)
    {
        Forward(speed);
        currentDistance = GetRightEncoderInch();
        frc::SmartDashboard::PutNumber("LeftEncoderInches", GetRightEncoderInch());
        //Util::DelayInSeconds(1.0);
    }
    if (currentDistance > inch)
    {
        ResetEncoder();
    }
    Stop();

    //This is PIDS
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

//Used to turn the robot a certain amount of degrees(RelativeAngle is user's wanted angle)
// void DriveTrainSubsystemBase::TurnInDegrees(double relativeAngle, double speed)
// {
//     //troubleshooting values, use these for testing what makes the robot go to the relative angle
//     frc::SmartDashboard::PutNumber("Current Angle", relativeAngle);
//     frc::SmartDashboard::PutBoolean("In Place", true);
//     double startAngle = IMUGetAngle();
//     double currentAngle = IMUGetAngle();
//     //logic used to turn the robot left or right and keeping it turned
//     if (relativeAngle > 0)
//     {
//         TurnRight(speed);
//         while (currentAngle - startAngle < relativeAngle)
//         {
//             currentAngle = IMUGetAngle();
//         }
//     }
//     if (relativeAngle < 0)
//     {
//         TurnLeft(speed);
//         while (currentAngle - startAngle > relativeAngle)
//         {
//             currentAngle = IMUGetAngle();
//         }
//     }
//     Stop();
// }

//Used to turn the robot a certain amount of degrees(RelativeAngle is user's wanted angle)
void DriveTrainSubsystemBase::TurnInDegrees(double relativeAngle, double speed)
{
    //This is Regular
    double startDistance = GetRightEncoderInch();
    double currentDistanceRight = GetLeftEncoderInch();
    double currentDistanceLeft = GetRightEncoderInch();
    double inch = Util::Abs(relativeAngle)*(Util::PI/180)*10.5;
    while (currentDistanceRight - startDistance < inch || currentDistanceLeft - startDistance < inch )
    {
        if(relativeAngle < 0)
        {
            TurnLeft(speed);
        }
        else
        {
            TurnRight(speed);
        }
        
        currentDistanceLeft = GetRightEncoderInch();
        currentDistanceRight = GetLeftEncoderInch();
        frc::SmartDashboard::PutNumber("LeftEncoderInches", GetRightEncoderInch());
        //Util::DelayInSeconds(1.0);
    }
    if (currentDistanceLeft > inch)
    {
        ResetEncoder();
    }
    if (currentDistanceRight > inch)
    {
        ResetEncoder();
    }
    Stop();
}

void DriveTrainSubsystemBase::Init()
{
    GyroInit();
    Init();
}

//function used to turn the robot in seconds; Use at your own risk
void DriveTrainSubsystemBase::ForwardInSeconds(double goalTime, double speed)
{
    m_autoTimer.Stop();
    m_autoTimer.Reset();
    m_autoTimer.Start();
    double startTime = m_autoTimer.Get();
    do
    {
        Forward(speed);
    } while (goalTime > m_autoTimer.Get()-startTime);
    Stop();
}

void DriveTrainSubsystemBase::AlignWithVision(double deadZoneLocation, int deadZoneRange, bool defaultTurnRight)
{
    Util::Log("Direction", "Null");
    double turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
    while(turn != 0.0)
    {
        turn = WhereToTurn(deadZoneLocation, deadZoneRange);
        if(turn < -1.0)
        {
                Util::Log("Direction", "No See");
            //Turn right/left if object is not seen
            if(defaultTurnRight == true)
            {
                TurnRight(0.25);
            }
            else if(defaultTurnRight == false)
            {
                TurnLeft(0.25);
            }
        }
        else if (turn < 0.0)
        {
            Util::Log("Direction", "TurnLeft");
            //Turn left if object is on the left
            TurnLeft(0.2);
        }
        else if(turn > 0.0)
        {
            Util::Log("Direction", "TurnRight");
            //Turn right if object is on the right
            TurnRight(0.2);
        }
    }
    Util::Log("Direction", "Center");
    Forward(0.3);
    while(turn > -2.9)
    {
        //Continue Forwards until object is not see-able
        turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
        Util::Log("TurnCam", turn);
    }
     Util::Log("Direction", "Stop");
     Stop();
}
void DriveTrainSubsystemBase::MoveWithVision(double deadZoneLocation, int deadZoneRange, int moveSpeed, bool defaultTurnRight)
{
    double turn =  WhereToTurn(deadZoneLocation, deadZoneRange);
    while(turn != 0.0)
    {
        turn = WhereToTurn(deadZoneLocation, deadZoneRange);
        if(turn < -1.0)
        {
            //Turn right/left if object is not seen
            if(defaultTurnRight == true)
            {
                TurnRight(0.3);
            }
            else if(defaultTurnRight == false)
            {
                TurnLeft(0.3);
            }
        }
        else if (turn < 0.0)
        {
            //Move left if object is on the left
            MoveArcade(moveSpeed, -0.2);
        }
        else if(turn > 0.0)
        {
            //Turn right if object is on the right
            MoveArcade(moveSpeed, 0.2);
        }
        else
        {
            //Object is in the center
            MoveArcade(moveSpeed, 0.0);
        }
    }
}