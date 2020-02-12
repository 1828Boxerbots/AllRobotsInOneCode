/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/DPDTSwitchDriver.h"
#include "Util.h"
#include <frc/DriverStation.h>

DPDTSwitchDriver::DPDTSwitchDriver(int CHANNEL_A, int CHANNEL_B) 
{
    m_pChannelA = new frc::DigitalInput(CHANNEL_A);
    m_pChannelB = new frc::DigitalInput(CHANNEL_B);
}


int DPDTSwitchDriver::Get()
{
    Util::DelayInSeconds(3);
    if(m_pChannelA->Get() && !(m_pChannelB->Get()))
    {
        return 1;
    }
    else if (m_pChannelA->Get() && m_pChannelB->Get())
    {
        return 2;
    }
    else if (!(m_pChannelA->Get()) && m_pChannelB->Get())
    {
        return 3;
    }
    else if (!(m_pChannelA->Get()) && !(m_pChannelB->Get()))
    {
        frc::DriverStation::ReportError("Autonomous Switch unresponsive");
        return -1;
    }
}