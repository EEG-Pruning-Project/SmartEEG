/********************
 * .edf convertor Module
 *
 * Written by Minh Quang Pham
 *
 ********************/
#include <fstream>
#include <iostream>
#include "converter.h"

using namespace std;

int maxPos (int in){
	return 256 + (44 * 112) + (in * 8);
}

void convertFile (char* inputName){
	fstream myFile (inputName, ios::in | ios::out | ios::binary);

	int myPos = maxPos(34);
	myFile.seekp(myPos);
	myFile << char(0x31);

	myPos = maxPos(40);
	myFile.seekp(myPos);
	myFile << char(0x31);

	myFile.seekp(0x1810);
	myFile << char(0x31);

	myFile.seekp(0x1840);
	myFile << char(0x31);

	myFile.seekp(0xC4);
	myFile << char(0x43);

	myFile.close();
}
