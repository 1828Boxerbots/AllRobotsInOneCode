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
	m_camera.SetResolution( M_CAMERA_WIDTH, M_CAMERA_HEIGHT );
	//m_camera.SetExposureHoldCurrent();
	//m_camera.SetWhiteBalanceHoldCurrent();
	m_cvSink = frc::CameraServer::GetInstance() -> GetVideo();
	m_outputStream = frc::CameraServer::GetInstance()->PutVideo( IMAGE_FILTERED, M_CAMERA_WIDTH, M_CAMERA_HEIGHT );
	m_outputStreamTwo = frc::CameraServer::GetInstance()->PutVideo ( IMAGE_THRESHOLD, M_CAMERA_WIDTH, M_CAMERA_HEIGHT );
	m_outputStreamHSV = frc::CameraServer::GetInstance()->PutVideo ( IMAGE_HSV, M_CAMERA_WIDTH, M_CAMERA_HEIGHT);

	//Setting Crop
	double rioW = 70;
	SetCrop((M_CAMERA_WIDTH/2) - (rioW/2), (M_CAMERA_HEIGHT*0.75), rioW, M_CAMERA_HEIGHT*0.25);
	//SetCrop(0, M_CAMERA_HEIGHT*0.75, M_CAMERA_WIDTH, M_CAMERA_HEIGHT*0.25);

	return true;
}

void OldCameraVision::Tick()
{
	// if(m_cvSink.GrabFrame(m_frame) == 0)
	// {
	// 	return;
	// }

	//cv::line(m_frame, cv::Point(0, 0), cv::Point(m_frame.size().width, m_frame.size().height), cv::Scalar(0,0,255), 3);

	WhereToTurn();

	//m_outputStream.PutFrame(m_frame);
}

void OldCameraVision::SetCrop(int cropX, int cropY, int cropW, int cropH)
{
	m_cropX = cropX;
	m_cropY = cropY;
	m_cropW = cropW;
	m_cropH = cropH;
}

void OldCameraVision::GetSize(int *pHeight, int *pWidth)
{
	*pHeight = M_CAMERA_HEIGHT;
	*pWidth = M_CAMERA_WIDTH;
}

//deadZone can be a range of -1 to 1
double OldCameraVision::WhereToTurn(double deadZoneLocation, int deadZoneRange)
{
	Util::Log("Frame Counter", m_frameCounter++);

	int deadZone2 = ( deadZoneLocation * m_screenCenterX ) + m_screenCenterX;

	//Check if there is a blob
	if (GetBlob(deadZone2) == false /*|| m_centroidX == nan( && m_centroidY == nan(ind)*/)
	{
		Util::Log("WhereToTurn Result", OUT_OF_CAMERA_RANGE);
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
		Util::Log("WhereToTurn Result", 0.0);
		return 0.0;
	}

	//Use some MATH to turn our position into a percentage and return
	double powerPercentage = ( ( m_centroidX - m_screenCenterX ) / m_screenCenterX ) - deadZoneLocation;
	if( powerPercentage > 1.0 )
	{
		powerPercentage = 1.0;
	}
	if( powerPercentage < -1.0 )
	{
		powerPercentage = -1.0;
	}
	// cv::Mat textImg = m_frame;
	// cv::QtFont font;
	// std::string powerPercentageStr = std::to_string(powerPercentage);

	// cv::putText(textImg, powerPercentageStr, cv::Point(m_centroidX, m_centroidY), cv::FONT_HERSHEY_SIMPLEX, 2.0, cv::Scalar(255, 0, 0), 2);
	// SendImage("TextImage", textImg);

	Util::Log("WhereToTurn Result", powerPercentage);
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
	else if(title == IMAGE_HSV)
	{
		m_outputStreamHSV.PutFrame(frame);
	}
}

bool OldCameraVision::GrabFrame()
{
	if(m_cvSink.GrabFrame(m_frame) == 0)
	{
		return false;
	}
	return true;
}

bool OldCameraVision::GetBlob(int deadZonePixel)
{
	//Gets one frame from camera
	if(GrabFrame() == false)
	{
		return false;
	}
	/*if (m_frame.empty() == true)
		return false; //Exit if empty*/

	//Filter the image
	SetColor();

	if( ( m_centroidY > 0.0 ) && ( m_centroidX > 0.0 ) )
	{
		cv::Point yPoint = cv::Point(0, m_centroidY); // Uppermost Y point
		cv::Point xPoint = cv::Point(m_centroidX, 0); // Leftmost X point
		cv::Point yHPoint = cv::Point(M_CAMERA_WIDTH, m_centroidY); // Lowest Y point
		cv::Point xHPoint = cv::Point(m_centroidX, M_CAMERA_HEIGHT); // Rightmost X point
		cv::Scalar lineColor; // Color of the line


		//Place a 2 line where the blob is
		switch (m_visionColor)
		{
		case VisionColors::GREEN_CONE_N:
			lineColor = cv::Scalar(0,255,0); // Green
			break;
		case VisionColors::RED_CONE_N:
			lineColor = cv::Scalar(0,0,255); // Red
			break;
		case VisionColors::YELLOW_CONE:
			lineColor = cv::Scalar(0,255,125); // Yellow
			break;
		case VisionColors::ORANGE_CONE:
			lineColor = cv::Scalar(0,255,200); // Orange
			break;
		default:
			lineColor = cv::Scalar(0,0,255); // Red as Default
			break;
		}
		//Point Lines
		cv::line(m_frame, yPoint, yHPoint, lineColor, M_LINE_THICKNESS);
		cv::line(m_frame, xPoint, xHPoint, lineColor, M_LINE_THICKNESS);
		//ROI Lines
		cv::line(m_frame, cv::Point(m_cropX, m_cropY), cv::Point(m_cropX + m_cropW, m_cropY), cv::Scalar(0, 255, 200)); // Top Line
		cv::line(m_frame, cv::Point(m_cropX, m_cropY), cv::Point(m_cropX, m_cropY + m_cropH - 5), cv::Scalar(0, 255, 200));// Left Line
		cv::line(m_frame, cv::Point(m_cropX + m_cropW, m_cropY), cv::Point(m_cropX+m_cropW, m_cropY + m_cropH - 5), cv::Scalar(0, 255, 200));// Right Line

		//Show where deadzone is
		cv::line(m_frame, cv::Point(deadZonePixel, 0), cv::Point(deadZonePixel, M_CAMERA_HEIGHT - 5), M_DEADZONE_COLOR, M_LINE_THICKNESS);
	}
	else
	{
		return false;
	}
	// //Display the new image
	SendImage(IMAGE_FILTERED, m_frame);

	//Checks is there is no blob
	if (isnan(m_centroidX) && isnan(m_centroidY))
	{
	 	return false;
	}

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
		//Green
		case VisionColors::GREEN_CONE_M:
			resultL = GREEN_CONE_LOW_M;
			resultH = GREEN_CONE_HIGH_M;
			break;
		case VisionColors::GREEN_CONE_A:
			resultL = GREEN_CONE_LOW_A;
			resultH = GREEN_CONE_HIGH_A;
			break;
		case VisionColors::GREEN_CONE_N:
			resultL = GREEN_CONE_LOW_N;
			resultH = GREEN_CONE_HIGH_N;
			break;
		//Red
		case VisionColors::RED_CONE_M:
			resultL = RED_CONE_LOW_M;
			resultH = RED_CONE_HIGH_M;
			break;
		case VisionColors::RED_CONE_A:
			resultL = RED_CONE_LOW_A;
			resultH = RED_CONE_HIGH_A;
			break;
		case VisionColors::RED_CONE_N:
			resultL = RED_CONE_LOW_N;
			resultH = RED_CONE_HIGH_N;
			break;
		//Yellow Lemon
		case VisionColors::YELLOW_LEMON_M:
			resultL = YELLOW_LEMON_LOW_M;
			resultH = YELLOW_LEMON_HIGH_M;
			break;
		case VisionColors::YELLOW_LEMON_A:
			resultL = YELLOW_LEMON_LOW_A;
			resultH = YELLOW_LEMON_HIGH_A;
			break;
		case VisionColors::YELLOW_LEMON_N:
			resultL = YELLOW_LEMON_LOW_N;
			resultH = YELLOW_LEMON_HIGH_N;
			break;
		//Purple
		case VisionColors::PURPLE_BOTTLE_M:
			resultL = PURPLE_BOTTLE_LOW_M;
			resultH = PURPLE_BOTTLE_HIGH_M;
			break;
		case VisionColors::PURPLE_BOTTLE_A:
			resultL = PURPLE_BOTTLE_LOW_A;
			resultH = PURPLE_BOTTLE_HIGH_A;
			break;
		case VisionColors::PURPLE_BOTTLE_N:
			resultL = PURPLE_BOTTLE_LOW_N;
			resultH = PURPLE_BOTTLE_HIGH_N;
			break;
		//Others
		case VisionColors::YELLOW_CONE:
			resultL = YELLOW_CONE_LOW;
			resultH = YELLOW_CONE_HIGH;
			break;
		case VisionColors::ORANGE_CONE:
			resultL = ORANGE_CONE_LOW;
			resultH = ORANGE_CONE_HIGH;
			break;
		//FMS Color
		case VisionColors::FMS_COLOR:
			resultL = FMS_LOW;
			resultH = FMS_HIGH;
			break;
		default:
			resultL = YELLOW_LEMON_LOW_A;
			resultH = YELLOW_LEMON_HIGH_A;
			break;
	}

	Util::Log("LowH", resultL.val[0]);
	Util::Log("HighH", resultH.val[0]);
	Util::Log("LowS", resultL.val[1]);
	Util::Log("HighS", resultH.val[1]);
	Util::Log("LowV", resultL.val[2]);
	Util::Log("HighV", resultH.val[2]);

	m_rect = cv::Rect2d(m_cropX, m_cropY, m_cropW, m_cropH);
	m_imgHSV = m_imgHSV(m_rect);

	SendImage(IMAGE_HSV, m_imgHSV);

	cv::inRange(m_imgHSV, resultL, resultH, m_imgThresholded);

	cv::erode(m_imgThresholded, m_imgThresholdedTwo, cv::getStructuringElement(cv::MorphShapes::MORPH_ELLIPSE, cv::Size(5, 5)));
	cv::dilate(m_imgThresholdedTwo, m_imgThresholded, cv::getStructuringElement(cv::MorphShapes::MORPH_ELLIPSE, cv::Size(6, 6)));

	//Display Filtered Image
	SendImage(IMAGE_THRESHOLD, m_imgThresholded);
	// Find moments of the image
	cv::Moments m = cv::moments(m_imgThresholded, true);
	if(m.m00 != 0)
	{
		Util::Log("OldCameraVision", "centroids were valid");
		m_centroidX = (m.m10 / m.m00) + m_cropX;
		m_centroidY = (m.m01 / m.m00) + m_cropY;
		cv::Point p(m_centroidX, m_centroidY);
	}
	else
	{
		Util::Log("OldCameraVision", "centroids were divied by 0");
		m_centroidX = -1.0;
		m_centroidY = -1.0;
	}

	GetCentroidX();
	GetCentroidY();

	Util::DelayInSeconds(0.5);
}

void OldCameraVision::SetHigh(int HSV, int value)
{
	switch (HSV)
	{
	case 1:
		FMS_HIGH.val[0] = value;
		break;
	case 2:
		FMS_HIGH.val[1] = value;
		break;
	case 3:
		FMS_HIGH.val[2] = value;
		break;
	default:
		FMS_HIGH.val[1] = value;
		break;
	}
}

void OldCameraVision::SetLow(int HSV, int value)
{
	switch (HSV)
	{
	case 1:
		FMS_LOW.val[0] = value;
		break;
	case 2:
		FMS_LOW.val[1] = value;
		break;
	case 3:
		FMS_LOW.val[2] = value;
		break;
	default:
		FMS_LOW.val[1] = value;
		break;
	}
}

void OldCameraVision::SetFMSColor(VisionColors color)
{
	switch (color)
	{
		//Red
	case OldCameraVision::RED_CONE_M:
		FMS_LOW = RED_CONE_LOW_M;
		FMS_HIGH = RED_CONE_HIGH_M;
		break;
	case OldCameraVision::RED_CONE_A:
		FMS_LOW = RED_CONE_LOW_A;
		FMS_HIGH = RED_CONE_HIGH_A;
		break;
	case OldCameraVision::RED_CONE_N:
		FMS_LOW = RED_CONE_LOW_N;
		FMS_HIGH = RED_CONE_HIGH_N;
		break;
		//Green
	case OldCameraVision::GREEN_CONE_M:
		FMS_LOW = GREEN_CONE_LOW_M;
		FMS_HIGH = GREEN_CONE_HIGH_M;
		break;
	case OldCameraVision::GREEN_CONE_A:
		FMS_LOW = GREEN_CONE_LOW_A;
		FMS_HIGH = GREEN_CONE_HIGH_A;
		break;
	case OldCameraVision::GREEN_CONE_N:
		FMS_LOW = GREEN_CONE_LOW_N;
		FMS_HIGH = GREEN_CONE_HIGH_N;
		break;
		//Yellow Lemon
	case OldCameraVision::YELLOW_LEMON_M:
		FMS_LOW = YELLOW_LEMON_LOW_M;
		FMS_HIGH = YELLOW_LEMON_HIGH_M;
		break;
	case OldCameraVision::YELLOW_LEMON_A:
		FMS_LOW = YELLOW_LEMON_LOW_A;
		FMS_HIGH = YELLOW_LEMON_HIGH_A;
		break;
	case OldCameraVision::YELLOW_LEMON_N:
		FMS_LOW = YELLOW_LEMON_LOW_N;
		FMS_HIGH = YELLOW_LEMON_HIGH_N;
		break;
		//Purple
	case OldCameraVision::PURPLE_BOTTLE_M:
		FMS_LOW = PURPLE_BOTTLE_LOW_M;
		FMS_LOW = PURPLE_BOTTLE_HIGH_M;
		break;
	case OldCameraVision::PURPLE_BOTTLE_A:
		FMS_LOW = PURPLE_BOTTLE_LOW_A;
		FMS_LOW = PURPLE_BOTTLE_HIGH_A;
		break;
	case OldCameraVision::PURPLE_BOTTLE_N:
		FMS_LOW = PURPLE_BOTTLE_LOW_N;
		FMS_LOW = PURPLE_BOTTLE_HIGH_N;
		break;
		//Other
	case OldCameraVision::YELLOW_CONE:
		FMS_LOW = YELLOW_CONE_LOW;
		FMS_HIGH = YELLOW_CONE_HIGH;
		break;
	case OldCameraVision::ORANGE_CONE:
		FMS_LOW = ORANGE_CONE_LOW;
		FMS_HIGH = ORANGE_CONE_HIGH;
		break;
	default:
		FMS_LOW = YELLOW_LEMON_LOW_M;
		FMS_HIGH = YELLOW_LEMON_HIGH_M;
		break;
	}
}

void OldCameraVision::SetLookingColor(VisionColors color)
{
	m_visionColor = color;
}

OldCameraVision::VisionColors OldCameraVision::GetLookingColor()
{
	return m_visionColor;
}

double OldCameraVision::GetCentroidX()
{
	Util::Log("Centroid X", m_centroidX);
	return m_centroidX;
}

double OldCameraVision::GetCentroidY()
{
	Util::Log("Centroid Y", m_centroidY);
	return m_centroidY;
}
