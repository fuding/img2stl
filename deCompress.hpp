/*
 *     ____  ____  _____   ____________
 *    / __ \/ __ \/  _/ | / /_  __/ __ \
 *   / /_/ / /_/ // //  |/ / / / / /_/ /
 *  / ____/ _, _// // /|  / / / / _, _/
 * /_/   /_/ |_/___/_/ |_/ /_/ /_/ |_|
 *
 * Copyright Printr B.V. All rights reserved.
 * This code is closed source and should under
 * nu circumstances be copied or used in other
 * applications that for Printr B.V.
 *
 */

#ifndef DECOMPRESS_H_
#define DECOMPRESS_H_

#include <string>
using namespace std;

class DeCompress {
public:
	static int DeCompressPngStl(string pngstl);
private:
	static int getPng(string png, string compressedFile, uint32_t endpos);
	static int getStl(string stl, string compressedFile, uint32_t startpos, uint64_t fileSize);
	static string getStlFileName(fstream *, int stlFileNameLenght, uint64_t fileSize);
	static string getPngFileName(fstream *, int pngFileNameLenght, int stlFileNameLenght,  uint64_t fileSize);
};

#endif /* DECOMPRESS_H_ */
