/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/ColorSensorDriver.h"
#include <frc/smartdashboard/SmartDashboard.h>

#include <String>

ColorSensorDriver::ColorSensorDriver(frc::I2C::Port port) 
{
    m_pDevice = new rev::ColorSensorV3(port);
}


uint32_t ColorSensorDriver::GetProximity()
{
    return m_pDevice->GetProximity();
}


SpinSubsystemBase::FMSColors ColorSensorDriver::GetColor()
{
    frc::Color detectedColor = m_pDevice->GetColor();

    std::string message = "";

    SpinSubsystemBase::FMSColors output;

    if (IsRed(detectedColor.red, detectedColor.green, detectedColor.blue))
    {
        output = SpinSubsystemBase::FMSColors::RED;
        message = "Red";
    }
    else
    {
      if (IsGreen(detectedColor.red, detectedColor.green, detectedColor.blue))
      {
        output = SpinSubsystemBase::FMSColors::GREEN;
        message = "Green";
      }
      else
      {
        if (IsBlue(detectedColor.red, detectedColor.green, detectedColor.blue))
        {
          output = SpinSubsystemBase::FMSColors::BLUE;
          message = "Blue";
        }
        else
        {
          if (IsYellow(detectedColor.red, detectedColor.green, detectedColor.blue))
          {
            output = SpinSubsystemBase::FMSColors::YELLOW;
            message = "Yellow";
          }
          else
          {
            output = SpinSubsystemBase::FMSColors::INVALID;
            message = "Invalid";
          }
        }
      }
    }

    frc::SmartDashboard::PutString("Color sensor driver color", message);
    return output;
}


std::string ColorSensorDriver::GetColorString()
{
    std::string retval;
    SpinSubsystemBase::FMSColors temp = GetColor();
    switch (temp)
    {
        case (SpinSubsystemBase::FMSColors::RED):
            retval = (std::string)"Red";
            break;
        case (SpinSubsystemBase::FMSColors::YELLOW):
            retval = (std::string)"Yellow";
            break;
        case (SpinSubsystemBase::FMSColors::BLUE):
            retval = (std::string)"Blue";
            break;
        case (SpinSubsystemBase::FMSColors::GREEN):
            retval = (std::string)"Green";
            break;
        case (SpinSubsystemBase::FMSColors::INVALID):
            retval = (std::string)"Invalid";
            break;
        default:
            retval = (std::string)"ERROR";
            break;
    }
    return retval;
}


bool ColorSensorDriver::IsRed(double R, double G, double B) 
{
    if( R >= RED_LOW_R && R <= RED_HIGH_R)
    {
        if( G >= RED_LOW_G && G <= RED_HIGH_G)
        {
            if (B >= RED_LOW_B && B <= RED_HIGH_B)
            {
            return true; 
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool ColorSensorDriver::IsGreen(double R, double G, double B) 
{
    if( R >= GREEN_LOW_R && R <= GREEN_HIGH_R)
    {
        if( G >= GREEN_LOW_G && G <= GREEN_HIGH_G)
        {
        if ( B >= GREEN_LOW_B && B <= GREEN_HIGH_B)
            {
                return true; 
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool ColorSensorDriver::IsBlue(double R, double G, double B) 
{
    if( R >= BLUE_LOW_R && R <= BLUE_HIGH_R)
    {
        if( G >= BLUE_LOW_G && G <= BLUE_HIGH_G)
        {
            if (B >= BLUE_LOW_B && B <= BLUE_HIGH_B)
            {
            return true; 
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}


bool ColorSensorDriver::IsYellow(double R, double G, double B) 
{
    if( R >= YELLOW_LOW_R && R <= YELLOW_HIGH_R)
    {
        if( G >= YELLOW_LOW_G && G <= YELLOW_HIGH_G)
        {
            if (B >= YELLOW_LOW_B && B <= YELLOW_HIGH_B)
            {
            return true; 
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool ColorSensorDriver::StatusIsFatal()
{
    return m_pDevice->StatusIsFatal();
}


void ColorSensorDriver::DetectOverlap()
{
    frc::Color detectedColor = m_pDevice->GetColor();
    
    const char* fileLoc = "ColorSensorDriver.cpp";

    bool isRed = IsRed(detectedColor.red, detectedColor.green, detectedColor.blue);
    bool isGreen = IsGreen(detectedColor.red, detectedColor.green, detectedColor.blue);
    bool isBlue = IsBlue(detectedColor.red, detectedColor.green, detectedColor.blue);
    bool isYellow = IsYellow(detectedColor.red, detectedColor.green, detectedColor.blue);

    if(isRed && isYellow)
    {
        Util::SendErrorAndCode("Red overlaps with Yellow", 101, fileLoc);
    }
    if(isRed && isGreen)
    {
        Util::SendErrorAndCode("Red overlaps with Green", 102, fileLoc);
    }
    if(isRed && isBlue)
    {
        Util::SendErrorAndCode("Red overlaps with Blue", 103, fileLoc);
    }
    if(isYellow && isGreen)
    {
        Util::SendErrorAndCode("Yellow overlaps with Green", 104, fileLoc);
    }
    if(isYellow && isBlue)
    {
        Util::SendErrorAndCode("Yellow overlaps with Blue", 105, fileLoc);
    }
    if(isBlue && isGreen)
    {
        Util::SendErrorAndCode("Blue overlaps with Green", 106, fileLoc);
    }
}

// development in progress 3/5/2020
