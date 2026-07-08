#include "quicksort.h"
#include <algorithm>

using namespace std;

int quickPass(vector<Movie>& movies, int startIndex, int endIndex)
{
    int pivotIndex = startIndex;
    int upIndex = startIndex + 1;
    int downIndex = endIndex;

    while (upIndex <= downIndex)
    {
        if (!isMovieRankedLower(movies[upIndex], movies[pivotIndex]))
        {
            upIndex++;
        }
        else if (isMovieRankedLower(movies[downIndex], movies[pivotIndex]))
        {
            downIndex--;
        }
        else
        {
            swap(movies[upIndex], movies[downIndex]);
        }
    }

    swap(movies[pivotIndex], movies[downIndex]);
    return downIndex;
}

void subQuickSort(vector<Movie>& movies, int startIndex, int endIndex)
{
    if (startIndex >= endIndex)
    {
        return;
    }

    int divider = quickPass(movies, startIndex, endIndex);

    subQuickSort(movies, startIndex, divider - 1);
    subQuickSort(movies, divider + 1, endIndex);
}

void quickSort(vector<Movie>& movies)
{
    if (movies.empty())
    {
        return;
    }

    subQuickSort(movies, 0, movies.size() - 1);
}

bool isSortedDescending(const vector<Movie>& movies)
{
    for (int i = 0; i < static_cast<int>(movies.size()) - 1; i++)
    {
        if (isMovieRankedHigher(movies[i + 1], movies[i]))
        {
            return false;
        }
    }

    return true;
}
