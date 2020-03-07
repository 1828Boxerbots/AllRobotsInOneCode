/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerBase.h"
#include <frc2/command/button/Button.h>

RobotContainerBase::RobotContainerBase() {}

void RobotContainerBase::SetCamerastream()
{
    

    frc::SmartDashboard::PutString("test","After set defelut");
}
void RobotContainerBase::SetDrive(DriveStyles driveStyle)
{
    switch (driveStyle)
    {
        case TANK_STYLE:
            m_pDrive->SetDefaultCommand(frc2::RunCommand(
            [this] 
            {
                m_pDrive->MoveTank(-m_controller.GetY(frc::GenericHID::kLeftHand), -m_controller.GetY(frc::GenericHID::kRightHand));
            }
            ,{m_pDrive}));
            break;

        case ARCADE_STYLE:
            m_pDrive->SetDefaultCommand(frc2::RunCommand(
            [this] 
            {
                m_pDrive->MoveArcade(m_controller.GetY(frc::GenericHID::kLeftHand), m_controller.GetX(frc::GenericHID::kLeftHand));
            }
            ,{m_pDrive}));
            break;
    }
}

void RobotContainerBase::SetButtonA()
{
    frc2::Button buttonA{[this] {return m_controller.GetAButton();}};
    buttonA.WhileHeld(&m_turretTurnLeft);
    buttonA.WhenReleased(&m_turretStop);
}

void RobotContainerBase::SetButtonB()
{
    frc2::Button buttonB{[this] {return m_controller.GetBButton();}};
    buttonB.WhenHeld(&m_turretTurnRight);
    buttonB.WhenReleased(&m_turretStop);
}

void RobotContainerBase::SetButtonX()
{
    frc2::Button buttonX{[this] {return m_controller.GetXButton();}};
    buttonX.WhenHeld(&m_loaderEject);
    buttonX.WhenReleased(&m_loaderStop);
}

void RobotContainerBase::SetButtonY()
{
    frc2::Button buttonY{[this] {return m_controller.GetYButton();}};
    buttonY.WhenHeld(&m_loaderLoad);
    buttonY.WhenReleased(&m_loaderStop);
}

void RobotContainerBase::SetStartButton()
{
    /*
    frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
    startButton.WhenPressed(&m_follower);
    */
}

void RobotContainerBase::SetBackButton()
{
    
}

void RobotContainerBase::SetLeftBumper()
{
    frc2::Button bumperL{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
    // Set the bottom back to eject eventually maybe
    bumperL.WhenHeld(&m_shooterSpin);
    bumperL.WhenReleased(&m_shooterStop);
}

void RobotContainerBase::SetRightBumper()
{
    frc2::Button bumperR{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
    bumperR.WhenHeld(&m_shooterSpin);
    bumperR.WhenReleased(&m_shooterStop);
}

void RobotContainerBase::SetLeftTrigger()
{
    //frc2::Button leftTrigger{[this] {return m_controller.GetTriggerAxis(frc::GenericHID::kLeftHand);}};
    //leftTrigger.WhenPressed(&m_resetEncoder);
}

void RobotContainerBase::SetRightTrigger()
{
    
}