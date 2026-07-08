#include <catch2/catch_test_macros.hpp>
#include "minHeap.h"
#include "quicksort.h"

#include <algorithm>
#include <vector>

using namespace std;

Movie makeMovie(int id, double score) {
    Movie movie;
    movie.movieId = id;
    movie.movieName = "Movie " + to_string(id);
    movie.recommendationScore = score;
    return movie;
}

TEST_CASE("Min heap returns movies from lowest score to highest score", "[minHeap]") {
    minHeap heap;

    heap.insert(makeMovie(1, 3.5));
    heap.insert(makeMovie(2, 1.2));
    heap.insert(makeMovie(3, 4.8));
    heap.insert(makeMovie(4, 2.0));

    REQUIRE(heap.deleteMin().movieId == 2);
    REQUIRE(heap.deleteMin().movieId == 4);
    REQUIRE(heap.deleteMin().movieId == 1);
    REQUIRE(heap.deleteMin().movieId == 3);
    REQUIRE(heap.empty());
}

TEST_CASE("Min heap safely handles empty heap operations", "[minHeap]") {
    minHeap heap;

    REQUIRE(heap.empty());
    REQUIRE(heap.size() == 0);
    REQUIRE(heap.obtainMin().recommendationScore == 0);
    REQUIRE(heap.deleteMin().recommendationScore == 0);
}

TEST_CASE("Quick sort orders movies by recommendation score descending", "[quicksort]") {
    vector<Movie> movies = {
        makeMovie(1, 2.1),
        makeMovie(2, 4.9),
        makeMovie(3, 3.3),
        makeMovie(4, 4.1)
    };

    quickSort(movies);

    REQUIRE(movies[0].movieId == 2);
    REQUIRE(movies[1].movieId == 4);
    REQUIRE(movies[2].movieId == 3);
    REQUIRE(movies[3].movieId == 1);
    REQUIRE(isSortedDescending(movies));
}

TEST_CASE("Sorted descending helper detects unsorted movie scores", "[quicksort]") {
    vector<Movie> sortedMovies = {
        makeMovie(1, 5.0),
        makeMovie(2, 4.0),
        makeMovie(3, 1.0)
    };
    vector<Movie> unsortedMovies = {
        makeMovie(1, 5.0),
        makeMovie(2, 1.0),
        makeMovie(3, 4.0)
    };

    REQUIRE(isSortedDescending(sortedMovies));
    REQUIRE_FALSE(isSortedDescending(unsortedMovies));
}

TEST_CASE("Heap top-k approach keeps only the highest scoring movies", "[minHeap][topK]") {
    vector<Movie> movies = {
        makeMovie(1, 1.0),
        makeMovie(2, 5.0),
        makeMovie(3, 3.0),
        makeMovie(4, 4.0),
        makeMovie(5, 2.0)
    };
    minHeap heap;
    int k = 3;

    for (const auto &movie : movies) {
        if (heap.size() < k) {
            heap.insert(movie);
        }
        else if (isMovieRankedHigher(movie, heap.obtainMin())) {
            heap.deleteMin();
            heap.insert(movie);
        }
    }

    vector<int> topMovieIds;
    while (!heap.empty()) {
        topMovieIds.push_back(heap.deleteMin().movieId);
    }

    sort(topMovieIds.begin(), topMovieIds.end());

    REQUIRE(topMovieIds == vector<int>{2, 3, 4});
}
