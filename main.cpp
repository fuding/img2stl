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
