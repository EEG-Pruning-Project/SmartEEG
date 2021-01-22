/********************
 * Flags Module
 *
 * Written by Jazmin Barraza
 *
 ********************/

#include <iostream>
#include <vector>
#include  <algorithm>
#include <iterator>
#include "edflib.h"
#include "Flags.h"
using namespace std;

//finds the flag positions for each flag and stores it in the position vector
void Flags::find_flags(vector<string> s, vector<int> &p, string k)
{
    //iterates through the vector
    vector<string>::iterator it = s.begin();


    //while the vector hasn't ended
    for(int i = 0; i < s.size();i++)
    {
        string s1 (s[i]);

        size_t found = s1.find(k);
        if(found != string::npos)
        {
            //gets the positon
            p.push_back(i);
            it++;
        }
        else
            it++;
    }
}

//gets the onsets from vector onset and uses position vector
void Flags::get_onsets(vector<long long> &o, vector<int> pos)
{
    //create temperary vector
    vector<long long> temp;
    //iterates through both position and onset vector
    vector<long long>::iterator it = o.begin();
    vector<int>::iterator pit = pos.begin();

    //for in range of the vector size of onset
    for (int i = 0; i < o.size(); ++i)
    {
        //index
        int index = it - o.begin();
        //If value from position vector equals the index of onset
        if (*pit == index)
        {
            //put it in the temperary vector
            temp.push_back(o[i]);
            //increment position vector
            pit++;

        } else
            //increment onset index
            it++;
    }
    //deletes everything in onset
    o.clear();
    //for in range of temperary vector size
    for(int i=0; i < temp.size(); i++)
    {
        //put what is in temperary vector in onset vector
        o.push_back(temp[i]);
    }
    //clear temperary
    temp.clear();
}


//keeps all the alarms from annotations
void Flags::keep_alarms(vector<string> &s, vector<long long> &o)
{
    vector<string>::iterator it = s.begin();
    vector<long long>::iterator it2 = o.begin();

    //go through postion vector using a for loop
    while (it != s.end())
    {
        //index of annotation
        int i = it - s.begin();
        int i2 = it2 - o.begin();
        //if it equals any of the alarms
        string s1 (s[i]);

        size_t found = s1.find("alarm:");
        if(found != string::npos)
        {
            //increment annotation position
            it++;
            it2++;
        }
        else
            //if not delete it from the vector
            s.erase(s.begin()+i);
        	if(s.size() != o.size())
        		o.erase(o.begin()+i2);
    }
}

void Flags::readAnnotations(char* inputName, vector<string> &s, vector<long long> &o)
{
    edf_annotation_struct a;
    edf_hdr_struct hdr;

    int r = edfopen_file_readonly(inputName, &hdr, EDFLIB_READ_ALL_ANNOTATIONS);

    if(hdr.filetype < 0 || r < 0)
    {
        return;
    }
    else{
        for (int i = 0; i < hdr.annotations_in_file; i++)
        {
            if (edf_get_annotation(hdr.handle, i, &a)) {
                printf("Error: edf_get_annotations()");
                edfclose_file(hdr.handle);
                return;
            } else {
                /*printf("annotation: onset is %I64d    description is %s\n",
                       a.onset, a.annotation
                );*/
                o.push_back(a.onset);
                s.push_back(a.annotation);

            }
        }
        edfclose_file(r);
    }
}
