//============================================================================
// Name        : main.cpp
// Author      : Joris van Hien
// Version     : 0.1
// Copyright   : Copyright Joris van Hien 2014
// Description : Used to combine an png with a stl file.
//
// Build	   : g++ main.cpp deCompress.cpp -o decompressor
//
//============================================================================

#include <iostream>

#include "deCompress.hpp"

using namespace std;

int main(int argc, char *argv[] ) 
{
	if(argc != 2)
	{
		cout << "Shapedrop Decompressor" << endl;
		cout << "To Decompress ./decompressor [inputpng]" << endl;
		return 0;
	}

	else if(argc == 2)
	{
		DeCompress::DeCompressPngStl(argv[1]);
	}

	cout << "Everything went better than expected!" << endl;
	cout << "See you again @PRINTR" << endl;
	return 0;
}
