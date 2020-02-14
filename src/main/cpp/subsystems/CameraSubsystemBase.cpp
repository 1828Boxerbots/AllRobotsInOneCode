/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystemBase.h"
#include "Constants.h"
#include "subsystems/DriveTrainSubsystemBase.h"

CameraSubsystemBase::CameraSubsystemBase(DriveTrainSubsystemBase *pDrive) {m_pDriveObject = pDrive;}

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

void CameraSubsystemBase::SetColor()
{
    inRange(m_frame, Scalar(0, 150, 0), Scalar(175, 255, 175), m_colorFiliter);//BGR
}

void CameraSubsystemBase::FilterFrame()
{
    SetColor();
    
    morphologyEx(m_colorFiliter, m_openFilter, MORPH_OPEN, m_morp, Point(-1, -1), 4);
    dilate(m_openFilter,m_dilution,m_morp);
    morphologyEx(m_dilution, m_output, MORPH_CLOSE, m_morp,Point(-1,-1),4);
}
void CameraSubsystemBase::CenterMomment()
{
    m_moment = cv::moments(m_output);
    m_center = cv::Point2f(m_moment.m10 / m_moment.m00, m_moment.m01 / m_moment.m00);

}

void CameraSubsystemBase::InitSendImage()
{
    #ifdef SEND_VIDEO
    // Get a CvSink. This will capture Mats from the Camera
    m_cvSink = frc::CameraServer::GetInstance()->GetVideo();
    
    // Setup a CvSource. This will send images back to the Dashboard
    m_outputStream = frc::CameraServer::GetInstance()->PutVideo("Rectangle", m_sendSizeHeight, m_sendSizeWidth);
    #endif
}

void CameraSubsystemBase::SendImage()
{
    #ifdef SEND_VIDEO

    if (m_cvSink.GrabFrame(m_sendFrame) == 0) 
    {
        // Send the output the error.
        m_outputStream.NotifyError(m_cvSink.GetError());
    }
    else
    {
        // Add a RED rectangle on the image
        //auto WHITE = cv::Scalar(255,255,255);
        auto RED = cv::Scalar(255,0,0);
        int thickness = 5;
        rectangle(m_sendFrame,
                cv::Point(m_center.y - m_sendRectHeight/2, m_center.x - m_sendRectWidth/2),
                cv::Point(m_center.y + m_sendRectHeight/2, m_center.x + m_sendRectWidth/2),
                RED, thickness);

        // Give the output stream a new image to display
        m_outputStream.PutFrame(m_sendFrame);
    }
    
    #endif
}

int CameraSubsystemBase::WhereToTurn()
{
    frc::SmartDashboard::PutBoolean("ABC", true);
    SendImage();

    if ( m_center.x > GetLeftMin() && m_center.x <  GetLeftMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Left");
        return GO_LEFT;
    }
    if(m_center.x  > GetRightMin() && m_center.x < GetRightMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Right");
        return GO_RIGHT;
    }
    if(m_center.x  < GetCenterMin() && m_center.x  > GetCenterMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Center");
        return STOP;
    }
    if (m_center.x < 0 || m_center.x > GetMaxResolutionX())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "CANT SEE");
        return CANT_FIND_IMAGE; 
    }
    return STOP;

}

void CameraSubsystemBase::PrintTurn(int turn)
{
    double printturn = turn;
    m_printX = m_center.x;
    frc::SmartDashboard::PutNumber("turn",printturn);
    frc::SmartDashboard::PutNumber("center of x",m_printX);
    //imshow("camera",Output);
 
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
    //CameraPeriodic();
}

void CameraSubsystemBase::CameraPeriodic()
{
    m_frameNumber++;
    frc::SmartDashboard::PutNumber("Camera Frame Number", m_frameNumber);
    Tick();
}
void CameraSubsystemBase::AutoCameraTurn()
{
    int dir = WhereToTurn();
    while (dir != 0)
    {
        if (dir == +1) m_pDriveObject->TurnRight();
        if (dir == -1) m_pDriveObject->TurnLeft();
        dir = WhereToTurn();
    }
}

