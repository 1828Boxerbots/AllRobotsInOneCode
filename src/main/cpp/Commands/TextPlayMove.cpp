// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Commands/TextPlayMove.h"

TextPlayMove::TextPlayMove(DriveTrainSubsystemBase *pDrive, const char *pfilename) 
{
  // Use addRequirements() here to declare subsystem dependencies.
  m_filename = pfilename;

  m_pDrive = pDrive;
  AddRequirements(pDrive);
}

// Called when the command is initially scheduled.
void TextPlayMove::Initialize() 
{
	//inFile.open("./recording_2021-03-29_17-07-55_A.txt");
  inFile.open(LOG_FILE);

	// keep reading until EOF``````````````````````````````````````````````````````````````````````
	while (!inFile.eof())
	{
		OneFrame data;

		//get one line (up to "\n")
		char buff[BUFF_SIZE];
		inFile.getline(buff, BUFF_SIZE);

		if (strlen(buff) > 0)
		{
			if (buff[0] != ';') //if not comment
			{
				// get data
				sscanf(buff, "%19s", data.timestamp, TIMESTAMP_MAX_SIZE);
				sscanf(&buff[strlen(data.timestamp)]
					, "%d %d %lf %lf %lf"
					, &data.framenum
					, &data.delayTime
					, &data.gyro
					, &data.left
					, &data.right
				);

				// push to end of array
				arr.push_back(data);
			}
		}
	}
}

// Called repeatedly when this Command is scheduled to run
void TextPlayMove::Execute() 
{
	// check if any data found
	if (arr.size() > 0)
	{
		// parse through found data
		if(index < arr.size())
		{
			//process data
			/*
			std::cout << "timestamp=" << arr[i].timestamp << " ";
			std::cout << "framenum=" << arr[i].framenum << " ";
			std::cout << "delayTime=" << arr[i].delayTime << " ";
			std::cout << "gyro=" << arr[i].gyro << " ";
			std::cout << "left=" << arr[i].left << " ";
			std::cout << "right=" << arr[i].right << " ";
			std::cout << std::endl;
			*/
			index++;
			m_pDrive->MoveArcade(arr[index].left, arr[index].right);
		}
	}
}

// Called once the command ends or is interrupted.
void TextPlayMove::End(bool interrupted) {}

// Returns true when the command should end.
bool TextPlayMove::IsFinished() {
  return m_isFinished;
}

void TextPlayMove::Process(RecordingStructure &data)
{
  m_pDrive->MoveArcade(data.m_left, data.m_right);
  
  Util::DelayInSeconds((double)data.m_sec / 1000.0);
}