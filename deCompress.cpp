//============================================================================
// Name        : pngExpander.cpp
// Author      : Joris van Hien
// Version     : 0.1
// Copyright   : Copyright Joris van Hien 2014
// Description : Used to combine an png with a stl file.
//============================================================================

#include "deCompress.hpp"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <stdint.h>
#include <unistd.h>

typedef uint32_t ULONG;


const unsigned int blockSize = 0x10000;

int DeCompress::DeCompressPngStl(string pngstl) 
{
	fstream fileStream;
	uint64_t filePointer;
	uint64_t fileSize = 0;
	uint32_t position = 0;
	int stlFileNameLenght = 0;
	int pngFileNameLenght = 0;
	int stlEnd = 0;

	//Get size of png
	fileStream.open(pngstl.c_str(), ios::in | ios::out | ios::binary);
	if (!fileStream.is_open()) 
	{
		cout << "Unable to load specified file.\n";
		exit(EXIT_FAILURE);
	}

	// setting the reading position of the file stream to the end
	fileStream.seekg(0, ios::end);

	char buffer[6];		//used to read 6 bytes 2x filename lenght 1x place of stl
	// setting the reading position of the file stream to the end
	fileStream.seekg(0, ios::end);

	// getting this position of the reading pointer, thereby retrieving file size
	fileSize = fileStream.tellg();
	std::cout << "filesize: " << fileSize << std::endl;

	//Set filePointer to begin of CRC
	filePointer = fileSize - 6; // 4 bytes back from end
	fileStream.seekg(filePointer);
	fileStream.read(buffer, 6);		// read all 8 bytes of CRC

	for (int u = 2; u < 6; u++) 
	{
		position <<= 8;
		position += (buffer[u] & 0xFF);
	}

	cout << "STL position: " << position << endl;

	pngFileNameLenght = buffer[0]; //get lenght of png file name
	stlFileNameLenght = buffer[1]; // get lenght of stl file name

	cout << "png file name lenght: " << pngFileNameLenght << endl;
	cout << "stl file name lenght: " << stlFileNameLenght << endl;

	string stlFileName = getStlFileName(&fileStream, stlFileNameLenght, fileSize);
	string pngFileName = getPngFileName(&fileStream, pngFileNameLenght , stlFileNameLenght, fileSize);

	stlEnd = fileSize - (6 + pngFileNameLenght + pngFileNameLenght);

	fileStream.close();

	getPng(pngFileName, pngstl, position);
	getStl(stlFileName, pngstl, position, stlEnd);
	return 0;
}

int DeCompress::getPng(string png, string compressedFile, uint32_t endpos) 
{
	fstream fileStreamOut;
	fstream fileStreamIn;
	uint64_t filePointer;
	uint32_t position = 0;

	int bufferSize = blockSize; // arbitrary choice of buffer size
	int difference = 0;		// difference between current position and file size
	char buffer[blockSize];	// initializing byte array of certain specified size

	//Open new PNG file
	fileStreamOut.open(png.c_str(), ios::out | ios::binary);
	if (!fileStreamOut.is_open()) 
	{
		cout << "Unable to load specified file.\n";
		exit(EXIT_FAILURE);
	}

	fileStreamIn.open(compressedFile.c_str(), ios::in | ios::out | ios::binary);
	if (!fileStreamIn.is_open()) 
	{
		cout << "Unable to load specified file.\n";
		exit(EXIT_FAILURE);
	}

	fileStreamIn.seekg(0, ios::beg);
	// loop until file pointer has reached the end of the file
	cout << "\nBeginning Decompression of png \n";
	filePointer = 0;

	//add png to file
	while (filePointer < endpos) 
	{
		// calculating difference between the current position in the file and file size
		difference = endpos - filePointer;
		// if the difference is less than the buffer size, then no need to fill the
		// buffer completely, only by the difference
		if (difference < bufferSize) 
		{
			bufferSize = difference;
		}

		fileStreamIn.seekg(filePointer);
		fileStreamIn.read(buffer, bufferSize);
		// setting writing pointer to the current location
		fileStreamOut.seekp(filePointer);
		// writing the inverted file
		fileStreamOut.write(buffer, bufferSize);
		// incrementing current file pointer by the amount of buffer
		filePointer += bufferSize;
		// adjusting interface
		float progress = (float) filePointer / (float) endpos * 100.0f;
		cout << '\r';
		cout << "Png creating Completed: " << (int) progress << "%";
	}
	fileStreamOut.close();
	fileStreamIn.close();
	return 0;
}

int DeCompress::getStl(string stl, string compressedFile, uint32_t startpos, uint64_t fileSize) 
{
	fileSize = fileSize - 4;
	fstream fileStreamOut;
	fstream fileStreamIn;
	uint64_t filePointer;
	uint32_t position = 0;

	int bufferSize = blockSize; 	// arbitrary choice of buffer size
	int difference = 0;				// difference between current position and file size
	char buffer[blockSize];			// initializing byte array of certain specified size

	//Open new PNG file
	fileStreamOut.open(stl.c_str(), ios::out | ios::binary);
	if (!fileStreamOut.is_open()) 
	{
		cout << "Unable to load specified file.\n";
		exit(EXIT_FAILURE);
	}

	fileStreamIn.open(compressedFile.c_str(), ios::in | ios::out | ios::binary);
	if (!fileStreamIn.is_open()) 
	{
		cout << "Unable to load specified file.\n";
		exit(EXIT_FAILURE);
	}

	fileStreamIn.seekg(startpos);
	// loop until file pointer has reached the end of the file
	cout << "\nBeginning Decompression of stl \n";
	filePointer = startpos;

	cout << startpos << endl;

	//add png to file
	while (filePointer < fileSize) 
	{
		// calculating difference between the current position in the file and file size
		difference = fileSize - filePointer;
		// if the difference is less than the buffer size, then no need to fill the
		// buffer completely, only by the difference
		if (difference < bufferSize) 
		{
			bufferSize = difference;
		}

		fileStreamIn.seekg(filePointer);
		fileStreamIn.read(buffer, bufferSize);
		// setting writing pointer to the current location
		fileStreamOut.seekp(filePointer - startpos);
		// writing the inverted file
		fileStreamOut.write(buffer, bufferSize);
		// incrementing current file pointer by the amount of buffer
		filePointer += bufferSize;
		// adjusting interface
		float progress = (float) filePointer / (float) (fileSize - startpos)
				* 100.0f;
		cout << '\r';
		cout << "Png creating Completed: " << endl;
	}
	fileStreamOut.close();
	fileStreamIn.close();
	return 0;
}

string DeCompress::getStlFileName(fstream* fileStream, int stlFileNameLenght, uint64_t fileSize) 
{
	uint64_t filePointer;
	char buffer[stlFileNameLenght+1];
	string stlName;

	filePointer = (fileSize-6) - stlFileNameLenght;
	fileStream->seekg(filePointer);
	fileStream->read(buffer,stlFileNameLenght);
	buffer[stlFileNameLenght] = '\0';		//Terminate with \0 to be sure the string ends

	stlName = string(buffer);
	cout << "stl name: " << stlName << endl;
	return stlName;
}

string DeCompress::getPngFileName(fstream* fileStream, int pngFileNameLenght, int stlFileNameLenght, uint64_t fileSize) 
{
	uint64_t filePointer;
	char buffer[pngFileNameLenght+1];
	string pngName;

	filePointer = (fileSize-6) - stlFileNameLenght - pngFileNameLenght;
	fileStream->seekg(filePointer);
	fileStream->read(buffer,pngFileNameLenght);
	buffer[pngFileNameLenght] = '\0';	//Terminate with \0 to be sure the string ends

	pngName = string(buffer);
	cout << "png name: " << pngName << endl;
	return pngName;
}
