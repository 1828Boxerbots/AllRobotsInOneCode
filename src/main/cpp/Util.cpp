/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Util.h"
#include <frc/Timer.h>

double Util::Limit(double value, double lowerLimit, double higherLimit)
{
    if(lowerLimit > higherLimit)
    {
        return value;
    }
    if(value > higherLimit)
    {
        value = higherLimit;
    } 
    if(value < lowerLimit)
    {
        value = lowerLimit;
    }   
    return value;
}

void Util::DelayInSeconds(double seconds)
{
    frc::Timer timer;
    //starts timer and gets start time and beginning current time
    timer.Start();
    double startTime = timer.Get();
    double currentTime = timer.Get();
    //Keep looping until end time is reached
    while(currentTime - startTime < seconds)
    {
        //Gets current time and sends it to the smartdashboard for checking
        currentTime = timer.Get();
    }
    //Stops and resets timer used for driving forward
    timer.Stop();
    timer.Reset();
}

