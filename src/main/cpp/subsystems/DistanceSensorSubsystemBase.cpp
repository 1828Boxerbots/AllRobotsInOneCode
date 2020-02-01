/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/DistanceSensorSubsystemBase.h"

DistanceSensorSubsystemBase::DistanceSensorSubsystemBase() {}

// This method will be called once per scheduler run
void DistanceSensorSubsystemBase::Periodic() {}

void DistanceSensorSubsystemBase::Init()
{
    m_device.Write(ACQ_COMMAND, ACQ_CONFIG_REG);
}

int DistanceSensorSubsystemBase::GetDistanceInCM()
{
        Init();

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
    uint16_t centimeters = (high << 8) | low;

    // Use this if you want to see distance on Smashboard
    //SmartDashboard::PutNumber("Lidar Distance", (int)centimeters);

    return (int)centimeters;
}

int DistanceSensorSubsystemBase::GetDistanceInInch()
{
    int distance = GetDistanceInCM();
    int newDistance = distance * CMtoIN;

    // Use this if you want to see distance on Smashboard
    //SmartDashboard::PutNumber("Lidar Distance", (int)newDistance);

    return (int)newDistance;
}
