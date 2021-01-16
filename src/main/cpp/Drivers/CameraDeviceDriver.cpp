/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Drivers/CameraDeviceDriver.h"

CameraDeviceDriver::CameraDeviceDriver(int index) 
{
    m_index = index;
}

bool CameraDeviceDriver::Init()
{
    m_USBcamera = cs::UsbCamera("USB Camera", m_index);
    // if(m_CVcamera.open(0))
    // {
    //     return false;
    // }
    // return true;
}

void CameraDeviceDriver::DisplayCamera()
{
    m_USBcamera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
    m_USBcamera.SetResolution(640, 480);
}
