/*
 * deCompress.hpp
 *
 *  Created on: 29-mei-2014
 *      Author: Joris
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
