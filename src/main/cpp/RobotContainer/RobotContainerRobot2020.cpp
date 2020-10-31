/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "../include/RobotContainer/RobotContainerRobot2020.h"
#include <frc2/command/button/JoystickButton.h>
#include "../include/Drivers/DPDTSwitchDriver.h"
#include <frc/DriverStation.h>

SpinSubsystemRobot2020::FMSColors RobotContainerRobot2020::givenColor = SpinSubsystemRobot2020::FMSColors::INVALID;


RobotContainerRobot2020::RobotContainerRobot2020()
{
  m_pDrive = new DriveTrainSubsystemRobot2020;
  m_pLoader = new LoaderSubsystemRobot2020;
  m_pSpin = new SpinSubsystemRobot2020;
  m_pShooter = new ShooterSubsystemRobot2020;
  m_pArm = new ArmSubsystemRobot2020;

  //Sensors
  m_pMuxLeftDistance = new MuxDistanceSensorDriver((Rev2mDistanceSensor::Port)I2C_ADDR_LEFTDISTANCESENSOR_ROBOT2020, *m_pMultiplexerDriver, U8T_LINE_LEFTDISTANCESENSOR_ROBOT2020);
  m_pMuxRightDistance = new MuxDistanceSensorDriver((Rev2mDistanceSensor::Port)I2C_ADDR_RIGHTDISTANCESENSOR_ROBOT2020, *m_pMultiplexerDriver, U8T_LINE_RIGHTDISTANCESENSOR_ROBOT2020);

  //m_pCamera = new CameraSubsystemBase(m_pDrive);

  m_pShootLoad = new ShootLoadCommand(m_pLoader, m_pShooter, m_encoderSpeedWanted, m_motorSpeed);
  //SpinWithArm Commands
  m_pSpinMotor = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinMotor, m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinWithColor = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinWithColor, m_speed, m_wantedRotation, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinToColor = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinToColor, m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinMotorOpp = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinMotor, -m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pSpinStop = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseSpinStop, m_speed, 0, ArmSubsystemBase::ArmPositions::INVALID_POS);
  m_pArmDown = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseArm, 0, 0, ArmSubsystemBase::ArmPositions::LOWEST_POS);
  m_pArmUp = new SpinWithArm(m_pArm, m_pSpin, SpinWithArm::SpinSelector::UseArm, 0, 0, ArmSubsystemBase::ArmPositions::HIGHEST_POS);

  // Configure the button bindings
  ConfigureButtonBindings();
  m_pDrive->Init();
  //if(m_pCamera!=nullptr)m_pCamera->Init();
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


int RobotContainerRobot2020::ReadDioSwitch()
{
   //Object hooked up to double pole double throw switch driver {Channel A, Channel B}
  /*
  //Uncomment these two lines out to enable DioSwitch
  DPDTSwitchDriver dpdtSwitch{2,3};
  return dpdtSwitch.Get();
  */
  int changeOneTwoThree = 1;
  return changeOneTwoThree;
}


frc2::Command* RobotContainerRobot2020::GetAutonomousCommand()
 {
  int dioAutoSwitcher;
  dioAutoSwitcher = ReadDioSwitch();
  frc::SmartDashboard::PutBoolean("Case 1", false);
  frc::SmartDashboard::PutBoolean("Case 2", false);
  frc::SmartDashboard::PutBoolean("Case 3", false);
  frc::SmartDashboard::PutBoolean("Case Default", false);
  switch(dioAutoSwitcher)
  {
    case 1:
    frc::SmartDashboard::PutBoolean("Case 1", true);
      return &m_autoInFrontTargetZone;
      break;

    case 2:
      frc::SmartDashboard::PutBoolean("Case 2", true);
      return &m_autoBetweenTargetZoneLoadingZone;
    case 3:
      frc::SmartDashboard::PutBoolean("Case 3", true);
      return &m_autoInFrontLoadingZone;
      break;
    default:
      frc::SmartDashboard::PutBoolean("Case Default", true);
      //return &m_autoInFrontTargetZone;
      break;
  }
  return nullptr;
}


void RobotContainerRobot2020::Init()
{
  if(m_pSpin != nullptr) m_pSpin->InterpretFMS(ReadFMS());
  m_pDrive->Init();
  if(m_pLoader != nullptr) m_pLoader->SetLoadMotor(0.0);
  m_pLoader->Init();
  frc::SmartDashboard::PutBoolean("Is Enabled", true);
  m_pShooter->Init();
  m_pMuxLeftDistance->Init(true);
  m_pMuxRightDistance->Init(true);

}


void RobotContainerRobot2020::DisableInit()
{
  if(m_pLoader != nullptr) m_pLoader->SetLoadMotor(0.0);
  m_pShooter->Init();
  frc::SmartDashboard::PutBoolean("Is Enabled", false);
  m_pMuxLeftDistance->Init(false);
  m_pMuxRightDistance->Init(false);
}


void RobotContainerRobot2020::SetButtonA()
{
  frc2::Button buttonAOne{[this] {return m_controller.GetAButton();}};
  buttonAOne.WhileHeld(&m_loaderFeed);  
  buttonAOne.WhenReleased(&m_loaderFeedStop);
  
  frc2::Button buttonATwo{[this] {return m_controller2.GetAButton();}};
  //buttonATwo.WhenPressed(&m_armPosition_High);  
  buttonATwo.WhenPressed(m_pArmDown);

  //buttonATwo.WhenHeld(&m_armPosition_High);  
  //buttonATwo.WhenReleased(&m_armPosition_Stop);
}


void RobotContainerRobot2020::SetButtonB()
{
  frc2::Button buttonBOne{[this] {return m_controller.GetBButton();}};
  buttonBOne.WhenHeld(&m_loaderAllIntake);
  buttonBOne.WhenReleased(&m_loaderAllStop);
  
  frc2::Button buttonBTwo{[this] {return m_controller2.GetBButton();}};
  //buttonBTwo.WhenPressed(&m_armPosition_Low);  
  buttonBTwo.WhenPressed(m_pArmUp);  

  //buttonBTwo.WhenHeld(&m_armPosition_Low);  
  //buttonBTwo.WhenReleased(&m_armPosition_Stop);
}


void RobotContainerRobot2020::SetButtonX()
{
  frc2::Button buttonXOne{[this] {return m_controller.GetXButton();}};
  buttonXOne.WhenHeld(&m_loaderMiddle);
  buttonXOne.WhenReleased(&m_loaderMiddleStop);

  frc2::Button buttonXTwo{[this] {return m_controller2.GetXButton();}};
  buttonXTwo.WhenPressed(m_pSpinMotor);
  //buttonXTwo.WhileHeld(m_pSpinMotor);
  //buttonXTwo.WhenHeld(m_pSpinMotor);

  buttonXTwo.WhenReleased(m_pSpinStop);
}


void RobotContainerRobot2020::SetButtonY()
{
  frc2::Button buttonYOne{[this] {return m_controller.GetYButton();}};
  buttonYOne.WhenHeld(&m_loaderTop);
  buttonYOne.WhenReleased(&m_loaderTopStop);

  frc2::Button buttonYTwo{[this] {return m_controller2.GetYButton();}};
  buttonYTwo.WhenPressed(m_pSpinMotorOpp);
  //buttonYOne.WhileHeld(m_pSpinMotorOpp);
  //buttonYTwo.WhenHeld(m_pSpinMotorOpp);
  
  buttonYTwo.WhenReleased(m_pSpinStop);
}


void RobotContainerRobot2020::SetRightTrigger()
{
  frc2::Button buttonRTOne{[this] {return m_controller.GetTriggerAxis(frc::GenericHID::kRightHand);}};
  buttonRTOne.WhenPressed(&m_shooterSpin);
  buttonRTOne.WhenReleased(&m_shooterStop);
  //m_shooterSpin;

/*
  frc2::Button buttonRTTwo{[this] {return m_controller2.GetTriggerAxis(frc::GenericHID::kRightHand);}};
  buttonRTTwo.(m_pSpinWithColor);*/
}


void RobotContainerRobot2020::SetLeftBumper()
{
  frc2::Button buttonLBOne{[this] {return m_controller.GetBumper(frc::GenericHID::kLeftHand);}};
  buttonLBOne.WhenPressed(&m_shooterEncoderReset);
  buttonLBOne.WhenReleased(&m_shooterEncoderReset);

  frc2::Button buttonLBTwo{[this] {return m_controller2.GetBumper(frc::GenericHID::kLeftHand);}};
  buttonLBTwo.WhenPressed(m_pShootLoad);
}


void RobotContainerRobot2020::SetRightBumper()
{
  frc2::Button buttonRBOne{[this] {return m_controller.GetBumper(frc::GenericHID::kRightHand);}};
  buttonRBOne.WhenHeld(&m_loaderSetInverted);
  buttonRBOne.WhenReleased(&m_loaderResetInverted);

  frc2::Button buttonRBTwo{[this] {return m_controller2.GetBumper(frc::GenericHID::kRightHand);}};
  buttonRBTwo.WhenHeld(&m_loaderPhotogate);
  buttonRBTwo.WhenReleased(&m_loaderAllStop);
}


void RobotContainerRobot2020::SetStartButton()
{
  frc2::Button startButtonOne{[this] {return m_controller.GetStartButton();}};
  startButtonOne.WhenPressed(&m_shooterSpinMax);
  startButtonOne.WhenReleased(&m_shooterStop);

  frc2::Button startButttonTwo{[this] {return m_controller2.GetStartButton();}};
  startButttonTwo.WhenPressed(&m_armLift_Motor);
  startButttonTwo.WhenReleased(&m_armStop);
}


void RobotContainerRobot2020::SetBackButton()
{
  frc2::Button backButtonOne{[this] {return m_controller.GetBackButton();}};
  
  backButtonOne.WhenPressed(&m_shooterSpinHalf);
  backButtonOne.WhenReleased(&m_shooterStop);
  //backButton.WhenPressed(m_pShootLoad);

  frc2::Button backButttonTwo{[this] {return m_controller2.GetBackButton();}};
  backButttonTwo.WhenPressed(&m_armLower_Motor);
  backButttonTwo.WhenReleased(&m_armStop);
}

void RobotContainerRobot2020::AutonomousPeriodic()
{
  //always getting distance from distance sensor. Change later so that they are only getting data when turning
  m_pMuxLeftDistance->GetDistance();
  m_pMuxRightDistance->GetDistance();
}

// Working as of 2/19/2020


void RobotContainerRobot2020::TeleopPeriodic()
{
  std::string gameData;
  gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if(gameData.length() > 0)
  {
    switch (gameData[0])
    {
      case 'B' :
        givenColor = SpinSubsystemRobot2020::FMSColors::BLUE;
        Util::Log("FMSColor", givenColor);
        //Blue case code
        break;
      case 'G' :
        givenColor = SpinSubsystemRobot2020::FMSColors::GREEN;
        Util::Log("FMSColor", givenColor);
        //Green case code
        break;
      case 'R' :
        givenColor = SpinSubsystemRobot2020::FMSColors::RED;
        Util::Log("FMSColor", givenColor);
        //Red case code
        break;
      case 'Y' :
        givenColor = SpinSubsystemRobot2020::FMSColors::YELLOW;
        Util::Log("FMSColor", givenColor);
        //Yellow case code
        break;
      default :
        givenColor = SpinSubsystemRobot2020::FMSColors::INVALID;
        Util::Log("FMSColor", givenColor);
        //This is corrupt data
        break;
    }
  } else {
    //Code for no data received yet
  }
}

