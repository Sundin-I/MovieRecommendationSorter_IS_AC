//
// Created by Hikari on 7/1/2026.
//

#ifndef PROJECT1_MOVIES_H
#define PROJECT1_MOVIES_H
#include <vector>
#include <string>

using namespace std;

struct Movies {
    int movieId;
    string movieName;

    vector<string> movieGenres;

    double averageMovieRating = 0;
    int ratingCount = 0;
    double recommendationScore = 0;
    double RatingSum = 0;


};


#endif //PROJECT1_MOVIES_H