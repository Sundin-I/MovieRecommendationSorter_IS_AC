//
// Created by Hikari on 7/1/2026.
//

#ifndef PROJECT1_MINHEAP_H
#define PROJECT1_MINHEAP_H

#include <vector>
#include "Movie.h"

using namespace std;

class minHeap {
private:
    vector<Movie> movieHeap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(const Movie& selectedMovie);
    Movie deleteMin();
    Movie obtainMin();
    int size() const;
    bool empty() const;
};

#endif //PROJECT1_MINHEAP_H