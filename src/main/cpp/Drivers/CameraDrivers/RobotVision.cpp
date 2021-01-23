#include "Drivers/CameraDrivers/RobotVision.h"
#include <opencv2/imgproc/imgproc.hpp>


RobotVision::RobotVision() : WindowsVisionBase(0)
{
	
}

void RobotVision::Init()
{
	m_camera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
	m_camera.SetResolution(640,480);
	m_cvSink = frc::CameraServer::GetInstance() -> GetVideo();
	m_outputStream = frc::CameraServer::GetInstance()->PutVideo("Filtered Two", 640, 480);
	
}

void RobotVision::Tick()
{
	if(GetImage() == false)
    {
        return;
    }

	cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0, 0, 255), 3);

	//m_outputStream.PutFrame(m_frame);
	SendImage("output", m_frame);
}

void RobotVision::SendImage(std::string title, cv::Mat frame)
{
	m_outputStream.PutFrame(frame);
}

bool RobotVision::GetImage()
{
    if (m_cvSink.GrabFrame(m_frame) == 0)
	{
		return false;
	}

    return true;
}

void RobotVision::Log(std::string title, std::string value)
{
	Util::Log(title, value);
}