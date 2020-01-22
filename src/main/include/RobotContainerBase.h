/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>
#include <frc/XboxController.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/InstantCommand.h>
#include "Constants.h"

class RobotContainerBase {
 public:
  RobotContainerBase();

  protected:
    //Creating the controllers
    frc::XboxController m_controller{USB_CONTROLLER_ONE};
    frc::XboxController m_controller2{USB_CONTROLLER_TWO};
    //DriveTrainSubsystemBase *m_pDrive;

   /* frc2::RunCommand m_driveTrainMoveTank {[this] 
    { 
        if (m_pDrive) m_pDrive->MoveTank(m_controller.GetY(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kRightHand));
    }, {m_pDrive}};*/
};
