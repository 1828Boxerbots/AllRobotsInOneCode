/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystemBase.h"

CameraSubsystem::CameraSubsystem() {}

void CameraSubsystem::InterlizeCamera(int port)
{
    m_video.open(port);
}

void CameraSubsystem::IntakeFrame()
{
    m_video >> m_frame;

}
void CameraSubsystem::FilterFrame()
{
    inRange(m_frame, Scalar(0, 0, 200), Scalar(120, 120, 255), m_colorFilter);//BGR
    morphologyEx(m_colorFilter, m_closeFilter, MORPH_CLOSE, m_morp,Point(-1,-1),4);
    morphologyEx(m_colorFilter, m_openFilter, MORPH_OPEN, m_morp, Point(-1, -1), 4);
}
void CameraSubsystem::CenterMomment()
{
    m_moment = cv::moments(m_openFilter);
    m_center = cv::Point2f(m_moment.m10 / m_moment.m00, m_moment.m01 / m_moment.m00);

}
int CameraSubsystem::WhereToTurn()
{
    if (m_center.x < 270)
    {
        // std::cout << "left" << std::endl;
        return -1;
    }
    if(m_center.x  > 370)
    {
        //std::cout << "right" << std::endl;
        return 1;
    }
    if(m_center.x  < 370 && m_center.x  > 270)
    {
        //std::cout << "m_center" << std::endl;
        return 0;
    }
    return 0;

}

void CameraSubsystem::PrintTurn(int turn)
{
    double print = turn;
    frc::SmartDashboard::PutNumber("turn",print);
}


// This method will be called once per scheduler run
void CameraSubsystem::Periodic() 
{
    IntakeFrame();
    FilterFrame();
    CenterMomment();
}
