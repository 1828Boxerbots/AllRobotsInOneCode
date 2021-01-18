#include "Drivers/CameraVision.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


CameraVision::CameraVision(int port)
{
	m_index = port;
}

bool CameraVision::Init()
{
	// cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    // camera.SetResolution(640, 480);
    // cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
    // cv::Mat source;

	m_camera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
	m_camera.SetResolution(640,480);
	m_cvSink = frc::CameraServer::GetInstance() -> GetVideo();
	m_outputStream = frc::CameraServer::GetInstance()->PutVideo("Filtered One", 640, 480);

	return true;
}

void CameraVision::Tick()
{
	// if(m_cvSink.GrabFrame(m_frame) == 0)
	// {
	// 	return;
	// }

	//cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0,0,255), 3);

	GetBlob();

	//m_outputStream.PutFrame(m_frame);
}

double CameraVision::WhereToTurn(double deadZone)
{
	//Check if there is a blob
	if (GetBlob() == false /*|| m_centroidX == nan( && m_centroidY == nan(ind)*/)
	{
		return -2.0;
	}

	//std::cout << m_centroidX << std::endl;
	//std::cout << m_centroidY << std::endl;

	//Get the Center of the screen
	double screenCenter = m_frame.size().width / 2;
	//Get Dead zone values
	double highDedZone = screenCenter + m_deadZone;
	double lowDedZone = screenCenter - m_deadZone;
	//Check if we are in the dead zone
	if (m_centroidX > lowDedZone && m_centroidX < highDedZone)
	{
		return 0.0;
	}

	//Use some MATH to turn our position into a percentage and return
	double powerPercentage = (m_centroidX - screenCenter) / screenCenter;
	// cv::Mat textImg = m_frame;
	// cv::QtFont font;
	// std::string powerPercentageStr = std::to_string(powerPercentage);

	// cv::putText(textImg, powerPercentageStr, cv::Point(m_centroidX, m_centroidY), cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(255, 0, 0), 2);
	// SendImage("TextImage", textImg);

	return powerPercentage;
}


void CameraVision::SendImage(std::string title, cv::Mat frame/*, int width, int height*/)
{
	//cs::CvSource outputVideo = frc::CameraServer::GetInstance()->PutVideo(title, width, height);
	m_outputStream.PutFrame(frame);
}

bool CameraVision::GetBlob()
{
	//Gets one frame from camera
	if(m_cvSink.GrabFrame(m_frame) == 0)
	{
		return false;
	}
	/*if (m_frame.empty() == true)
		return false; //Exit if empty*/

	//Filter the image
	SetColor();

	//Place a 2 line where the blob is
	cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0,0,255), 3);
	cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);

	//Show where the center of the screen is on the camera
	double screenCenter = m_frame.size().width / 2;
	cv::line(m_frame, cv::Point(screenCenter, 0), cv::Point(screenCenter, m_frame.size().height), cv::Scalar(255, 0, 0), 3);

	// //Display the new image
	SendImage("raw image", m_frame);

	//cv::waitKey(1);

	//Checks is there is no blob
	// if (isnan(m_centroidX) && isnan(m_centroidY))
	// {
	// 	return false;
	// }

	return true;
}

void CameraVision::SetColor()
{
	//Change the camera image from BGR to HSV - Blue Green Red to Hue Saturation Value
	cv::Mat imgHSV;
	cv::cvtColor(m_frame, imgHSV, cv::COLOR_BGR2HSV);
	//SendImage("grey image", imgHSV);

	//Looks for specifc colors in the image
	cv::Mat imgThresholded;
	cv::inRange(imgHSV, cv::Scalar(m_iLowH, m_iLowS, m_iLowV), cv::Scalar(m_iHighH, m_iHighS, m_iHighV), imgThresholded);
	//Display Filtered Image
	//SendImage("Threshold", imgThresholded);
	// Find moments of the image
	cv::Moments m = cv::moments(imgThresholded, true);
	m_centroidX = m.m10 / m.m00;
	m_centroidY = m.m01 / m.m00;
	cv::Point p(m_centroidX, m_centroidY);

}
