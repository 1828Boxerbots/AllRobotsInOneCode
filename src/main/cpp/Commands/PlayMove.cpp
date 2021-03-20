// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/PlayMove.h"

PlayMove::PlayMove(DriveTrainSubsystemBase *pDrive, const char *pfilename) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_filename = pfilename;

  m_pDrive = pDrive;
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void PlayMove::Initialize() 
{
  m_logfile.open(LOG_FILE);
  if(m_logfile.is_open())
  {
    m_logfile << "Looking File = " << m_filename << "\n";
  }

  m_inputFile.open(m_filename, std::ios::in | std::ios::binary);

  //Get length of the recorded file
  m_inputFile.seekg(0, std::ios::end);
  m_filelength = m_inputFile.tellg();

  m_logfile << "File: " << m_filename << " Length of file: " << m_filelength << std::endl;

  //Go back to beginning we are at the end of the file
  m_inputFile.seekg(0, std::ios::beg);

  //Allocate memory
  m_pbuffer = new char[m_filelength];

  //Read data in a block
  m_inputFile.read(m_pbuffer, m_filelength);
  m_inputFile.close();

  //Grab first byte
  m_pPlaybackPtr = &m_pbuffer[0];
}

// Called repeatedly when this Command is scheduled to run
void PlayMove::Execute()
{
  //If accidently went here when finished return
  if(m_isFinished)
  {
    return;
  }

  //Set Time
  char currentTime[256];
  std::string timeChar = Util::TimeStampStr();
  sprintf(currentTime, "Time: %s", timeChar);
  //Post time on log file
  m_logfile << currentTime << std::endl;
  m_logfile.flush();
  //Log pointer position and size
  m_logfile << "PlayBack = " << (long)m_pPlaybackPtr << " sizeof(RecordingStructure) = " << sizeof(RecordingStructure)
    << " Last Position = " << (long)(m_pbuffer + m_filelength) << std::endl;

  //Create left right variables
  double left = 0.0;
  double right = 0.0;

  //While there is still file left contiue to read
  while((long)(m_pPlaybackPtr + sizeof(RecordingStructure)) < (long)(m_pbuffer + m_filelength))
  {
    //Set binary vaules to structure values
    RecordingStructure *pValues = (RecordingStructure *)m_pPlaybackPtr;

    //Verfiy sync
    if(pValues->m_sync1 == RecordingStructure::SYNC1 && pValues->m_sync2 == RecordingStructure::SYNC2)
    {
      //Set structure values to motor values
      left = pValues->m_left;
      right = pValues->m_right;

      //Log motor values in log file
      m_logfile << "Left: " << left << " right: " << right << std::endl;

      //Move with Arcade
      m_pDrive->MoveArcade(left, right);

      //Get next data point
      m_pPlaybackPtr = (char*)(m_pPlaybackPtr + sizeof(RecordingStructure));
      return;
    }
    else
    {
      //Move down one byte if sync is not alligned
      m_pPlaybackPtr = (char*)(m_pPlaybackPtr + 1);
      m_logfile << "Sync off! NEXT!! " << std::endl;
    }
  }

  //Check if all values have been read
  if((long)(m_pPlaybackPtr + sizeof(RecordingStructure)) > (long)(m_pbuffer + m_filelength))
  {
    m_isFinished = true;
  }
}

// Called once the command ends or is interrupted.
void PlayMove::End(bool interrupted) {}

// Returns true when the command should end.
bool PlayMove::IsFinished() 
{
  return m_isFinished;
}
