/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/SpinSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include "../../../include/RobotContainer/RobotContainerRobot2020.h"
#include "../../../include/subsystems/Robot2020/ArmSubsystemRobot2020.h"
#include "../../../include/subsystems/ArmSubsystemBase.h"

SpinSubsystemRobot2020::SpinSubsystemRobot2020(){}


void SpinSubsystemRobot2020::Init()
{
 
}

void SpinSubsystemRobot2020::Periodic()
{
    #ifndef NOHW
    m_colorSensor.ReturnAllColors();
    Util::Log("Count Color Read", m_beatColorRead++, "spinRobot2020");
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

    #ifndef NOHW
    //Gets the starting color of the wheel
    FMSColors startColor = m_colorSensor.GetColor();
    

    //Checks if it picked up a valid color
    if(startColor == INVALID)
    {
        return;
    }

    //Start Spinning if color is valid
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

    //Stops the Spinner after finished spinning
    Stop();
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


std::string SpinSubsystemRobot2020::GetColor()
{
    #ifndef NOHW
    m_colorSensor.ReturnAllColors();
    return m_colorSensor.GetColorString();
    #else
    return NULL;
    #endif
}

void SpinSubsystemRobot2020::SpinToColor()
{

    FMSColors wantedColor = RobotContainerRobot2020::givenColor;
    FMSColors realColor;

    if(ReadColorSensor() == INVALID)
    {
        return;
    }

    do
    {
        FMSColors currentColor = ReadColorSensor();

        currentColor = MapColors(currentColor);
        realColor = currentColor;

        SetSpinMotor(1.0);
    } while (realColor != wantedColor);

    Stop();
}

SpinSubsystemBase::FMSColors SpinSubsystemRobot2020::GetFMSColor()
{
    //tbt
    return FMSColors::RED;
}

SpinSubsystemBase::FMSColors SpinSubsystemRobot2020::ConvertColor(FMSColors color)
{
    switch (color)
    {
        case RED:
            return BLUE;
            break;

        case BLUE:
            return RED;
            break;

        case YELLOW:
            return GREEN;
            break;

        case GREEN:
            return YELLOW;
            break;

        default:
            return INVALID;
            break;
    }
}

int SpinSubsystemRobot2020::CalcDir()
{
    /*
    0 = dont move
    1 = Clock-wise TBD
    -1 = Counter Clock-wise TBD
    */

    FMSColors wantedColor = GetFMSColor();
    FMSColors currentColor = ReadColorSensor();

    int direction;

    switch (wantedColor)
    {
        case RED:
            if(currentColor == YELLOW || currentColor == BLUE)
            {
                direction = 1;
            }
            else if(currentColor == GREEN)
            {
                direction = -1;
            }
            else if(currentColor == RED)
            {
                direction = 0;
            }
            break;

        case GREEN:
            if(currentColor == YELLOW || currentColor == BLUE)
            {
                direction = 1;
            }
            else if(currentColor == RED)
            {
                direction = -1;
            }
            else if(currentColor == GREEN)
            {
                direction = 0;
            }
            break;

        case YELLOW:
            if(currentColor == GREEN || currentColor == BLUE)
            {
                direction = 1;
            }
            else if(currentColor == RED)
            {
                direction = -1;
            }
            else if(currentColor == YELLOW)
            {
                direction = 0;
            }
            break;

        case BLUE:
            if(currentColor == GREEN || currentColor == RED)
            {
                direction = 1;
            }
            else if(currentColor == YELLOW)
            {
                direction = -1;
            }
            else if(currentColor == BLUE)
            {
                direction = 0;
            }
            break;
    
    default:
        direction = 0;
        break;
    }

    return direction;
}
