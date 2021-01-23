#pragma once
#include "WindowsVisionBase.h"
#include <cameraserver/CameraServer.h>
#include "Util.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

class RobotVision : public WindowsVisionBase
{
public:
	RobotVision(int port);
	bool Init() override;
	void Tick() override;
    void Log(std::string title, std::string value) override;
private:
	void SendImage(std::string title, cv::Mat frame) override;
    bool GetImage() override;

	//The points that hold the center of blob
	double m_centroidX;
	double m_centroidY;

	//How big is the dead zone where WhereToTurn() = 0.0
	double m_deadZone = 50.0;

	//Holds the camera and raw image
	cs::UsbCamera m_camera;
	cs::CvSink m_cvSink;
	cs::CvSource m_outputStreamLine;
	cs::CvSource m_outputStreamThreshold;
	cs::CvSource m_outputStreamHSV;

	//Values that it is filtering by
	int m_iLowH = LOWH_GREEN_CONE;
	int m_iHighH = HIGHH_GREEN_CONE;
	int m_iLowS = LOWS_GREEN_CONE;
	int m_iHighS = HIGHS_GREEN_CONE;
	int m_iLowV = LOWV_GREEN_CONE;
	int m_iHighV = HIGHV_GREEN_CONE;
};

