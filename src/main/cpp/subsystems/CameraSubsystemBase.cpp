/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/CameraSubsystemBase.h"
#include "Constants.h"
#include "subsystems/DriveTrainSubsystemBase.h"

CameraSubsystemBase::CameraSubsystemBase(DriveTrainSubsystemBase *pDrive) 
{
    m_pDriveObject = pDrive;
}

void CameraSubsystemBase::InitializeCamera(int port)
{
    m_video.open(port);
    m_isInitialized = true;
}

void CameraSubsystemBase::IntakeFrame()
{
    if (m_isInitialized == false) 
    {
        return;
    }
    m_video >> m_frame;
}

void CameraSubsystemBase::Init()
{
    if (m_isInitialized == true)
    {
        return;
    }
    InitializeCamera(USB_CAMERA_ONE);
    m_isInitialized = true;
}

void CameraSubsystemBase::SetColor()
{
    if (m_isInitialized == false) 
    {
        return;
    }
    cv::inRange(m_frame, cv::Scalar(LOW_BLUE, LOW_GREEN, LOW_RED), cv::Scalar(HIGH_BLUE, HIGH_GREEN, HIGH_RED), m_colorFilter);//BGR
}

void CameraSubsystemBase::FilterFrame()
{
    if (m_isInitialized == false) 
    {
        return;
    }
    SetColor();
    
    cv::morphologyEx(m_colorFilter, m_openFilter, cv::MORPH_OPEN, m_morph, cv::Point(-1, -1), 4);
    cv::dilate(m_openFilter,m_dilution,m_morph);
    cv::morphologyEx(m_dilution, m_output, cv::MORPH_CLOSE, m_morph, cv::Point(-1,-1),4);
}

void CameraSubsystemBase::CenterMoment()
{
    if (m_isInitialized == false) 
    {
        return;
    }
    m_moment = cv::moments(m_output);
    m_center = cv::Point2f(m_moment.m10 / m_moment.m00, m_moment.m01 / m_moment.m00);

}

void CameraSubsystemBase::InitSendImage()
{
    #ifdef SEND_VIDEO
    /*
    // Get a CvSink. This will capture Mats from the Camera
    m_cvSink = frc::CameraServer::GetInstance()->GetVideo();
    
    // Setup a CvSource. This will send images back to the Dashboard
    m_outputStream = frc::CameraServer::GetInstance()->PutVideo("Rectangle", m_sendSizeHeight, m_sendSizeWidth);
    */
    #endif
}

void CameraSubsystemBase::SendImage()
{
    #ifdef SEND_VIDEO
/*
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
*/    
    #endif
}

int CameraSubsystemBase::WhereToTurn()
{
    frc::SmartDashboard::PutNumber("CodeRun", false);
    frc::SmartDashboard::PutBoolean("ABC", false);
    if (m_isInitialized == false) 
    {
        frc::SmartDashboard::PutBoolean("ABC", true);
        return CANT_FIND_IMAGE; 
    }
    SendImage();
    Tick();
    if ( m_center.x > GetLeftMin() && m_center.x <  GetLeftMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Left");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return GO_LEFT;
    }
    if(m_center.x  > GetRightMin() && m_center.x < GetRightMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Right");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return GO_RIGHT;
    }
    if(m_center.x  < GetCenterMin() && m_center.x  > GetCenterMax())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "Center");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return STOP;
    }
    if (m_center.x < 0 || m_center.x > GetMaxResolutionX())
    {
        frc::SmartDashboard::PutString("Camera Turn To", "CANT SEE");
        frc::SmartDashboard::PutBoolean("ABC", true);
        return CANT_FIND_IMAGE; 
    }
    frc::SmartDashboard::PutBoolean("ABC", true);
    frc::SmartDashboard::PutBoolean("CodeRun", true);
    return STOP;
    }
void CameraSubsystemBase::PrintTurn(int turn)
{
    double printturn = turn;
    m_printX = m_center.x;
    frc::SmartDashboard::PutNumber("turn",printturn);
    frc::SmartDashboard::PutNumber("center of x",m_printX);
    frc::SmartDashboard::PutNumber("Shadow", 969);
    //imshow("camera",Output);
}

void CameraSubsystemBase::Tick()
{
    frc::SmartDashboard::PutNumber("Shadow", 777);
    IntakeFrame();
    frc::SmartDashboard::PutNumber("Shadow", 888);
    FilterFrame();
    frc::SmartDashboard::PutNumber("Shadow", 999);
    CenterMoment();
    frc::SmartDashboard::PutNumber("Shadow", 1000);
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

    frc::SmartDashboard::PutBoolean("CameraWork", false);
    int dir;
    m_frameNumber++;
    frc::SmartDashboard::PutNumber("CameraWork frameNum", m_frameNumber);
    do
    {
frc::SmartDashboard::PutNumber("Shadow", 1);
        dir = WhereToTurn();
        frc::SmartDashboard::PutNumber("Camera Direction", dir);

frc::SmartDashboard::PutNumber("Shadow", 2);
        m_frameNumber++;
        frc::SmartDashboard::PutNumber("CameraWork frameNum", m_frameNumber);

frc::SmartDashboard::PutNumber("Shadow", 3);
        if (dir == 1) 
        {
frc::SmartDashboard::PutNumber("Shadow", 4);
            m_pDriveObject->TurnRight();
frc::SmartDashboard::PutNumber("Shadow", 5);
        }
        if (dir == -1) 
        {
frc::SmartDashboard::PutNumber("Shadow", 6);
            m_pDriveObject->TurnLeft();
frc::SmartDashboard::PutNumber("Shadow", 7);
        }
        if(dir != -1 && dir != +1) 
        {
frc::SmartDashboard::PutNumber("Shadow", 8);
            m_pDriveObject->TurnLeft(); 
            frc::SmartDashboard::PutBoolean("CodeBroke", true);
frc::SmartDashboard::PutNumber("Shadow", 9);
        }
    } while(dir != STOP);
frc::SmartDashboard::PutNumber("Shadow", 10);
    frc::SmartDashboard::PutBoolean("CameraWork", true);
}

