#pragma once

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "../Constants.h"
#include <cameraserver/CameraServer.h>


class CameraVision
{
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="index"> 0 = webcam, 1 = USB camera </param>
	CameraVision(int index);

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
	double WhereToTurn(double deadZone);

	void Tick();

private:

	//Values that it is filtering by
	int m_iLowH = LOWH_RED;
	int m_iHighH = HIGHH_RED;
	int m_iLowS = LOWS_RED;
	int m_iHighS = HIGHS_RED;
	int m_iLowV = LOWV_RED;
	int m_iHighV = HIGHV_RED;

	//The index/port of the camera - given in the constructor
	int m_index;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//How big is the dead zone where WhereToTurn() = 0.0
	double m_deadZone = 50.0;

	//Holds the camera and raw image
	cv::Mat m_frame;
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStream;

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
	bool GetBlob();

	/// <summary>
	/// Filters the image and gets the position of its center
	/// </summary>
	void SetColor();

};
