//
// Created by Or Gabay on 12/12/2022.
//
using namespace std;

#include "Knn.h"

/**
* The KNN class which contains the details of the current KNN problem and its solution algorithm
*/

Knn::Knn (vector<Sample> db, string distance, int k, vector<double> vectorFromUser)
{
    /**
     * Constructor of KNN. Initializes the problem with all the details received from the user:
     * the database, the type of the distance function, the K neighbors and the vector.
     */
    theDb=db;
    typeDistance=distance;
    theK=k;
    theVectorFromUser=vectorFromUser;
}
string Knn::findTheLabel (){
    /**
     * This function implements the KNN algorithm. Solves the given problem,
     * returns a string of the label name of the K nearest neighbors of the obtained vector,
     * according to the distance function the user wants and according to his database.
     */
    // Vector of pairs - distance of a sample from the inserted vector, and the sample itself:
    vector <pair<double, Sample>> allTheDistances;

    // Go over the samples in the database, calculate the distance according to the requested distance function
    // between the sample and the given vector and insert it into the distances vector:
    for (int i=0; i<theDb.size();i++){
        double distance2 = 0;
        Distance distance1(typeDistance);
        distance2 = distance1.calc(theVectorFromUser, theDb[i].deatils);
        allTheDistances.push_back(make_pair(distance2, theDb[i]));
    }

    //Performing a bubble sort on the distances so that
    // the minimum distance is first and the largest distance is last:
    for (int i=0; i<allTheDistances.size();i++) {
        for (int j=0; j<allTheDistances.size()-1;j++){
            if (allTheDistances[j].first>allTheDistances[j+1].first){
                swap (allTheDistances[j], allTheDistances[j+1]);
            }
        }
    }

    // Find the labels of the K neighbors whose
    // distance from the given vector is the smallest (nearest neighbors):
    vector<string> theNearestNeighobors (theK);
    for (int i=0; i<theK; i++){
        theNearestNeighobors[i] = allTheDistances[i].second.label;
    }

    // Finding and returning the label that returns
    // the most from the list of K nearest neighbors to the given vector:
    map <string, int> theCommonLabel;
    for (string theLabel: theNearestNeighobors){
        theCommonLabel[theLabel]++;
    }
    string theFinalResult;
    int max =0;
    for (auto label :theCommonLabel){
        if (label.second>max)
        {
            theFinalResult=label.first;
            max=label.second;
        }
    }
    return theFinalResult;
}
