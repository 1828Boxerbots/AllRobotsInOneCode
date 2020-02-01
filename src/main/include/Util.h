/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/Timer.h>

namespace Util
{
    double Limit(double value, double lowerLimit = -1.0, double higherLimit = 1.0);

    void DelayInSeconds(double seconds);
    bool CompareDouble(double value, double requiredValue, double tolerance = 0.001);

    //Other Constants 
    constexpr double PI = 3.141592653589793238462643383279502884197169399375105820974944;
}


