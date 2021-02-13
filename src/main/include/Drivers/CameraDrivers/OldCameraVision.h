#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "../../Constants.h"
#include <cameraserver/CameraServer.h>


class OldCameraVision
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="index"> 0 = webcam, 1 = USB camera </param>
	OldCameraVision(int index);

	/// <summary>
	/// Initialize Hardware
	/// </summary>
	/// <returns>
	///		true = initialization successful
	///		false = error occured
	/// </returns>
	bool Init();

	/// <summary>
	/// Which direction should the robot turn and how fast
	/// </summary
	/// 
	/// <returns>
	///		range is -1.0 to +1.0, negative value is turn left
	/// </returns>
	double WhereToTurn( double deadZoneLocation = 0.0, int deadZoneRange = 100);

	enum VisionColors{INVALID_COLOR, RED_CONE, GREEN_CONE, YELLOW_CONE, ORANGE_CONE, YELLOW_LEMON, PURPLE_BOTTLE, FMS_COLOR};

	void Tick();
	
	void SetHigh(int HSV, int value);
	void SetLow(int HSV, int value);

	void SetFMSColor(VisionColors color);

	void SetLookingColor(VisionColors color);
	VisionColors GetLookingColor();

private:
 	int m_frameCounter = 0;

	// const int LOWH_GREEN_CONE  = 38;
	// const int HIGHH_GREEN_CONE  = 79;
	// const int LOWS_GREEN_CONE  = 127;
	// const int HIGHS_GREEN_CONE  = 255;
	// const int LOWV_GREEN_CONE = 123;
	// const int HIGHV_GREEN_CONE = 255;

	// const int LOWH_RED_CONE  = 0;
	// const int HIGHH_RED  = 6;
	// const int LOWS_RED  = 134;
	// const int HIGHS_RED  = 255;
	// const int LOWV_RED  = 120;
	// const int HIGHV_RED  = 255;

	const cv::Scalar GREEN_CONE_LOW{30, 107, 103}; // 2/12/2021 Time 2:37PM
	const cv::Scalar GREEN_CONE_HIGH{79,255,255};
	const cv::Scalar RED_CONE_LOW{3,180,100};
	const cv::Scalar RED_CONE_HIGH{10,255,255};
	const cv::Scalar YELLOW_CONE_LOW{24, 50,150};
	const cv::Scalar YELLOW_CONE_HIGH{32,130,255};
	const cv::Scalar ORANGE_CONE_LOW{0,76,255};
	const cv::Scalar ORANGE_CONE_HIGH{21,255,255};
	const cv::Scalar YELLOW_LEMON_LOW{18, 190, 200};
	const cv::Scalar YELLOW_LEMON_HIGH{42, 255, 255};
	const cv::Scalar PURPLE_BOTTLE_LOW{145, 0, 0};
	const cv::Scalar PURPLE_BOTTLE_HIGH{179, 255, 255};

	const cv::Scalar BLUE_TEAMSHIRT_LOW{50, 50, 100};
	const cv::Scalar BLUE_TEAMSHIRT_HIGH{100, 255, 255};

	const std::string IMAGE_FILTERED = "Filtered";
	const std::string IMAGE_THRESHOLD = "Threshold";

	cv::Scalar FMS_HIGH{179, 255, 255};
	cv::Scalar FMS_LOW{0, 0, 0};

	const double OUT_OF_CAMERA_RANGE = -3.0;

	//Values that it is filtering by
	// int m_iLowH = LOWH_GREEN_CONE;
	// int m_iHighH = HIGHH_GREEN_CONE;
	// int m_iLowS = LOWS_GREEN_CONE;
	// int m_iHighS = HIGHS_GREEN_CONE;
	// int m_iLowV = LOWV_GREEN_CONE;
	// int m_iHighV = HIGHV_GREEN_CONE;

	//The index/port of the camera - given in the constructor
	int m_index;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//How big is the dead zone where WhereToTurn() = 0.0
	//double m_deadZone = 50.0;

	//VisionColors m_visionColor = FMS_COLOR;
	VisionColors m_visionColor = FMS_COLOR;
	//Holds the camera and raw image
	cv::Mat m_frame; 
	cv::Mat m_imgHSV;
	cv::Mat m_imgThresholded;
	cv::Mat m_imgThresholdedTwo;
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStream;
	cs::CvSource m_outputStreamTwo;

	/// <summary>
	/// Create a new window to display an image
	/// </summary>
	/// <param name="title">String of what the window is called</param>
	/// <param name="frame">The image that should be displayed</param>
	void SendImage(std::string title, cv::Mat frame/*, int width, int height*/);

	/// <summary>
	/// Find the blob on the image
	/// </summary>
	/// <returns>True - The image is fine  False - The image is empty </returns>
	bool GetBlob(int deadZonePixel);

	/// <summary>
	/// Filters the image and gets the position of its center
	/// </summary>
	void SetColor();

	bool GrabFrame();
};

