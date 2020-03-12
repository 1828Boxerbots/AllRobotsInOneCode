/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Robot2020/SpinSubsystemRobot2020.h"
#include <frc/smartdashboard/SmartDashboard.h>

SpinSubsystemRobot2020::SpinSubsystemRobot2020()
{
    m_pMultiplexer = new I2CMultiplexerDriver(I2C_PORT_MULTIPLEXER_ROBOT2020);
    m_pColorSensor = new MuxColorSensorDriver(I2C_PORT_MULTIPLEXER_ROBOT2020, *m_pMultiplexer, U8T_LINE_COLORSENSOR_ROBOT2020);
}

void SpinSubsystemRobot2020::Init()
{
 
}


void SpinSubsystemRobot2020::Periodic()
{
    m_pColorSensor->ReturnAllColors();
    Util::Log("Count Color Read", m_beatColorRead++, "spinRobot2020");
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
    FMSColors startColor = m_pColorSensor->GetColor();
    

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
        currentColor = m_pColorSensor->GetColor();
        }
        while(currentColor == startColor);

        /**Starts after we leave the start color
        * Do-While loop till we see the start color again
        */
        do
        {
        currentColor = m_pColorSensor->GetColor();
        }
        while(currentColor != startColor);
    }

    //Stops the Spinner after finished spinning
    Stop();
}



SpinSubsystemBase::FMSColors SpinSubsystemRobot2020::ReadColorSensor()
{
    #ifndef NOHW
    return m_pColorSensor->GetColor();
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
    m_pColorSensor->ReturnAllColors();
    return m_pColorSensor->GetColorString();
    #else
    return NULL;
    #endif
}
