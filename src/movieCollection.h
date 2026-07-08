//
// Created by Hikari on 7/1/2026.
//

#ifndef PROJECT1_MOVIECOLLECTION_H
#define PROJECT1_MOVIECOLLECTION_H

#include <string>
#include <vector>

#include "minHeap.h"

using namespace std;

class movieCollection {
private:
    vector<Movie> movies;
    int totalRatingsLoaded = 0;
    bool scoresCalculated = false;

public:
    void loadsDataSet();
    void totalCountofRecommendation();
    void calculationofScores();
    void showTopKmovies();
    void showTopKmovies_bygenre();
    void algorithmComparison();
    void searchTitles();
};

#endif //PROJECT1_MOVIECOLLECTION_H
