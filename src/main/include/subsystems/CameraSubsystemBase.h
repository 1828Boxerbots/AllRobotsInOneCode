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
#include <cameraserver/CameraServer.h>
#include "Constants.h"


using namespace cv;

class CameraSubsystemBase : public frc2::SubsystemBase {
 public:
  CameraSubsystemBase();

  void Init();
  int WhereToTurn();
  void Tick();
<<<<<<< Updated upstream
=======
  void CameraPeriodic();
  void setCenterWidth(int width) {m_centerWidth = width;}
>>>>>>> Stashed changes

  const int GO_LEFT = -1;
  const int GO_RIGHT = +1;
  const int STOP = 0;

  /*virtual int GetLeftMin() { return 0;}
  virtual int GetLeftMax() { return 250;}*/
  virtual int GetCenterMin() { return (m_frameWidth/2) - m_centerWidth;}
  virtual int GetCenterMax() { return (m_frameWidth/2) + m_centerWidth;}
  /*virtual int GetRightMin() { return 350;}
  virtual int GetRightMax() { return ;}*/
  virtual int GetMaxResolutionX() { return m_frameWidth;}
  virtual int GetMaxResolutionY() { return 480;}
  virtual void SetColor();

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
  VideoCapture m_video;

  int m_frameWidth = 0;
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  int m_centerWidth = 50;
  int m_frameNumber = 1;

  Mat m_frame;
  Mat m_morp = cv::getStructuringElement(MORPH_CROSS, Size(3, 3), Point(-1, 1));
  Mat m_output;
  Mat m_colorFiliter;
  //Mat closeFilter;
  //Mat m_output;
  Mat m_dilution;
  Mat m_openFilter;
  cv::Moments m_moment;
  cv::Point m_center;
  
  double m_printX;
  
};
