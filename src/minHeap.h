//
// Created by Hikari on 7/1/2026.
//

#ifndef PROJECT1_MINHEAP_H
#define PROJECT1_MINHEAP_H
#include <vector>
#include "movies.h"



class minHeap {
private:
    vector<Movies> movieHeap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(const Movies& selectedMovie);
    Movies deleteMin();
    Movies obtainMin();
    int size() const;
    bool empty() const;
    void printingTheMenu();

};


#endif //PROJECT1_MINHEAP_H