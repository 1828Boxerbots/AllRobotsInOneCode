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
#include "subsystems/DriveTrainSubsystemBase.h"



class CameraSubsystemBase : public frc2::SubsystemBase {
 public:
  CameraSubsystemBase(DriveTrainSubsystemBase *pDrive);

  void Init();
  int WhereToTurn();
  void Tick();
  void CameraPeriodic();

  const int GO_LEFT = -1;
  const int GO_RIGHT = +1;
  const int STOP = 0;
  const int CANT_FIND_IMAGE = -2;

  virtual int GetLeftMin() { return 10;}
  virtual int GetLeftMax() { return 250;}
  virtual int GetCenterMin() { return 250;}
  virtual int GetCenterMax() { return 350;}
  virtual int GetRightMin() { return 350;}
  virtual int GetRightMax() { return 640;}
  virtual int GetMaxResolutionX() { return 640;}
  virtual int GetMaxResolutionY() { return 480;}
  virtual void SetColor();
  void AutoCameraTurn();

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

  cv::Mat m_frame;
  cv::Mat m_morp = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3), cv::Point(-1, 1));
  cv::VideoCapture m_video;
  cv::Mat m_output;
  cv::Mat m_colorFilter;
  //Mat closeFilter;
  //Mat m_output;
  cv::Mat m_dilution;
  cv::Mat m_openFilter;
  cv::Moments m_moment;
  cv::Point m_center;

  #ifdef SEND_VIDEO
  int m_sendSizeWidth = 480;
  int m_sendSizeHeight = 640;
  int m_sendRectWidth = m_sendSizeWidth/2;
  int m_sendRectHeight = m_sendSizeHeight/2;
  cv::Mat m_sendFrame;
  cs::CvSink m_cvSink;
  cs::CvSource m_outputStream;
  #endif
  void SendImage();
  void InitSendImage();
  
  double m_printX;
  DriveTrainSubsystemBase *m_pDriveObject = nullptr;
  
};
