/********************
 * Flags Module Header
 *
 * Written by Jazmin Barraza
 *
 ********************/
#ifndef THESMARTEEG_V2_FLAGS_H
#define THESMARTEEG_V2_FLAGS_H
#include <vector>
#include <iostream>
using namespace std;

class Flags{
public:
    void find_flags(vector<string> s, vector<int> &p, string k);
    void get_onsets(vector<long long> &o, vector<int> pos);
    void keep_alarms(vector<string> &s, vector<long long> &o);
    void readAnnotations(char* inputName, vector<string> &s, vector<long long> &o);

};


#endif //THESMARTEEG_V2_FLAGS_H
