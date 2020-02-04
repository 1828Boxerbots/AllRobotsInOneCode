/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class SpinSubsystemBase : public frc2::SubsystemBase {
 public:
  SpinSubsystemBase();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();
  void SpinWithEncoders(double R, double r, double revolutions = 4.0);
  void SpinUntilColor(int targetColor);
  int Map(int color);
  virtual void Init() {};
  virtual int ReadColorSensor() {return m_color;};
  virtual void SetSpinMotor (double speed = 1.0) {}
  virtual double GetNumberOfTicks(double R, double revolutions, double r); //inches
  virtual double GetEncoderTicks() {return m_encoder++;}
  void Log();

 protected:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.

  const double COLORWHEELRADIUS = 16; //inches
  double SPINWHEELRADIUS = 3; //unknown
  double m_encoder = 1;
  int m_color = RED;

  // These are typed this way because this is how they appear on the field piece
  const int RED = 0;
  const int GREEN = 1;
  const int BLUE = 2;
  const int YELLOW = 3;
};
