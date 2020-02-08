/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "../CameraSubsystemBase.h"
#include "../../Constants.h"
class CameraSubsystemRocky :  public CameraSubsystemBase
{
 public:
  CameraSubsystemRocky();
 
  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  
  virtual int GetLeftMin() { return 10;}
  virtual int GetLeftMax() { return 250;}
  virtual int GetCenterMin() { return 250;}
  virtual int GetCenterMax() { return 350;}
  virtual int GetRightMin() { return 350;}
  virtual int GetRightMax() { return 640;}
  virtual int GetMaxResolutionX() { return 640;}
  virtual int GetMaxResolutionY() { return 480;}
  virtual void SetColor();
  void Periodic();

  

  private:
  
  
  
  protected:
  void InterlizeCamera(int port);
  void IntakeFrame();
  void FilterFrame();
  void CenterMomment();
  void PrintTurn(int turn);
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
};
