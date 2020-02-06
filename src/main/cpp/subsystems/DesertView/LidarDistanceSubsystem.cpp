/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DesertView/LidarDistanceSubsystem.h"

LidarDistanceSubsystem::LidarDistanceSubsystem() {}

// This method will be called once per scheduler run
void LidarDistanceSubsystem::Periodic() {}

void LidarDistanceSubsystem::Init()
{
    #ifndef NOHW
    m_device.Write(ACQ_COMMAND, ACQ_CONFIG_REG);
    #endif
}

double LidarDistanceSubsystem::GetDistanceInCM()
{
    Init();

    uint16_t centimeters = m_distance++;
    #ifndef NOHW
    uint8_t val;
    while(m_device.Read(STATUS, 1, &val) == false) 
    {
        if ((val & 0x1) == 0)
        {
            break;
        }
    }

    uint8_t high;
    uint8_t low;
    m_device.Read(FULL_DELAY_HIGH, 1, &high);
    m_device.Read(FULL_DELAY_LOW , 1, &low );
    centimeters = (high << 8) | low;
    m_distance = centimeters;
    #endif
    // Use this if you want to see distance on Smashboard
    frc::SmartDashboard::PutNumber("Lidar Distance", m_distance);

    return m_distance;
}

double LidarDistanceSubsystem::GetDistanceInInch()
{
    int distance = GetDistanceInCM();
    int newDistance = distance * CMtoIN;

    // Use this if you want to see distance on Smashboard
    //SmartDashboard::PutNumber("Lidar Distance", (int)newDistance);

    return (double)newDistance;
}
