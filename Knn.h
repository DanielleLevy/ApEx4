//
// Created by Or Gabay on 13/12/2022.
//

#ifndef EX2_KNN_H
#define EX2_KNN_H
using namespace std;
#include "Sample.h"
#include <iostream>
#include <vector>
#include "Distance.h"
#include <utility>
#include <iostream>
#include <map>


class Knn {
public:
    vector<Sample> theDb;
    string typeDistance;
    int theK;
    vector<double> theVectorFromUser;
    Knn (vector<Sample> db, string distance, int k);

    string findTheLabel (vector<double> vectorFromUser);
};

#endif //EX2_KNN_H
