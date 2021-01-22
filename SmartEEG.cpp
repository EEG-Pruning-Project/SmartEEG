
#include <iostream>
#include <edflib.c>
#include <vector>
#include <algorithm>
#include "select.h"
#include "output.h"
#include "Flags.h"
using namespace std;

int main() {
		char* filename = "DA70203U_0001.edf";
		Flags f;
		vector<string> annot;
		vector<long long> onset;
		vector<outputStruct> riskVector;
		f.readAnnotations(filename, annot, onset);
        f.keep_alarms(annot, onset);
        posToOutput(filename, onset, riskVector);
}

