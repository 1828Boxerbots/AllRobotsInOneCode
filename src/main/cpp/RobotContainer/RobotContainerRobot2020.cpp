/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRobot2020.h"
#include <frc2/command/button/JoystickButton.h>

RobotContainerRobot2020::RobotContainerRobot2020()
{
  m_pDrive = new DriveTrainSubsystemRobot2020;
  m_pLoader = new LoaderSubsystemRobot2020;
  m_pSpin = new SpinSubsystemRobot2020;
  m_pShooter = new ShooterSubsystemRobot2020;
  //m_pCamera = new CameraSubsystemBase;
  m_pArm = new ArmSubsystemRobot2020;
  //m_pDistance = new DistanceSensorSubsystemRobot2020;
  m_pShootLoad = new ShootLoadCommand(m_pLoader, m_pShooter, 5400, 1.0);

  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  SetDrive();
}

void RobotContainerRobot2020::ConfigureButtonBindings()
{
  //Robot2020

  //Loader
  SetButtonA();
  SetButtonB();
  SetButtonX();
  SetButtonY();

  SetRightBumper();

  //Shooter
  SetRightTrigger();
  SetStartButton();
  SetBackButton();

  //Shooter Encoder
  SetLeftBumper();

}

frc2::Command* RobotContainerRobot2020::GetAutonomousCommand() {
  // An example command will be run in autonomous
  return 0;
}

void RobotContainerRobot2020::Init()
{
  if(m_pSpin != nullptr) m_pSpin->InterpretFMS(ReadFMS());
  m_pDrive->Init();
  if(m_pLoader != nullptr) m_pLoader->SetLoadMotor(0.0);
  m_pLoader->Init();
  frc::SmartDashboard::PutBoolean("Is Enabled", true);
  m_pShooter->Init();
}

void RobotContainerRobot2020::DisableInit()
{
  if(m_pLoader != nullptr) m_pLoader->SetLoadMotor(0.0);
  m_pShooter->Init();
  frc::SmartDashboard::PutBoolean("Is Enabled", false);
}

void RobotContainerRobot2020::SetButtonA()
{
  frc2::Button buttonAOne{[this] {return m_controller.GetAButton();}};
  buttonAOne.WhileHeld(&m_loaderFeed);  
  buttonAOne.WhenReleased(&m_loaderFeedStop);
  
  frc2::Button buttonATwo{[this] {return m_controller2.GetAButton();}};
  buttonATwo.WhenPressed(&m_armPosition1);  
}

void RobotContainerRobot2020::SetButtonB()
{
  frc2::Button buttonB{[this] {return m_controller.GetBButton();}};
  buttonB.WhenHeld(&m_loaderAllIntake);
  buttonB.WhenReleased(&m_loaderAllStop);
  
  frc2::Button buttonBTwo{[this] {return m_controller2.GetBButton();}};
  buttonBTwo.WhenPressed(&m_armPosition0);  
}

void RobotContainerRobot2020::SetButtonX()
{
  frc2::Button buttonX{[this] {return m_controller.GetXButton();}};
  buttonX.WhenHeld(&m_loaderMiddle);
  buttonX.WhenReleased(&m_loaderMiddleStop);

  frc2::Button buttonXTwo{[this] {return m_controller2.GetXButton();}};
  buttonXTwo.WhenHeld(&m_spinHoldN);
  buttonXTwo.WhenReleased(&m_spinStop);
}

void RobotContainerRobot2020::SetButtonY()
{
  frc2::Button buttonY{[this] {return m_controller.GetYButton();}};
  buttonY.WhenHeld(&m_loaderTop);
  buttonY.WhenReleased(&m_loaderTopStop);

  frc2::Button buttonYTwo{[this] {return m_controller2.GetYButton();}};
  buttonYTwo.WhenHeld(&m_spinHoldP);
  buttonYTwo.WhenReleased(&m_spinStop);
}

void RobotContainerRobot2020::SetRightTrigger()
{
  frc2::Button buttonRT{[this] {return m_controller.GetTriggerAxis(frc::GenericHID::kRightHand);}};
  buttonRT.WhenPressed(&m_shooterSpin);
  buttonRT.WhenReleased(&m_shooterStop);
  //m_shooterSpin;
}

void RobotContainerRobot2020::SetLeftBumper()
{
  frc2::Button buttonLB{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
  buttonLB.WhenPressed(&m_shooterEncoderReset);
  buttonLB.WhenReleased(&m_shooterEncoderReset);
}

void RobotContainerRobot2020::SetRightBumper()
{
  frc2::Button buttonRB{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
  buttonRB.WhenHeld(&m_loaderSetInverted);
  buttonRB.WhenReleased(&m_loaderResetInverted);
}

void RobotContainerRobot2020::SetStartButton()
{
  frc2::Button startButton{[this] {return m_controller.GetStartButton();}};
  startButton.WhenPressed(&m_shooterSpinMax);
  startButton.WhenReleased(&m_shooterStop);
}

void RobotContainerRobot2020::SetBackButton()
{
  frc2::Button backButton{[this] {return m_controller.GetBackButton();}};
  /*
  backButton.WhenPressed(&m_shooterSpinHalf);
  backButton.WhenReleased(&m_shooterStop);
  */
  backButton.WhenPressed(m_pShootLoad);
}

// Working as of 2/19/2020
