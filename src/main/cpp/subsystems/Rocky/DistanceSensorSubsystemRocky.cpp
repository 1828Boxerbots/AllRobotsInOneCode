/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Rocky/DistanceSensorSubsystemRocky.h"
#include <frc/smartdashboard/SmartDashboard.h>

DistanceSensorSubsystemRocky::DistanceSensorSubsystemRocky() {}

// This method will be called once per scheduler run
void DistanceSensorSubsystemRocky::Periodic() {}

double DistanceSensorSubsystemRocky::GetDistanceForward()
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

    frc::SmartDashboard::PutNumber("Lidar Distance", (int)centimeters);

    return (int)centimeters;
}

void DistanceSensorSubsystemRocky::Init()
{
    m_device.Write(ACQ_COMMAND, ACQ_CONFIG_REG);
}



double DistanceSensorSubsystemRocky::GetDistanceInInch()
{
    return CMtoIN*GetDistanceForward();
}
void DistanceSensorSubsystemRocky::ForwardDetectionSensor(double distance)
{
    double startDistance = GetDistanceInInch();
    double currentDistance = GetDistanceInInch();
    if(distance > 0)
    {
        while(currentDistance - startDistance < distance) {currentDistance = GetDistanceInInch();}
    }
}