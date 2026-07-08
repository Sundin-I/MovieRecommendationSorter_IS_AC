//
// Created by Hikari on 7/1/2026.
//

#ifndef PROJECT1_MOVIE_H
#define PROJECT1_MOVIE_H

#include <vector>
#include <string>

using namespace std;

struct Movie {
    int movieId = 0;
    string movieName;

    vector<string> movieGenres;

    double averageMovieRating = 0;
    int ratingCount = 0;
    double recommendationScore = 0;
    double RatingSum = 0;
};

inline bool isMovieRankedLower(const Movie& left, const Movie& right) {
    if (left.recommendationScore == right.recommendationScore) {
        return left.movieId > right.movieId;
    }

    return left.recommendationScore < right.recommendationScore;
}

inline bool isMovieRankedHigher(const Movie& left, const Movie& right) {
    if (left.recommendationScore == right.recommendationScore) {
        return left.movieId < right.movieId;
    }

    return left.recommendationScore > right.recommendationScore;
}

#endif //PROJECT1_MOVIE_H
