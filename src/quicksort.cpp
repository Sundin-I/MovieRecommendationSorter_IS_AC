#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Movie
{
    private:
        string title;
        int review_count = 0;
        int review_total = 0;
        int id;
        vector<bool> genres;
    public:
        Movie(int _id, string _title, vector<bool> _genres)
        {
            id = _id;
            title = _title;
            genres = _genres;
        }
        void addRating(int review)
        {
            review_count++;
            review_total += review;
        }
        float rating() const
        {
            if (review_count > 0)
            {
                float temp_total = review_total;
                return temp_total / review_count;
            }
            else
            {
                return 0;
            }
        }
        void resetRating()
        {
            review_count = 0;
            review_total = 0;
        }
        bool operator<(const Movie& other) const
        {
            return this->rating() < other.rating();
        }
        bool operator>(const Movie& other) const
        {
            return this->rating() > other.rating();
        }
        bool operator==(const Movie& other) const
        {
            return this->rating() == other.rating();
        }
        bool operator<=(const Movie& other) const
        {
            return this->rating() <= other.rating();
        }
        bool operator>=(const Movie& other) const
        {
            return this->rating() >= other.rating();
        }
        string getTitle()
        {
            return title;
        }
        int getCount()
        {
            return review_count;
        }
        int getID()
        {
            return id;
        }
        bool getGenre(int index)
        {
            return genres[index];
        }
};
void PrintVector(vector<string> vec)
{
    for (int i = 0; i < vec.size() - 1; i++)
    {
        cout << vec[i] << ", ";
    }
    if (vec.size() != 0)
    {
        cout << vec[vec.size() - 1];
    }
    cout << endl;
}
template <typename T>
int QuickPass(vector<T>& vec, int strt_indx, int end_indx)
{
    if (end_indx - strt_indx > 0)
    {
        int pvot_indx = strt_indx;
        int up_indx = strt_indx + 1;
        int dwn_indx = end_indx;
        while (up_indx <= dwn_indx)
        {
            if (vec[up_indx] <= vec[pvot_indx])
            {
                up_indx++;
            }
            else if (vec[dwn_indx] > vec[pvot_indx])
            {
                dwn_indx--;
            }
            else if (vec[up_indx] > vec[pvot_indx] && vec[dwn_indx] <= vec[pvot_indx])
            {
                swap(vec[up_indx], vec[dwn_indx]);
            }
        }
        swap(vec[pvot_indx], vec[dwn_indx]);
        return dwn_indx;
    }
    else
    {
        return -1;
    }
}
template <typename T>
void SubQuickSort(vector<T>& vec, int strt_indx, int end_indx)
{
    int divider = QuickPass(vec, strt_indx, end_indx);
    if (divider != -1)
    {
        SubQuickSort(vec, strt_indx, divider - 1);
        SubQuickSort(vec, divider + 1, end_indx);
    }
}
template <typename T>
void QuickSort(vector<T>& vec)
{
    SubQuickSort(vec, 0, vec.size() - 1);
}
template <typename T>
bool IsSorted(vector<T> vec)
{
    for (int i = 0; i < vec.size() - 1; i++)
    {
        if (vec[i] > vec[i+1])
        {
            return false;
        }
    }
    return true;
}
vector<string> inputLine(string input, char delimeter)
{
  vector<string> out;
  int start = 0;
  for (int i = 0; i < input.size(); i++)
  {
    if (input[i] == delimeter)
    {
      out.push_back(input.substr(start, i - start));
      start = i + 1;
    }
  }
  out.push_back(input.substr(start, input.size() - start));
  return out;
}
void printStrings(vector<string> strings)
{
  for (int i = 0; i < strings.size(); i++)
  {
    cout << strings[i] << endl;
  }
}
void printIndex(vector<string> strings, int index)
{
    cout << strings[index] << endl;
}
void printIndexes(vector<string> strings, vector<int> indexes)
{
  for (int i = 0; i < indexes.size() - 1; i++)
  {
    cout << strings[indexes[i]] << ", ";
  }
  if (indexes.size() != 0)
  {
    cout << strings[indexes[indexes.size() - 1]];
  }
  cout << endl;
}
string getIndex(vector<string> strings, int index)
{
    return strings[index];
}
void printMovies(vector<Movie> movies)
{
  for (int i = 0; i < movies.size(); i++)
  {
    cout << movies[i].getTitle() << '	' << movies[i].rating();
    cout << '	' << movies[i].getCount() << endl;
  }
}
int searchName(vector<Movie> movies, string name)
{
    for (int i = 0; i < movies.size(); i++)
    {
        if (movies[i].getTitle() == name)
        {
            return movies[i].getID();
        }
    }
    return -1;
}
void printMovie(Movie movie)
{
    cout << movie.getTitle() << '	' << movie.rating();
    cout << '	' << movie.getCount() << endl;
}
void printFoundMovie(vector<Movie> movies, string name)
{
    printMovie(movies[searchName(movies, name) - 1]);
}
/*
void whitelist(vector<Movie>& movies, int genre)
{
    for (int i = 0; i < movies.size(); i++)
    {
        if (!movies[i].getGenre(genre))
        {
            movies.erase(movies.begin() + i);
        }
    }
}
void blacklist(vector<Movie>& movies, int genre)
{
    for (int i = 0; i < movies.size(); i++)
    {
        if (movies[i].getGenre(genre))
        {
            movies.erase(movies.begin() + i);
        }
    }
}
*/
void whitelist(vector<Movie>& movies, int genre)
{
    for (int i = movies.size() - 1; i >= 0; i--)
    {
        if (!movies[i].getGenre(genre))
        {
            movies.erase(movies.begin() + i);
        }
    }
}
void blacklist(vector<Movie>& movies, int genre)
{
    for (int i = movies.size() - 1; i >= 0; i--)
    {
        if (movies[i].getGenre(genre))
        {
            movies.erase(movies.begin() + i);
        }
    }
}
int main()
{
    vector<string> items = {};
    string input;
    ifstream Movies("u.item");
    ifstream Ratings("u.data");
    ifstream Genres("u.genre");
    //vector<string> inVctr;
    vector<Movie> movies;
    vector<int> ratingIDs;
    vector<int> ratings;
    //vector<int> genreIDs;
    vector<string> genreNames;
    vector<bool> temp_movie_genres;
    while (getline(Genres, input))
    {
        items = inputLine(input, '|');
        //PrintVector(items);
        //genreIDs.push_back(stoi(getIndex(items, 1)));
        genreNames.push_back(getIndex(items, 0));
    }
    while (getline(Movies, input))
    {
        items = inputLine(input, '|');
        //PrintVector(items);
        temp_movie_genres = {};
        for (int i = 5; i < 24; i++)
        {
            if (getIndex(items, i) == "0")
            {
                temp_movie_genres.push_back(false);
            }
            else if (getIndex(items, i) == "1")
            {
                temp_movie_genres.push_back(true);
            }
        }
        movies.emplace_back(stoi(getIndex(items, 0)), getIndex(items, 1), temp_movie_genres);
    }
    while (getline(Ratings, input))
    {
        items = inputLine(input, '	');
        //PrintVector(items);
        ratingIDs.push_back(stoi(getIndex(items, 1)));
        ratings.push_back(stoi(getIndex(items, 2)));
    }
    for (int i = 0; i < ratings.size(); i++)
    {
        movies[ratingIDs[i]].addRating(ratings[i]);
    }
    //printMovie(movies[searchName(movies, "Toy Story (1995)") - 1]);
    //printFoundMovie(movies, "Toy Story (1995)");
    QuickSort(movies);
    QuickSort(ratingIDs);
    //whitelist(movies, 1);
    //blacklist(movies, 1);
    printMovies(movies);
    //cout << movies.size() << endl;
    //printStrings(ratingIDs);
    //printStrings(ratings);
    return 0;
}