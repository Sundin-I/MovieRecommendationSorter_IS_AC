//
// Created by Hikari on 7/1/2026.
//
#include "minHeap.h"
#include "movies.h"
#include "movieCollection.h"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> movieGenres = {
    "unknown", "Action", "Adventure", "Animation",
    "Children's", "Comedy", "Crime", "Documentary",
    "Drama", "Fantasy", "Film-Noir", "Horror", "Musical",
    "Mystery", "Romance", "Sci-Fi","Thriller", "War", "Western"
};

void movieCollection::loadsDataSet() {
    ifstream itemFile("MovieData/u.item");

    if (!itemFile.is_open()) {
        cout<<"Failed to open file..."<<endl;
        return;
    }

    string line;

    while (getline(itemFile, line)) {
        stringstream ss(line);

        Movies film;
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
    cout<<"Loaded movie dataset..."<<endl;
}

void movieCollection::totalCountofRecommendation() {

    cout<<"Total count of recommendationed movies in dataset:"<<movies.size()<<endl;

}

void movieCollection::calculationofScores() {
    ifstream dataFile("MovieData/u.data");

    if (!dataFile.is_open()) {
        cout<<"Failed to open file..."<<endl;
        return;
    }

    int userId, itemid, rating, timestamp;

    while (dataFile >> userId >> itemid >> rating >> timestamp) {
        for (auto &movie : movies) {
            if (movie.movieId == itemid) {
                movie.RatingSum += rating;
                movie.ratingCount++;
                break;
            }
        }
    }
    for (auto &movie : movies) {
        if (movie.ratingCount > 0) {
            movie.averageMovieRating = movie.RatingSum / movie.ratingCount;
            movie.recommendationScore = movie.averageMovieRating * ((double)movie.ratingCount/(movie.ratingCount+50.0));
        }
    }
    scoresCalculated = true;
    cout << "Successfully calculated the scores!" << endl;
}


void movieCollection::showTopKmovies() {
    minHeap movieHeap;


    int k;
    cout<<"Type how many movies you want rated:";
    cin>>k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (auto &movie : movies) {
        if (movieHeap.size() < k) {
            movieHeap.insert(movie);
        }
        else if (!movieHeap.empty() && movie.recommendationScore > movieHeap.obtainMin().recommendationScore)
        {
            movieHeap.deleteMin();
            movieHeap.insert(movie);
        }
    }
    vector<Movies> result;

    while (!movieHeap.empty()) {
        result.push_back(movieHeap.deleteMin());
    }
    reverse(result.begin(), result.end());

    for (auto &movie : result) {
        cout<<movie.movieName<<" | Score: "<<movie.recommendationScore<<endl;
    }
}
void movieCollection::showTopKmovies_bygenre() {
    int k;
    cout<<"Type how many movies you want:"<<endl;
    cin>>k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string genre;
    cout <<"Genres: unknown, Action, Adventure Animation, "
           "Children's, Comedy, Crime, Documentary, Drama, "
           "Fantasy, Film-Noir, Horror, Musical, Mystery, Romance, "
           "Sci-Fi,Thriller, War, Western" <<endl;
    cout<<"Type a genre:";
    getline(cin >> ws, genre);

    minHeap movieHeapG;

    for (auto &movie : movies) {
        bool hasGenre = false;

        for (const auto &g : movie.movieGenres) {
            if (g == genre) {
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
        else if (!movieHeapG.empty() && movie.recommendationScore > movieHeapG.obtainMin().recommendationScore) {
            movieHeapG.deleteMin();
            movieHeapG.insert(movie);
        }
    }
    vector<Movies> result;

    while (!movieHeapG.empty()) {
        result.push_back(movieHeapG.deleteMin());
    }
    reverse(result.begin(), result.end());

    for (auto &movie : result) {
        cout<<movie.movieName<<" | Score: "<<movie.recommendationScore<<endl;
    }
}


void movieCollection::algorithmComparison() {
    int k;
    cout<<"Type how many movies you want:"<<endl;
    cin>>k;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    auto startHeap = chrono::high_resolution_clock::now();

    minHeap movieHeap;


    for (auto &movie : movies) {
        if (movieHeap.size() < k) {
            movieHeap.insert(movie);
        }
        else if (!movieHeap.empty() && movie.recommendationScore > movieHeap.obtainMin().recommendationScore)
        {
            movieHeap.deleteMin();
            movieHeap.insert(movie);
        }
    }
    vector<Movies> algortihmHeapresult;

    while (!movieHeap.empty()) {
        algortihmHeapresult.push_back(movieHeap.deleteMin());
    }
    auto endHeap = chrono::high_resolution_clock::now();
    auto heapTime = chrono::duration_cast<chrono::microseconds>(endHeap - startHeap);

    //Vincent will provide his quicksort version here

    cout<<"Time elapsed[heap]: "<<heapTime.count()<<" microseconds"<<endl;
    //Vincent's quicksort prints its output here



}void movieCollection::searchTitles() {

    string searchTitle;
    cout<<"Type a movie title keyword:";
    getline(cin >> ws, searchTitle);

    bool found = false;

    for (auto &movie : movies) {
        if (movie.movieName.find(searchTitle) != string::npos) {
            cout << movie.movieName<<" | ID: "<<movie.movieId<<endl;
            found = true;
        }
    }
    if (!found) {
        cout<<"No movies found matching"<<searchTitle<<endl;
    }
}

