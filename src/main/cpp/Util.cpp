/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Util.h"
#include <frc/Timer.h>
#include <frc/smartdashboard/SmartDashboard.h>

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

bool Util::CompareDouble(double value, double requiredValue, double tolerance)
{
    if((value > requiredValue - tolerance) && (value < requiredValue + tolerance))
    {
        return true;
    }
    else
    {
        return false;
    }
    //Another way to write this is
    //return (value > requiredValue - tolerance) && (value < requiredValue + tolerance);
}


double Util::AbsMax(double input, double maxValue) 
{
    // Just in case the max is negative
    maxValue = std::abs(maxValue);

    if (input > 0)
    {
        return std::min(input, maxValue);
    }
    else
    {
        return std::max(input, -maxValue);
    }
}
	

double Util::AbsMin(double input, double minValue) 
{

    // Just in case the max is negative
    minValue = std::abs(minValue);

    if (input > 0)
        return std::max(input, minValue);
    else
        return std::min(input, -minValue);
}


void Util::Log(std::string title, double value, std::string subsytemName)
{
    frc::SmartDashboard::PutNumber(subsytemName + " " + title, value);
}


void Util::Log(std::string title, int value, std::string subsytemName)
{
    frc::SmartDashboard::PutNumber(subsytemName + " " + title, value);
}


void Util::Log(std::string title, bool value, std::string subsytemName)
{
    frc::SmartDashboard::PutBoolean(subsytemName + " " + title, value);
}


void Util::Log(std::string title, std::string value, std::string subsytemName)
{
    frc::SmartDashboard::PutString(subsytemName + " " + title, value);
}


/* 
*  Specialized error reporting (Adam's test)
*  
*  Allows you to report to the driver station with a custom error code.
*/
void Util::SendErrorAndCode(const wpi::Twine& error, int32_t code)
{
    wpi::SmallString<128> temp;
    HAL_SendError(1, code, 0, error.toNullTerminatedStringRef(temp).data(), "", "", 1);
}


/* 
*  Overload of the other error function (Adam's test)
*  
*  Allows you to report to the driver station with a custom error code, and location.
*/
void Util::SendErrorAndCode(const wpi::Twine& error, int32_t code, const char *location)
{
    wpi::SmallString<128> temp;
    HAL_SendError(1, code, 0, error.toNullTerminatedStringRef(temp).data(), location, "", 1);
}
