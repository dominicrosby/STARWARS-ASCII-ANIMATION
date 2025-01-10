#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>

#include "movie.h"

MoviePlayer::MoviePlayer(std::string filmName)
{
	//MoviePlayer constructor: The parameterized constructor should:
	//set the appropriate member variables,
	mFilmName = filmName;
	currFrameNum = 1;
	//ensure that the tape is empty, then call the member function loadTape on the inputted file name.
	mFilm.clear();
	pos = mFilm.begin();
	loadTape();
}

MoviePlayer::~MoviePlayer()
{
	//WHAT DO I DO HERE
}

void MoviePlayer::goFwrd()
{
	//incriment position and counter
	if(pos != --mFilm.end())
	{
		pos++;
		currFrameNum++;
	}
}

void MoviePlayer::goBack()
{
	//decriment position and counter
	if(pos != --mFilm.begin())
	{
		pos--;
		currFrameNum--;
	}
	else
	{
		currFrameNum = 1;
		pos = mFilm.begin();
	}
}

void MoviePlayer::rewind()
{

	currFrameNum = 1;
	pos = mFilm.begin();
}

std::string MoviePlayer::getCurrFrame()
{
	return *pos;
}

void MoviePlayer::delCurrFrame()
{
	if(pos != mFilm.end())//fix this, check frame counter
	{
		pos = mFilm.erase(pos);
	}
}

void MoviePlayer::copyCurrFrame()
{
	pos = mFilm.insert(pos, *pos);
	currFrameNum++;
}

unsigned MoviePlayer::getCurrFrameNum() const
{
	// TODO: Complete function, fix return value
	return currFrameNum;
}

unsigned int MoviePlayer::getNumFrames() const
{
	// TODO: Complete function, fix return value
	return mFilm.size();
}

// Function: getFrameSize
// Purpose: Gives the number of lines in a frame
// For how big the "screen" for the film should be
// Input: None
// Returns: The value stored in FRAMESIZE
unsigned int MoviePlayer::getFrameSize() const
{
	// TODO: Complete function, fix return value
	return FRAMESIZE;
}

// Function: loadTape
// Purpose: Uses mFilmName (set by constructor) to fill
// mFilm with strings that make up the movie to display
// Input: None
// Returns: Nothing
void MoviePlayer::loadTape()
{
	std::ifstream file;
	//string for each line of file
	std::string fileLine;
	//lines grouped into slides
	std::string slideContents;
	int pauseLength;

	//open the textfile
	//file.open("/Users/dominicchristiansen/Downloads/CS/hw04-dominicrosby/input/scene1.ani");
	file.open(mFilmName);
	if(!file.is_open())
	{
		throw std::invalid_argument("file failed to open");
		file.close();
		exit(1);
	}
	//read the file
    while (!file.eof()) 
	{
        //read line by line
		std::getline(file, fileLine);
		int i;
		//if the fist character is a digit 
        if(std::isdigit(fileLine[0])) 
		{
			//save the digit for later
			pauseLength = stoi(fileLine);
        }
		else
		{
			continue;
		}
		//adds the following 13 lines after the number to the 
		for(i = 0; i < FRAMESIZE; i++)
		{
			//check for forward slash
			getline(file, fileLine);
			
			/*if(i < 12)
			{
			slideContents += fileLine + "\n"; 
			}*/
			//else
			if(fileLine[fileLine.length() - 1] == '\\')
			{
				slideContents += fileLine + " \n";
			}
			else
			{
				slideContents += fileLine + "\n";
			}
		}
		//second for loop pushes onto slide contents pauseLength times
		for(int n = 0; n < pauseLength; n++)
		{
			mFilm.push_back(slideContents);
		}
		slideContents.clear();
	}
	// Close the file
	file.close(); 
}
