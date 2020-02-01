/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystemBase.h"

CameraSubsystemBase::CameraSubsystemBase() {}

void CameraSubsystemBase::InterlizeCamera(int port)
{
    m_video.open(port);
}

void CameraSubsystemBase::IntakeFrame()
{
    m_video >> m_frame;

}

void CameraSubsystemBase::Init()
{
    InterlizeCamera(USB_CAMERA_ONE);
}

void CameraSubsystemBase::FilterFrame()
{
    inRange(m_frame, Scalar(0, 0, 200), Scalar(120, 120, 255), m_colorFilter);//BGR
    morphologyEx(m_colorFilter, m_closeFilter, MORPH_CLOSE, m_morp,Point(-1,-1),4);
    morphologyEx(m_colorFilter, m_openFilter, MORPH_OPEN, m_morp, Point(-1, -1), 4);
}
void CameraSubsystemBase::CenterMomment()
{
    m_moment = cv::moments(m_openFilter);
    m_center = cv::Point2f(m_moment.m10 / m_moment.m00, m_moment.m01 / m_moment.m00);

}

int CameraSubsystemBase::WhereToTurn()
{
    frc::SmartDashboard::PutNumber("Camera Center", m_center.x);
    if (m_center.x < 270)
    {
        // std::cout << "left" << std::endl;
        frc::SmartDashboard::PutString("Camera Turn To", "Left");
        return -1;
    }
    if(m_center.x  > 370)
    {
        //std::cout << "right" << std::endl;
        frc::SmartDashboard::PutString("Camera Turn To", "Right");
        return 1;
    }
    if(m_center.x  < 370 && m_center.x  > 270)
    {
        //std::cout << "m_center" << std::endl;
        frc::SmartDashboard::PutString("Camera Turn To", "Cener");
        return 0;
    }
    return 0;

}

void CameraSubsystemBase::PrintTurn(int turn)
{
    double print = turn;
    frc::SmartDashboard::PutNumber("turn",print);
}

void CameraSubsystemBase::Tick()
{
    IntakeFrame();
    FilterFrame();
    CenterMomment();
}

// This method will be called once per scheduler run
void CameraSubsystemBase::Periodic() 
{
    m_frameNumber++;
    frc::SmartDashboard::PutNumber("Camera Frame Number", m_frameNumber);
    Tick();
}
