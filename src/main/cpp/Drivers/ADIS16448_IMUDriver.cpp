/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/ADIS16448_IMUDriver.h"

ADIS16448_IMUDriver::ADIS16448_IMUDriver() 
{
    m_pDevice = new frc::ADIS16448_IMU();
}


void ADIS16448_IMUDriver::IMUGyroInit(bool log)
{
    if(log) {Util::Log("IMU Initialized", true, "IMU Driver");}
    ResetAngles();
    CalibrateIMU();
}


double ADIS16448_IMUDriver::GetTemperature()
{
    return m_pDevice->GetTemperature();
}


double ADIS16448_IMUDriver::GetPressure()
{
    return m_pDevice->GetBarometricPressure();
}


double ADIS16448_IMUDriver::GetAccelX()
{
    return m_pDevice->GetAccelInstantX();
}


double ADIS16448_IMUDriver::GetAccelY()
{
    return m_pDevice->GetAccelInstantY();
}


double ADIS16448_IMUDriver::GetAccelZ()
{
    return m_pDevice->GetAccelInstantZ();
}


double ADIS16448_IMUDriver::GetAngleX()
{
    return m_pDevice->GetGyroAngleX();
}


double ADIS16448_IMUDriver::GetAngleY()
{
    return m_pDevice->GetGyroAngleY();
}


double ADIS16448_IMUDriver::GetAngleZ()
{
    return m_pDevice->GetGyroAngleZ();
}


double ADIS16448_IMUDriver::GetMagX()
{
    return m_pDevice->GetMagInstantX();
}


double ADIS16448_IMUDriver::GetMagY()
{
    return m_pDevice->GetMagInstantY();
}


double ADIS16448_IMUDriver::GetMagZ()
{   
    return m_pDevice->GetMagInstantZ();
}


void ADIS16448_IMUDriver::ResetAngles()
{
    m_pDevice->Reset();
}


void ADIS16448_IMUDriver::CalibrateIMU()
{
    m_pDevice->Calibrate();
}


/**
 * This function is designed to show you all of the sensor outputs of the IMU.
 * 
 * 3-Axis Angles, Accelerations, and Magnetic pulls, as well as temperature and pressure.
 */
void ADIS16448_IMUDriver::LogAllValues()
{
    Util::Log("Angle X", GetAngleX(), "IMU DRIVER");
    Util::Log("Angle Y", GetAngleY(), "IMU DRIVER");
    Util::Log("Angle Z", GetAngleZ(), "IMU DRIVER");
    Util::Log("Magnetic Instant X", GetMagX(), "IMU DRIVER");
    Util::Log("Magnetic Instant Y", GetMagY(), "IMU DRIVER");
    Util::Log("Magnetic Instant Z", GetMagZ(), "IMU DRIVER");
    Util::Log("Acceleration X", GetAccelX(), "IMU DRIVER");
    Util::Log("Acceleration Y", GetAccelY(), "IMU DRIVER");
    Util::Log("Acceleration Z", GetAccelZ(), "IMU DRIVER");
    Util::Log("Temperature", GetTemperature(),"IMU DRIVER");
    Util::Log("Pressure", GetPressure(), "IMU DRIVER");
}

// Completed 3/4/2020
