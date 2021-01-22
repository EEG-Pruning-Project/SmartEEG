/********************
 * Pruning Module
 *
 * Written by Minh Quang Pham
 *
 ********************/
#include <iostream>
#include <vector>
#include <iterator>
#include "output.h"
#include "select.h"

using namespace std;

void posToOutput (char* inputName, vector<long long> &o){
	vector<long long>::iterator it = o.begin();
	int file = 0;
	while (it != o.end()) {
		int i = it - o.begin();
		long long initial = o[i];
		long long temp = o[i];

		vector<long long>::iterator it2 = it;

		while (it2 != o.end())
		{
			int i2 = it2 - o.begin();
			long long end = o[i2];
			if (end - temp <= 600000000){
				it = it2;
				temp = end;
			}
			it2++;
		}
		cout << "Initial Alarm: " << initial << " Final Alarm: " << temp << endl;

		string tempName = "output_";
		tempName += to_string(file);
		tempName += ".edf";
		char* outputName = new char [tempName.length()+1];
		strcpy(outputName, tempName.c_str());

		cout << outputName << endl;

		selectData(inputName, outputName, initial, temp);

		it++;
		file++;
	}
}

void posToOutput (char* inputName, vector<long long> &o, vector<outputStruct> &myOutput){
	vector<long long>::iterator it = o.begin();
	int file = 0;
	while (it != o.end()) {
		int i = it - o.begin();
		long long initial = o[i];
		long long temp = o[i];
		int alarms = 0;

		vector<long long>::iterator it2 = it;

		while (it2 != o.end())
		{
			int i2 = it2 - o.begin();
			long long end = o[i2];
			if (end - temp <= 600000000){
				it = it2;
				temp = end;
				alarms++;
			}
			it2++;
		}
		cout << "Initial Alarm: " << initial << " Final Alarm: " << temp << endl;

		string tempName = "output_";
		tempName += to_string(file);
		tempName += ".edf";
		outputStruct foo;
		foo.file = tempName;
		if (alarms > 1)
			foo.risk = "high";
		else
			foo.risk = "medium";
		char* outputName = new char [tempName.length()+1];
		strcpy(outputName, tempName.c_str());

		cout << outputName << " Risk: " << foo.risk << endl;

		selectData(inputName, outputName, initial, temp);

		it++;
		file++;
	}
}
