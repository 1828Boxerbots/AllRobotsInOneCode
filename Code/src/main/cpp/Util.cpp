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

 void Util::WaitInSeconds(double seconds)
 {
    frc::Timer time;
    double startTime = time.Get();
    double endTime = startTime + seconds;
    double currentTime = time.Get();
    while(endTime > currentTime)
    {
        currentTime = time.Get();
    }
 }
