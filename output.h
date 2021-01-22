/********************
 * Pruning Module Header
 *
 * Written by Minh Quang Pham
 *
 ********************/
#include <vector>

using namespace std;

#ifndef OUTPUT_H_
#define OUTPUT_H_

struct outputStruct {
	string file, risk;
};
void posToOutput (char* inputName, vector<long long> &o);
void posToOutput (char* inputName, vector<long long> &o, vector<outputStruct> &myOutput);




#endif /* OUTPUT_H_ */
