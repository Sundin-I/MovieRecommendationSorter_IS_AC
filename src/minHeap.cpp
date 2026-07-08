#include "minHeap.h"
#include <algorithm>
#include <iostream>

void minHeap::heapifyUp(int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (isMovieRankedLower(movieHeap[index], movieHeap[parent])) {
            swap(movieHeap[index], movieHeap[parent]);
            index = parent;
        }
        else {
            break;
        }
    }
}

void minHeap::heapifyDown(int index) {
    while (true) {
        int smallest_child_index = index;
        int LC = 2 * index + 1;
        int RC = 2 * index + 2;

        if (LC < static_cast<int>(movieHeap.size()) && isMovieRankedLower(movieHeap[LC], movieHeap[smallest_child_index])) {
            smallest_child_index = LC;
        }
        if (RC < static_cast<int>(movieHeap.size()) && isMovieRankedLower(movieHeap[RC], movieHeap[smallest_child_index])) {
            smallest_child_index = RC;
        }
        if (smallest_child_index != index) {
            swap(movieHeap[index], movieHeap[smallest_child_index]);
            index = smallest_child_index;
        }
        else {
            break;
        }
    }
}

void minHeap::insert(const Movie& selectedMovie)
{
    movieHeap.push_back(selectedMovie);
    heapifyUp(movieHeap.size() - 1);
}

Movie minHeap::deleteMin()
{
    if (movieHeap.empty()) {
        return Movie();
    }

    Movie deletedMovie = movieHeap[0];

    if (movieHeap.size() == 1) {
        movieHeap.pop_back();
        return deletedMovie;
    }

    movieHeap[0] = movieHeap.back();
    movieHeap.pop_back();
    heapifyDown(0);

    return deletedMovie;
}

Movie minHeap::obtainMin()
{
    if (movieHeap.empty()) {
        return Movie();
    }

    Movie obtainedMovie = movieHeap[0];

    return obtainedMovie;
}

int minHeap::size() const
{
    return movieHeap.size();
}

bool minHeap::empty() const
{
    return movieHeap.empty();
}
