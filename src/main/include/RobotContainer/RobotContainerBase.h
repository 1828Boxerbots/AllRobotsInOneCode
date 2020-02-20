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
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/WaitUntilCommand.h>
#include <frc2/command/WaitCommand.h>
#include <frc/DriverStation.h>

#include "Constants.h"
#include "subsystems/DriveTrainSubsystemBase.h"
#include "subsystems/LoaderSubsystemBase.h"
#include "subsystems/ShooterSubsystemBase.h"
#include "subsystems/DistanceSensorSubsystemBase.h"
#include "subsystems/CameraSubsystemBase.h"
#include "subsystems/ArmSubsystemBase.h"
#include "subsystems/SpinSubsystemBase.h"

#ifdef xxx
#include "subsystems/LipALoop/WristSubsystemLipALoop.h"
#include "subsystems/LipALoop/HandSubsystemLipALoop.h"
#endif // #ifdef xxx
#include "subsystems/Rocky/TurretSubsystemRocky.h"

class RobotContainerBase {
 public:
  RobotContainerBase();

  virtual void SetButtonA();
  virtual void SetButtonB();
  virtual void SetButtonX();
  virtual void SetButtonY();
  virtual void SetStartButton();
  virtual void SetBackButton();
  virtual void SetLeftBumper();
  virtual void SetRightBumper();
  virtual void SetLeftTrigger();
  virtual void SetRightTrigger();
  virtual void Init() = 0;
  virtual void DisableInit() = 0;
  bool GetRightBumper() {return m_controller.GetBumper(frc::GenericHID::JoystickHand::kRightHand);};
  std::string ReadFMS() {return frc::DriverStation::GetInstance().GetGameSpecificMessage();}

  enum DriveStyles
  {
    TANK_STYLE,
    ARCADE_STYLE
    //,WESTCOAST_STYLE
  };

  double LOAD = 1.0;
  double EJECT = -1.0;
  double STOP = 0.0;
  double ROBOT2020SPEEDLIMIT = 0.5;

  void SetDrive(DriveStyles style = TANK_STYLE);

  protected:
  //DriveTrainSubsystemBase m_driveTrain;
    //Creating the controllers
    frc::XboxController m_controller{USB_CONTROLLER_ONE};
    frc::XboxController m_controller2{USB_CONTROLLER_TWO};
    CameraSubsystemBase* m_pCamera = nullptr;

    DistanceSensorSubsystemBase *m_pDistance = nullptr;
    //DriveTrain subsystem commands
    DriveTrainSubsystemBase *m_pDrive = nullptr;
    frc2::RunCommand m_driveMoveTank       {[this] { if(m_pDrive != nullptr) m_pDrive->MoveTank(m_controller.GetY(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kRightHand)); }, {m_pDrive}};
    frc2::RunCommand m_driveMoveArcade     {[this] { if(m_pDrive != nullptr) m_pDrive->MoveArcade(m_controller.GetX(frc::GenericHID::kLeftHand), m_controller.GetY(frc::GenericHID::kLeftHand)); }, {m_pDrive}};
    frc2::InstantCommand m_driveGyroInit   {[this] {if(m_pDrive != nullptr)   m_pDrive->GyroInit();}, {m_pDrive}};
    frc2::InstantCommand m_driveInit       {[this] { if(m_pDrive != nullptr)   m_pDrive->Init();}, {m_pDrive}};
    frc2::InstantCommand m_driveEnableAntiCollision {[this] {if(m_pDrive != nullptr)   m_pDrive->EnableAnticollision();}, {m_pDrive}};
    frc2::InstantCommand m_driveForward12In0Deg     {[this] {if(m_pDrive != nullptr)   m_pDrive->ForwardInInch(12, 0.0, 0.75);}, {m_pDrive}};
    frc2::InstantCommand m_driveTurnLeft90Deg       {[this] {if(m_pDrive != nullptr)   m_pDrive->TurnInDegrees(-90);}, {m_pDrive}};
    frc2::InstantCommand m_driveForward24in90Deg    {[this] {if(m_pDrive != nullptr)   m_pDrive->ForwardInInch(24, -90.0, 0.75);}, {m_pDrive}};
    frc2::InstantCommand m_driveStop                {[this] {if(m_pDrive != nullptr)   m_pDrive->Stop();}, {m_pDrive}};

    // Loader subsystem commands
    LoaderSubsystemBase *m_pLoader = nullptr;
    //Every Other Robot
    frc2::RunCommand m_loaderEject          {[this] { if(m_pLoader!=nullptr) m_pLoader->LoadMotor(-1.0);}, {m_pLoader}};
    frc2::RunCommand m_loaderLoad           {[this] { if(m_pLoader!=nullptr) m_pLoader->LoadMotor(1.0);}, {m_pLoader}};
    frc2::RunCommand m_loaderStop           {[this] { if(m_pLoader!=nullptr) m_pLoader->LoadMotor(0.0);}, {m_pLoader}};
    
    //Robot2020
    frc2::RunCommand m_loaderFeed           {[this] {
      if (GetRightBumper())
      {
          if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(EJECT, 2); 
      } 
      else 
      {
        if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(LOAD, 2);
      }
    }, {m_pLoader}};
    frc2::RunCommand m_loaderMiddle           {[this] {
      if (GetRightBumper())
      {
          if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(EJECT, 1); 
      } 
      else 
      {
        if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(LOAD, 1);
      }
    }, {m_pLoader}};
    frc2::RunCommand m_loaderTop             {[this] {
      if (GetRightBumper())
      {
          if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(EJECT, 0); 
      } 
      else 
      {
        if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(LOAD, 0);
      }
    }, {m_pLoader}};
    frc2::RunCommand m_loaderAllIntake           {[this] {
      if (GetRightBumper())
      {
          if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(EJECT); 
      } 
      else 
      {
        if (m_pLoader != nullptr) m_pLoader->SetLoadMotor(LOAD);
      }
    }, {m_pLoader}};

    frc2::RunCommand m_loaderFeedStop       {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(STOP, 2);}, {m_pLoader}};
    frc2::RunCommand m_loaderMiddleStop     {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(STOP, 1);}, {m_pLoader}};
    frc2::RunCommand m_loaderTopStop        {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(STOP, 0);}, {m_pLoader}};
    frc2::RunCommand m_loaderAllStop        {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(STOP);}, {m_pLoader}};

    frc2::RunCommand m_loaderAllEject       {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(-1.0);}, {m_pLoader}};
    frc2::RunCommand m_loaderMiddleEject    {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(-1.0, 1);}, {m_pLoader}};
    frc2::RunCommand m_loaderBottomEject    {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(-1.0, 2);}, {m_pLoader}};
    frc2::RunCommand m_loaderTopEject       {[this] { if(m_pLoader!=nullptr) m_pLoader->SetLoadMotor(-1.0, 0);}, {m_pLoader}};
    frc2::InstantCommand m_loaderLoadMax    {[this] { if(m_pLoader != nullptr) m_pLoader->SetLoadMotor(1.0);}, {m_pLoader}};
    frc2::InstantCommand m_loaderWait5      {[this] { if(m_pLoader != nullptr) m_pLoader->WaitLoader(5);}, {m_pLoader}};

    // Shooter subsystem commands
    ShooterSubsystemBase *m_pShooter = nullptr;
    frc2::RunCommand m_shooterSpin          {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(-m_controller.GetTriggerAxis(frc::GenericHID::kRightHand));}, {m_pShooter}};
    frc2::RunCommand m_shooterEject         {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(m_controller.GetTriggerAxis(frc::GenericHID::kRightHand));}, {m_pShooter}};
    frc2::RunCommand m_shooterStop          {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(0.0);}, {m_pShooter}};
    frc2::RunCommand m_shooterEncoderReset  {[this] { if(m_pShooter!=nullptr) m_pShooter->ResetEncoder();}, {m_pShooter}};
    frc2::RunCommand m_shooterSpinMax       {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(1.0);}, {m_pShooter}};
    frc2::RunCommand m_shooterSpinHalf      {[this] { if(m_pShooter!=nullptr) m_pShooter->Shoot(0.5);}, {m_pShooter}};
    frc2::InstantCommand m_shooterShootMax  {[this] { if(m_pShooter != nullptr) m_pShooter->Shoot(1.0);}, {m_pShooter}};
    frc2::InstantCommand m_shooterWait5     {[this] { if(m_pShooter != nullptr) m_pShooter->WaitShooter(5);}, {m_pShooter}};

    //TurretSubsystemBase *m_*pTurret = nullptr;
    TurretSubsystemRocky *m_pTurret = nullptr;
    frc2::RunCommand m_turretTurnLeft       {[this] { if (m_pTurret!=nullptr) m_pTurret->Turn(m_controller.GetAButton(), m_controller.GetBButton());}, {m_pTurret}};
    frc2::RunCommand m_turretTurnRight      {[this] { if (m_pTurret!=nullptr) m_pTurret->Turn(m_controller.GetAButton(), m_controller.GetBButton());}, {m_pTurret}};
    frc2::RunCommand m_turretStop           {[this] { if (m_pTurret!=nullptr) m_pTurret->Turn(false, false);}, {m_pTurret}};

    //Arm Control
    ArmSubsystemBase *m_pArm = nullptr;
    //LipALoop
    frc2::RunCommand m_armUp_Servo          {[this] { if(m_pArm != nullptr) m_pArm->LiftArmUp();}, {m_pArm}};
    frc2::RunCommand m_armDown_Servo        {[this] { if(m_pArm != nullptr) m_pArm->LiftArmDown();}, {m_pArm}};
    frc2::RunCommand m_armStop              {[this] { if(m_pArm != nullptr) m_pArm->StopMotor();}, {m_pArm}};
    //SLAL
    frc2::RunCommand m_armLift_Motor        {[this] {if(m_pArm != nullptr) m_pArm->Raise();}, {m_pArm}};
    frc2::RunCommand m_armLower_Motor       {[this] {if(m_pArm != nullptr) m_pArm->Lower();}, {m_pArm}};
    //Robot2020
    frc2::RunCommand m_armPosition0         {[this] {if(m_pArm != nullptr) m_pArm->SetPosition(ArmSubsystemBase::LOWEST_POS);}, {m_pArm}};
    frc2::RunCommand m_armPosition1         {[this] {if(m_pArm != nullptr) m_pArm->SetPosition(ArmSubsystemBase::HIGHEST_POS);}, {m_pArm}};
      //frc2::Runcommand m_armPosition_Stop     {[this] {if(m_pArm != nullptr) m_pArm->ArmPosition(3);}, {m_pArm}};

#ifdef xxx
    //Wrist Control
    WristSubsystemLipALoop *m_pWrist = nullptr;
    frc2::RunCommand m_wristUp              {[this] { if(m_pWrist != nullptr) m_pWrist->MoveWristUp();}, {m_pWrist}};
    frc2::RunCommand m_wristDown            {[this] { if(m_pWrist != nullptr) m_pWrist->MoveWristDown();}, {m_pWrist}};
    frc2::RunCommand m_wristStop            {[this] { if(m_pWrist != nullptr) m_pWrist->MoveWristStop();}, {m_pWrist}};

    //Hand Control
    HandSubsystemLipALoop *m_pHand = nullptr;
    frc2::RunCommand m_handUp               {[this] { if(m_pHand != nullptr) m_pHand->MoveHandOpen();}, {m_pHand}};
    frc2::RunCommand m_handDown             {[this] { if(m_pHand != nullptr) m_pHand->MoveHandClose();}, {m_pHand}};
    frc2::RunCommand m_handStop             {[this] { if(m_pHand != nullptr) m_pHand->MoveHandStop();}, {m_pHand}};
#endif // #ifdef xxx

    //Spin Control
    SpinSubsystemBase *m_pSpin = nullptr;
    frc2::RunCommand m_spinToColor          {[this] { if(m_pSpin != nullptr) m_pSpin->SpinUntilColor();}, {m_pSpin}};
    frc2::RunCommand m_spin                 {[this] { if(m_pSpin != nullptr) m_pSpin->SpinWithEncoders();}, {m_pSpin}};



  frc2::SequentialCommandGroup m_autoTestOne = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand{[this]
    { if(m_pDrive != nullptr && m_pDistance != nullptr) 
      {
        double travelDistance = 60.0;
        double tolerance = 2.0;
        double currentDistance = m_pDistance->GetDistanceInInch();
        while(currentDistance < travelDistance-tolerance || currentDistance > travelDistance+tolerance)
        {
          if(currentDistance > travelDistance)
          {
            m_pDrive->Forward(1.0);
          }
          else
          {
            m_pDrive->Forward(-1.0);
          }
          currentDistance = m_pDistance->GetDistanceInInch();
        }
        m_pDrive->Stop();
      }
    }, {m_pDrive, m_pDistance}}
  };

  frc2::SequentialCommandGroup m_autoInFrontTargetZone = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)    m_pDrive->GyroInit();}, {m_pDrive}},
    frc2::InstantCommand{  [this] {m_pDrive->Init();}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)    m_pDrive->EnableAnticollision();}},
    //frc2::InstantCommand{  [this] {if(m_pShooter != nullptr)  m_pDrive->ForwardInInch(12, 0.0, 0.75);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pShooter != nullptr)  m_pDrive->TurnInDegrees(180);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pShooter != nullptr)  m_pDrive->ForwardInInch(24, 180.0, 0.75);}, {m_pDrive}},
  
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pCamera->AutoCameraTurn();}, {m_pCamera}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr)  m_pShooter->Shoot(1.0);}, {m_pShooter}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr)  m_pShooter->WaitShooter(5);}, {m_pShooter}}, 
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)   m_pLoader->SetLoadMotor(1.0);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)   m_pLoader->WaitLoader(5);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)   m_pLoader->SetLoadMotor(0.0);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr)  m_pShooter->Shoot(0.0);}, {m_pShooter}},
    frc2::InstantCommand{[this] {m_pDrive->Stop();}, {m_pDrive}}
  };
  
  frc2::SequentialCommandGroup m_autoBetweenTargetZoneLoadingZone = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->GyroInit();}, {m_pDrive}},
    frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->Init();}, {m_pDrive}},
   // frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->EnableAnticollision();}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->ForwardInInch(12, 0.0, 0.75);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->TurnInDegrees(-70);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->ForwardInInch(24, -80.0, 0.75);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->TurnInDegrees(-70);}, {m_pDrive}},
    frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pCamera->AutoCameraTurn();}, {m_pCamera}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr) m_pShooter->Shoot(1.0);}, {m_pShooter}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr) m_pShooter->WaitShooter(5);}, {m_pShooter}}, 
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)  m_pLoader->SetLoadMotor(1.0);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)  m_pLoader->WaitLoader(5);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)  m_pLoader->SetLoadMotor(0.0);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr) m_pShooter->Shoot(0.0);}, {m_pShooter}},
    
    frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->Stop();}, {m_pDrive}}
  };
  frc2::SequentialCommandGroup m_autoInFrontLoadingZone = frc2::SequentialCommandGroup
  {
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->GyroInit();}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->Init();}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->ForwardInInch(12, 0.0, 0.75);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->TurnInDegrees(-90);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->ForwardInInch(72, -90.0, 0.75);}, {m_pDrive}},
    //frc2::InstantCommand{  [this] {if(m_pDrive != nullptr)   m_pDrive->TurnInDegrees(-90);}, {m_pDrive}},
    frc2::InstantCommand{  [this] {m_pCamera->AutoCameraTurn();}, {m_pCamera}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr) m_pShooter->Shoot(1.0);}, {m_pShooter}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr) m_pShooter->WaitShooter(5);}, {m_pShooter}}, 
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)  m_pLoader->SetLoadMotor(1.0);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)  m_pLoader->WaitLoader(5);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pLoader != nullptr)  m_pLoader->SetLoadMotor(0.0);}, {m_pLoader}},
    frc2::InstantCommand{  [this] {if(m_pShooter != nullptr) m_pShooter->Shoot(0.0);}, {m_pShooter}},
    
    frc2::InstantCommand{[this] {if(m_pDrive != nullptr) m_pDrive->Stop();}, {m_pDrive}}
  };
  frc2::SequentialCommandGroup m_follower = frc2::SequentialCommandGroup
  {
    frc2::InstantCommand {[this] {if(m_pCamera != nullptr)m_pCamera->Init();}, {m_pCamera}},
    frc2::InstantCommand{[this]
    {
      if(m_pCamera == nullptr || m_pDrive == nullptr)
      {
        return; 
      }
      int direction = m_pCamera->WhereToTurn(); 
      while(true)
      {
        m_pCamera->Tick();
        if (direction == 1)
        {
          m_pDrive->TurnRight(0.3);
          direction = m_pCamera->WhereToTurn(); 
        }
        else if (direction == -1)
        {
          m_pDrive->TurnLeft(0.3);
          direction = m_pCamera->WhereToTurn(); 
        }
        else
        {
          m_pDrive->Stop();
        }
        direction = m_pCamera->WhereToTurn(); 
      }
    }, {m_pCamera, m_pDrive}}
  };

  frc2::SequentialCommandGroup m_autoTitoTest = frc2::SequentialCommandGroup
  {
    m_driveInit,
    m_driveForward12In0Deg,
    m_driveStop
  };

};
