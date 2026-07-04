
#include "minHeap.h"
#include <iostream>
#include <queue>


void minHeap::heapifyUp(int index)

{
    while (index > 0) {

        int parent = (index-1)/2;

        if (movieHeap[index].recommendationScore < movieHeap[parent].recommendationScore) {
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

        if (LC < static_cast<int>(movieHeap.size()) && movieHeap[LC].recommendationScore < movieHeap[smallest_child_index].recommendationScore) {
            smallest_child_index = LC;
        }
        if (RC < static_cast<int>(movieHeap.size()) && movieHeap[RC].recommendationScore < movieHeap[smallest_child_index].recommendationScore) {
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

void minHeap::insert(const Movies& selectedMovie)
{
    movieHeap.push_back(selectedMovie);
    heapifyUp(movieHeap.size() - 1);

}

Movies minHeap::deleteMin(){

    if (movieHeap.empty()) {
        return Movies();
    }
    Movies deletedMovie = movieHeap[0];

    if (movieHeap.size() == 1) {
        movieHeap.pop_back();
        return deletedMovie;
    }


    movieHeap[0] = movieHeap.back();
    movieHeap.pop_back();
    heapifyDown(0);

    return deletedMovie;

}


Movies minHeap::obtainMin() {

    if (movieHeap.empty()) {
        return Movies();
    }
    Movies obtainedMovie = movieHeap[0];

    return obtainedMovie;

}

int minHeap::size() const
{
    return movieHeap.size();

}

bool minHeap::empty() const {
    if (movieHeap.empty()) {
        return true;
    }
    return false;

}
/*
int findTopKmovies(vector<Movies>& movies, int k)
{
    priority_queue<Movies, vector<Movies>, greater<Movies>> pq;
    for (Movies i: movies) {
        pq.push(i);
        if (pq.size() > k)
            pq.pop();
    }
    return pq.top();
}*/