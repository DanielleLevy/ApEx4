//
// Created by danie on 04/12/2022.
//

#include "Sample.h"

using namespace std;
/**
 * Example class, each example contains a vector length, the vector itself and a label.
 * @param size-The size of the vector
 * @param a- The dimensions vector, contains DOUBLE
 * @param l- label
 */
Sample::Sample(int size, vector <double> a, string l){
        vectorSize=size;
        deatils=a;
        label=l;
    }

