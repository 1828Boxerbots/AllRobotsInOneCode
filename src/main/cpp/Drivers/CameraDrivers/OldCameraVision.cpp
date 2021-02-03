#include "Drivers/CameraDrivers/OldCameraVision.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Util.h"
#include <math.h>

OldCameraVision::OldCameraVision(int port)
{
	m_index = port;
}

bool OldCameraVision::Init()
{
	// cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
    // camera.SetResolution(640, 480);
    // cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
    // cs::CvSource outputStreamStd = frc::CameraServer::GetInstance()->PutVideo("Gray", 640, 480);
    // cv::Mat source;

	m_camera = frc::CameraServer::GetInstance() -> StartAutomaticCapture();
	m_camera.SetResolution(160,120);
	m_cvSink = frc::CameraServer::GetInstance() -> GetVideo();
	m_outputStream = frc::CameraServer::GetInstance()->PutVideo(IMAGE_FILTERED, 160, 120);
	m_outputStreamTwo = frc::CameraServer::GetInstance()->PutVideo(IMAGE_THRESHOLD, 160, 120);
	return true;
}

void OldCameraVision::Tick()
{
	// if(m_cvSink.GrabFrame(m_frame) == 0)
	// {
	// 	return;
	// }

	//cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0,0,255), 3);

	GetBlob(1000000000000000000000000000000);

	//m_outputStream.PutFrame(m_frame);
}

//deadZone can be a range of -1 to 1
double OldCameraVision::WhereToTurn(double deadZoneLocation, int deadZoneRange)
{
	Util::Log("Frame Counter", m_frameCounter++);

	double screenCenter = m_frame.size().width / 2;
	int deadZone2 = (deadZoneLocation*screenCenter)+screenCenter;

	//Check if there is a blob
	if (GetBlob(deadZone2) == false /*|| m_centroidX == nan( && m_centroidY == nan(ind)*/)
	{
		return OUT_OF_CAMERA_RANGE;
	}

	//std::cout << m_centroidX << std::endl;
	//std::cout << m_centroidY << std::endl;

	//Get the Center of the screen

	//Use some MATH to turn the deadZone from a percentage to the size of the screen

	//Get Dead zone values
	int highDedZone = deadZone2 + deadZoneRange;
	int lowDedZone = deadZone2 - deadZoneRange;
	Util::Log("Shadow 4", deadZone2);
	//Check if we are in the dead zone
	if (m_centroidX > lowDedZone && m_centroidX < highDedZone)
	{
		return 0.0;
	}

	//Use some MATH to turn our position into a percentage and return
	double powerPercentage = ((m_centroidX - screenCenter) / screenCenter) - deadZoneLocation;
	if(powerPercentage>1.0)
	{
		powerPercentage = 1.0;
	}
	if(powerPercentage<-1.0)
	{
		powerPercentage = -1.0;
	}
	// cv::Mat textImg = m_frame;
	// cv::QtFont font;
	// std::string powerPercentageStr = std::to_string(powerPercentage);

	// cv::putText(textImg, powerPercentageStr, cv::Point(m_centroidX, m_centroidY), cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(255, 0, 0), 2);
	// SendImage("TextImage", textImg);

	return powerPercentage;
}


void OldCameraVision::SendImage(std::string title, cv::Mat frame/*, int width, int height*/)
{
	//cs::CvSource outputVideo = frc::CameraServer::GetInstance()->PutVideo(title, width, height);
	if(title == IMAGE_FILTERED)
	{
		m_outputStream.PutFrame(frame);
	}
	else if(title == IMAGE_THRESHOLD)
	{
		m_outputStreamTwo.PutFrame(frame);
	}
}

bool OldCameraVision::GetBlob(int deadZonePixel)
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

	if(m_centroidY > 0.0 && m_centroidX > 0.0)
	{
		//Place a 2 line where the blob is
		switch (m_visionColor)
		{
		case VisionColors::GREEN_CONE:
			cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0,255,0), 3);
			cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 255, 0), 3);
			break;
		case VisionColors::RED_CONE:
			cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0,0,255), 3);
			cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
		default:
			cv::line(m_frame, cv::Point(0, m_centroidY), cv::Point(m_frame.size().width, m_centroidY), cv::Scalar(0,0,255), 3);
			cv::line(m_frame, cv::Point(m_centroidX, 0), cv::Point(m_centroidX, m_frame.size().height), cv::Scalar(0, 0, 255), 3);
			break;
		}

		//Show where deadzone is
		cv::line(m_frame, cv::Point(deadZonePixel, 0), cv::Point(deadZonePixel, m_frame.size().height), cv::Scalar(255, 0, 0), 3);
	}
	else
	{
		return false;
	}
	// //Display the new image
	SendImage(IMAGE_FILTERED, m_frame);

	//cv::waitKey(1);

	//Checks is there is no blob
	// if (isnan(m_centroidX) && isnan(m_centroidY))
	// {
	// 	return false;
	// }

	return true;
}

void OldCameraVision::SetColor()
{
	//Change the camera image from BGR to HSV - Blue Green Red to Hue Saturation Value
	cv::cvtColor(m_frame, m_imgHSV, cv::COLOR_BGR2HSV);
	//SendImage("grey image", imgHSV);

	//Looks for specifc colors in the image

	cv::Scalar resultL;
	cv::Scalar resultH;

	switch(m_visionColor)
	{
		case VisionColors::GREEN_CONE:
			resultL = GREEN_CONE_LOW;
			resultH = GREEN_CONE_HIGH;
			break;
		case VisionColors::RED_CONE:
			resultL = RED_CONE_LOW;
			resultH = RED_CONE_LOW;
			break;
		case VisionColors::YELLOW_CONE:
			resultL = YELLOW_CONE_LOW;
			resultH = YELLOW_CONE_LOW;
			break;
		case VisionColors::ORANGE_CONE:
			resultL = ORANGE_CONE_LOW;
			resultH = ORANGE_CONE_LOW;
			break;
		default:
			resultL = GREEN_CONE_LOW;
			resultH = GREEN_CONE_LOW;
			break;
	}

	cv::inRange(m_imgHSV, resultL, resultH, m_imgThresholded);

	//Display Filtered Image
	SendImage(IMAGE_THRESHOLD, m_imgThresholded);
	// Find moments of the image
	cv::Moments m = cv::moments(m_imgThresholded, true);
	if(m.m00 != 0)
	{
		Util::Log("OldCameraVision", "centroids were valid");
		m_centroidX = m.m10 / m.m00;
		m_centroidY = m.m01 / m.m00;
		cv::Point p(m_centroidX, m_centroidY);
	}
	else
	{
		Util::Log("OldCameraVision", "centroids were divied by 0");
		m_centroidX = -1.0;
		m_centroidY = -1.0;
	}
}
