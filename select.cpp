/********************
 * Selector Module
 *
 * Written by Minh Quang Pham
 *
 ********************/

#include <iostream>
#include "select.h"

using namespace std;

void selectData (char* inputName, char* outputName, long long start, long long end){
	int reader;
	edf_hdr_struct inFile;
	reader = edfopen_file_readonly(inputName, &inFile, EDFLIB_READ_ANNOTATIONS);

	int writer;
	writer = edfopen_file_writeonly(outputName, EDFLIB_FILETYPE_EDFPLUS, 30);

	start = start - 9000000000;
	if (start < 0)
		start = 0;
	end = end + 9000000000;
	if (end > inFile.file_duration)
		end = inFile.file_duration;
	long long length = end - start;

	int samStart = start/50000;
	int samEnd = end/50000;
	int samLength = length/50000;

	double buffer[200];

	if (reader < 0 || writer < 0){
		cout << "Error" << endl;
		return;
	}

	for (int i = 0; i < 30; i++){
		edf_set_samplefrequency(writer, i, 200);
		edf_set_physical_maximum(writer, i, 5000);
		edf_set_physical_minimum(writer, i, -5000);
		edf_set_digital_maximum(writer, i, 32768);
		edf_set_digital_minimum(writer, i, -32768);
	}

	for (int i = 0; i < samLength; i += 200){
		for (int j = 0; j < 30; j++) {
			edfseek(reader, j, samStart + i, EDFSEEK_SET);
			if (i + 200 > samLength) {
				int remaining = samLength - i;
				edfread_physical_samples(reader, j, remaining, buffer);
				int val2 = edfwrite_physical_samples(writer, buffer);

				if (val2 < 0)
					cout << "Failed to write to " << j << endl;

			} else {
				edfread_physical_samples(reader, j, 200, buffer);
				int val2 = edfwrite_physical_samples(writer, buffer);

				if (val2 < 0)
					cout << "Failed to write to " << j << endl;
			}
		}
	}

	edfclose_file(reader);
	edfclose_file(writer);

}

