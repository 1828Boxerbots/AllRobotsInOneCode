/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/SpinSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>

SpinSubsystemRobot2020::SpinSubsystemRobot2020() {}

void SpinSubsystemRobot2020::MultiplexerSelect(int position)
{
    //Put Multiplexer Stuff here
}

void SpinSubsystemRobot2020::Init()
{
    #ifndef NOHW
    m_spinEncoder.Reset();
    #endif
}

void SpinSubsystemRobot2020::SetSpinMotor (double speed)
{
    #ifndef NOHW
    m_spinMotor.Set(speed * m_scale);
    #endif
}

void SpinSubsystemRobot2020::SpinWithColor(double speed, int wantedRotation)
{    
    //Gets the starting color of the wheel
    FMSColors startColor = m_colorSensor.GetColor();
    

    //Checks if it picked up a valid color
    if(startColor == INVALID)
    {
        return;
    }

    //Start Spinning if color is vaild
    SetSpinMotor(speed);

    //Declares the currentColor Variable
    FMSColors currentColor;

    for(int halfRotations = 0; halfRotations < wantedRotation; halfRotations++)
    {
        //Do-While loop till we are out of the starting color
        do
        {
        currentColor = m_colorSensor.GetColor();
        }
        while(currentColor == startColor);

        /**Starts after we leave the start color
        * Do-While loop till we see the start color again
        */
        do
        {
        currentColor = m_colorSensor.GetColor();
        }
        while(currentColor != startColor);
    }

    //Stops the Spiner after finished spinning
    Stop();
}

double SpinSubsystemRobot2020::GetEncoderTicks()
{
    #ifndef NOHW
    double encoderValue = m_spinEncoder.GetRaw();
    frc::SmartDashboard::PutNumber("Spin Encoder Raw", encoderValue);
    return encoderValue;
    #else
    return 0.0;
    #endif
}

SpinSubsystemBase::FMSColors SpinSubsystemRobot2020::ReadColorSensor()
{
    #ifndef NOHW
    return m_colorSensor.GetColor();
    #else
    return INVALID;
    #endif
}

double SpinSubsystemRobot2020::GetTicksPerRevolution()
{
    return 360;
}
