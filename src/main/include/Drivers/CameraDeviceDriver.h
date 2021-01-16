/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <cameraserver/CameraServer.h>
#include <opencv/cxcore.h>
#include <opencv2/imgproc/imgproc.hpp>

class CameraDeviceDriver {
 public:
  CameraDeviceDriver(int index);
  bool Init();
  void DisplayCamera();

  cv::Mat m_frame;
  cs::UsbCamera m_USBcamera;
  //cv::VideoCapture m_CVcamera;
  int m_index;
};
