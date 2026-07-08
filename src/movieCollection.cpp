//
// Created by Hikari on 7/1/2026.
//
#include "minHeap.h"
#include "Movie.h"
#include "movieCollection.h"
#include "quicksort.h"
#include <chrono>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

vector<string> movieGenres = {
    "unknown", "Action", "Adventure", "Animation",
    "Children's", "Comedy", "Crime", "Documentary",
    "Drama", "Fantasy", "Film-Noir", "Horror", "Musical",
    "Mystery", "Romance", "Sci-Fi", "Thriller", "War", "Western"
};

string lowerCaseCopy(string text) {
    transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
        return static_cast<char>(tolower(c));
    });
    return text;
}

vector<Movie> topKMoviesWithHeap(const vector<Movie>& movies, int k) {
    minHeap movieHeap;

    for (const auto &movie : movies) {
        if (movieHeap.size() < k) {
            movieHeap.insert(movie);
        }
        else if (!movieHeap.empty() && isMovieRankedHigher(movie, movieHeap.obtainMin())) {
            movieHeap.deleteMin();
            movieHeap.insert(movie);
        }
    }

    vector<Movie> result;

    while (!movieHeap.empty()) {
        result.push_back(movieHeap.deleteMin());
    }

    reverse(result.begin(), result.end());
    return result;
}

void movieCollection::loadsDataSet() {
    movies.clear();
    totalRatingsLoaded = 0;
    scoresCalculated = false;

    ifstream itemFile("MovieData/u.item");

    if (!itemFile.is_open()) {
        cout << "Failed to open file..." << endl;
        return;
    }

    string line;

    while (getline(itemFile, line)) {
        stringstream ss(line);

        Movie film;
        string indicator;
        string idString;

        getline(ss, idString, '|');
        film.movieId = stoi(idString);

        getline(ss, film.movieName, '|');

        for (int i = 0; i < 3; i++) {
            getline(ss, indicator, '|');
        }

        for (int i = 0; i < 19; i++) {
            getline(ss, indicator, '|');
            if (indicator == "1") {
                film.movieGenres.push_back(movieGenres[i]);
            }
        }

        movies.push_back(film);
    }

    cout << "Loaded movie dataset..." << endl;
}

void movieCollection::totalCountofRecommendation() {
    cout << "Total movies loaded: " << movies.size() << endl;
    cout << "Total ratings loaded: " << totalRatingsLoaded;

    if (!scoresCalculated) {
        cout << " (calculate scores first to load ratings)";
    }

    cout << endl;
}

void movieCollection::calculationofScores() {
    if (movies.empty()) {
        cout << "Please load the movie dataset first." << endl;
        return;
    }

    ifstream dataFile("MovieData/u.data");

    if (!dataFile.is_open()) {
        cout << "Failed to open file..." << endl;
        return;
    }

    int userId, itemId, rating, timestamp;
    unordered_map<int, int> movieIndexById;
    totalRatingsLoaded = 0;

    for (int i = 0; i < static_cast<int>(movies.size()); i++) {
        movies[i].RatingSum = 0;
        movies[i].ratingCount = 0;
        movies[i].averageMovieRating = 0;
        movies[i].recommendationScore = 0;
        movieIndexById[movies[i].movieId] = i;
    }

    while (dataFile >> userId >> itemId >> rating >> timestamp) {
        totalRatingsLoaded++;
        auto movieIndex = movieIndexById.find(itemId);

        if (movieIndex != movieIndexById.end()) {
            Movie &movie = movies[movieIndex->second];
            movie.RatingSum += rating;
            movie.ratingCount++;
        }
    }

    for (auto &movie : movies) {
        if (movie.ratingCount > 0) {
            movie.averageMovieRating = static_cast<double>(movie.RatingSum) / movie.ratingCount;
            movie.recommendationScore = movie.averageMovieRating * ((double)movie.ratingCount / (movie.ratingCount + 50.0));
        }
    }

    scoresCalculated = true;
    cout << "Successfully calculated the scores!" << endl;
}

void movieCollection::showTopKmovies() {
    if (!scoresCalculated) {
        cout << "Please calculate movie recommendation scores first." << endl;
        return;
    }

    int k;
    cout << "Type how many movies you want rated: ";
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (k <= 0) {
        cout << "Invalid number of movies." << endl;
        return;
    }

    vector<Movie> result = topKMoviesWithHeap(movies, k);

    for (auto &movie : result) {
        cout << movie.movieName << " | Score: " << movie.recommendationScore << endl;
    }
}

void movieCollection::showTopKmovies_bygenre() {
    if (!scoresCalculated) {
        cout << "Please calculate movie recommendation scores first." << endl;
        return;
    }

    int k;
    cout << "Type how many movies you want: ";
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (k <= 0) {
        cout << "Invalid number of movies." << endl;
        return;
    }

    string genre;
    cout << "Genres: unknown, Action, Adventure, Animation, "
            "Children's, Comedy, Crime, Documentary, Drama, "
            "Fantasy, Film-Noir, Horror, Musical, Mystery, Romance, "
            "Sci-Fi, Thriller, War, Western" << endl;

    cout << "Type a genre: ";
    getline(cin >> ws, genre);
    string requestedGenre = lowerCaseCopy(genre);

    minHeap movieHeapG;

    for (auto &movie : movies) {
        bool hasGenre = false;

        for (const auto &g : movie.movieGenres) {
            if (lowerCaseCopy(g) == requestedGenre) {
                hasGenre = true;
                break;
            }
        }

        if (!hasGenre) {
            continue;
        }

        if (movieHeapG.size() < k) {
            movieHeapG.insert(movie);
        }
        else if (!movieHeapG.empty() && isMovieRankedHigher(movie, movieHeapG.obtainMin())) {
            movieHeapG.deleteMin();
            movieHeapG.insert(movie);
        }
    }

    vector<Movie> result;

    while (!movieHeapG.empty()) {
        result.push_back(movieHeapG.deleteMin());
    }

    reverse(result.begin(), result.end());

    for (auto &movie : result) {
        cout << movie.movieName << " | Score: " << movie.recommendationScore << endl;
    }

    if (result.empty()) {
        cout << "No movies found for genre " << genre << endl;
    }
}

void movieCollection::algorithmComparison() {
    if (!scoresCalculated) {
        cout << "Please calculate movie recommendation scores first." << endl;
        return;
    }

    int k;
    cout << "Type how many movies you want: ";
    cin >> k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (k <= 0) {
        cout << "Invalid number of movies." << endl;
        return;
    }

    auto startHeap = chrono::high_resolution_clock::now();

    vector<Movie> algorithmHeapResult = topKMoviesWithHeap(movies, k);

    auto endHeap = chrono::high_resolution_clock::now();
    auto heapTime = chrono::duration_cast<chrono::microseconds>(endHeap - startHeap);

    vector<Movie> quickSortMovies = movies;

    auto startQuickSort = chrono::high_resolution_clock::now();

    quickSort(quickSortMovies);

    vector<Movie> quickSortTopK;
    int resultCount = min(k, static_cast<int>(quickSortMovies.size()));

    for (int i = 0; i < resultCount; i++) {
        quickSortTopK.push_back(quickSortMovies[i]);
    }

    auto endQuickSort = chrono::high_resolution_clock::now();
    auto quickSortTime = chrono::duration_cast<chrono::microseconds>(endQuickSort - startQuickSort);

    bool sameRankings = algorithmHeapResult.size() == quickSortTopK.size();

    for (int i = 0; sameRankings && i < static_cast<int>(algorithmHeapResult.size()); i++) {
        if (algorithmHeapResult[i].movieId != quickSortTopK[i].movieId) {
            sameRankings = false;
        }
    }

    cout << "Time elapsed [heap Top-K]: " << heapTime.count() << " microseconds" << endl;
    cout << "Time elapsed [quicksort]: " << quickSortTime.count() << " microseconds" << endl;
    cout << "Both algorithms produced the same Top-" << resultCount << " ranking: "
         << (sameRankings ? "Yes" : "No") << endl;
}

void movieCollection::searchTitles() {
    if (movies.empty()) {
        cout << "Please load the movie dataset first." << endl;
        return;
    }

    string searchTitle;
    cout << "Type a movie title keyword: ";
    getline(cin >> ws, searchTitle);
    string normalizedSearchTitle = lowerCaseCopy(searchTitle);

    bool found = false;

    for (auto &movie : movies) {
        if (lowerCaseCopy(movie.movieName).find(normalizedSearchTitle) != string::npos) {
            cout << movie.movieName << " | ID: " << movie.movieId << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No movies found matching " << searchTitle << endl;
    }
}
