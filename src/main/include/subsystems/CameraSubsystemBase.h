/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <opencv2/core.hpp>
#include <opencv2/cvconfig.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <frc/smartdashboard/SmartDashboard.h>
#include "../Constants.h"
using namespace cv;

class CameraSubsystemBase : public frc2::SubsystemBase {
 public:
  CameraSubsystemBase();

  void Init();
  int WhereToTurn();
  void Tick();

protected:
  void InterlizeCamera(int port);
  void IntakeFrame();
  void FilterFrame();
  void CenterMomment();
  void PrintTurn(int turn);
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  int m_frameNumber = 1;

  Mat m_frame;
  Mat m_morp = cv::getStructuringElement(MORPH_CROSS, Size(3, 3), Point(-1, 1));
  VideoCapture m_video;
  Mat m_output;
  Mat m_colorFilter;
  Mat m_closeFilter;
  Mat m_openFilter;
  cv::Moments m_moment;
  cv::Point m_center;
};
