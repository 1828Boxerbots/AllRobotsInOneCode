// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/RecordMove.h"

RecordMove::RecordMove(const RecordMove& orig) 
{
  m_isFinished = orig.m_isFinished;
  m_pDrive = orig.m_pDrive;
  m_pController = orig.m_pController;

  m_plogfile = orig.m_plogfile;
  m_precordfile = orig.m_precordfile;
}

RecordMove::RecordMove(DriveTrainSubsystemBase *pDrive, frc::XboxController *pController)
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_pController = pController;

  m_pDrive = pDrive;
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void RecordMove::Initialize()
{
  m_plogfile = new std::ofstream;

  m_plogfile->open(LOG_FILE);

  char filename[2560];
  std::string time = Util::TimeStampStr();
  Util::Log("Recode Time", time);
  sprintf(filename, "/u/c418_recording/recording_%s.bin", time.c_str());
  Util::Log("Record File Name", filename);
  m_precordfile = new std::ofstream;
  m_precordfile->open(filename, std::ios::out | std::ios::app | std::ios::binary);

  if(m_plogfile->is_open())
  {
    *m_plogfile << "Recording File = " << filename << "\n";
  }
}

// Called repeatedly when this Command is scheduled to run
void RecordMove::Execute()
{

  double left = -m_pController->GetY(frc::GenericHID::kLeftHand);
  double right = m_pController->GetX(frc::GenericHID::kRightHand);
  m_pDrive->MoveArcade(left, right);

  *m_plogfile << Util::TimeStampStr() << " Left = " << left << " Right = " << right << std::endl;

  RecordingStructure record;
  record.m_left = float(left);
  record.m_right = float(right);
  if(m_precordfile->is_open())
  {
    m_precordfile->write( (char*)&record, sizeof(RecordingStructure) );
  }
}

// Called once the command ends or is interrupted.
void RecordMove::End(bool interrupted) {}

// Returns true when the command should end.
bool RecordMove::IsFinished() {
  return false;
}
