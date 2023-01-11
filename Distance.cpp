//
// Created by danie on 04/12/2022.
//


#include "Distance.h"
using namespace std;

/**
 * The class contains all the distance functions.
    The variable choice contains the user's choice of which insect function to use and is initialized in the constructor.
 */

Distance::Distance( string choiceFromTheUser){/**
 * constructor. Accepts the user's choice and initializes it in a variable
 */
        choice=choiceFromTheUser;
    }


double Distance::calc(vector <double> a,  vector <double> b){/**
 * A calculator function, receiving 2 vectors for calculation and according to the user's choice, sends the vectors to the various functions and returns the answer.
 */
        if (choice=="AUC"){
            return euclideanDistance(a,b);
        }
        if (choice=="MAN"){
            return manhattanDistance(a,b);
        }
        if (choice=="CHB"){
            return chebyshec(a,b);
        }
        if (choice=="CAN"){
            return canberraD(a,b);
        }
        if (choice=="MIN"){
            return minkowskiDistance(a,b);
        }
        return -1;
    }

double Distance::canberraD(vector <double> a,  vector <double> b ){
        /**
         * the function gets 2 vector in the same size and calculates their's canberra distance
         */
        double sum=0; //to sun the distances between the element of the vectors
        double distance; // to compute the distance between the element of the vector
        for (int i=0;i<a.size();i++) // runs on the vector's elements
        {
            distance=(abs(a[i]-b[i]))/(abs(a[i])+abs(b[i]));
            sum=sum+distance ;
        }
        return sum ;
    }


double Distance::chebyshec (vector <double> a, vector <double> b ){
        /**
          * the function gets 2 vector in the same size and calculates their's canberra distance
         */
        double max;  //use for the loop to find the maximum distance
        double distance[a.size()]; // to save the distance between the element of the vector
        for (int i=0;i<a.size();i++) // runs on the vector's elements
        {
            distance[i]=abs(a[i]-b[i]); //compute the distance between the element of the vector
        }
        max = distance[0] ; // init the max to the first distance
        for (int j=1;j<a.size();j++) //find the max distance between the vectors elements
            if (distance[j]>max)
                max=distance[j] ;
        return max ;
    }


double Distance::minkowskiDistance(vector <double> x,  vector <double> y ) {
        /**
         * this function gets 2 vectors in the same size and calculates their Minkowski distance
         */
        const double p=2;
        double sum = 0; // Sum the powers of the differences between the elements of the vectors
        double distance; // Roots the difference between any two elements of any vector
        double finalAnswer; // The final result after taking the root of the sum
        for (int i = 0; i < x.size(); i++) { // Runs over the values (elements) of each vector,
            // assuming both vectors are the same size
            distance = pow((x[i] - y[i]), p);
            sum = sum + distance;
        }
        finalAnswer = pow (sum, 1.0/p);
        return finalAnswer;
    }


double Distance::manhattanDistance(vector <double> x,  vector <double> y ) {
        /**
         * this function gets 2 vectors in the same size and calculates their Manhattan distance
         */
        double sum = 0; // Sum the differences between the elements of the vectors
        double distance; // Calculates the difference between any two elements of any vector
        for (int i = 0; i < x.size(); i++) { // Runs over the values (elements) of each vector,
            // assuming both vectors are the same size
            distance = (abs(x[i] - y[i]));
            sum = sum + distance;
        }
        return sum;
    }


double Distance::euclideanDistance(vector <double> x,  vector <double> y ) {
        /**
         * this function gets 2 vectors in the same size and calculates their Euclidean distance
         */
        double sum = 0; // Sum the squares of the differences between the elements of the vectors
        double distance; // Squares the difference between any two elements of any vector
        double finalAnswer; // The final result after taking the root of the sum
        for (int i = 0; i < x.size(); i++) { // Runs over the values (elements) of each vector,
            // assuming both vectors are the same size
            distance = pow((x[i] - y[i]), 2);
            sum = sum + distance;
        }
        finalAnswer = sqrt(sum);
        return finalAnswer;
    }


