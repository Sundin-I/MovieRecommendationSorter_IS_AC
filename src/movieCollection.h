//
// Created by Hikari on 7/1/2026.
//

#ifndef PROJECT1_MOVIECOLLECTION_H
#define PROJECT1_MOVIECOLLECTION_H
#include <string>
#include <unordered_map>
#include <vector>

#include "minHeap.h"


class movieCollection {
private:
    vector<Movies> movies;
    minHeap movieData;
    unordered_map<int, string> ratingSum;
    unordered_map<int, int> ratingCount;
public:
    void loadsDataSet();
    void totalCountofRecommendation();
    void calculationofScores();
    void showTopKmovies();
    void showTopKmovies_bygenre();
    void algorithmComparison();
    void searchTitles();
    void collectRatings();
    bool scoresCalculated = false;
};



#endif //PROJECT1_MOVIECOLLECTION_H