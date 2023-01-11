//
// Created by danie on 04/12/2022.
//

#ifndef EX2_DISTANCE_H
#define EX2_DISTANCE_H
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


class Distance {
public:
    /**
 * The public functions are actually the constructor and the function that calls the distance functions
 */
    string choice;
    Distance (string choiceFromTheUser);
    double calc(vector <double> a,  vector <double> b);
private:
    double canberraD(vector <double> a,  vector <double> b );
    double chebyshec (vector <double> a, vector <double> b );
    double minkowskiDistance(vector <double> x,  vector <double> y );
    double manhattanDistance(vector <double> x,  vector <double> y );
    double euclideanDistance(vector <double> x,  vector <double> y );

};

#endif //EX2_DISTANCE_H



