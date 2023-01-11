//
// Created by danie on 04/12/2022.
//

#ifndef EX2_SAMPLE_H
#define EX2_SAMPLE_H
#include <iostream>
#include <vector>
using namespace std;

class Sample {
public:
    int vectorSize;
    vector <double> deatils;
    string label;
    Sample(int size, vector <double> a, string l);
};


#endif //EX2_SAMPLE_H
