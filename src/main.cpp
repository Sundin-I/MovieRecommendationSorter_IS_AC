#include <iostream>
#include "movieCollection.h"
#include "minHeap.h"

using namespace std;

void printingTheMenu() {
    cout << endl;
    cout<<"------Movie Recommendation Menu: ------" <<endl;
    cout<<"1. Load dataset" <<endl;
    cout<<"2. Display total count of movie recommendations" <<endl;
    cout<<"3. Calculate movie recommendation scores" <<endl;
    cout<<"4. Display top movie recommendations" <<endl;
    cout<<"5. Display top movie recommendations by genre" <<endl;
    cout<<"6. Compare algorithm performance/runtime" <<endl;
    cout<<"7. Search movie by title" <<endl;
    cout<<"8. Exit" <<endl;
    cout<<"Enter choice: " <<endl;
}

int main(){

    movieCollection movieData;

    string userInput;

    while (true) {
        printingTheMenu();

        getline(cin, userInput);

        if (userInput == "1") {
            movieData.loadsDataSet();
        }
        else if (userInput == "2") {
            movieData.totalCountofRecommendation();
        }
        else if (userInput == "3") {
            movieData.calculationofScores();
        }
        else if (userInput == "4") {
            movieData.showTopKmovies();
        }
        else if (userInput == "5") {
            movieData.showTopKmovies_bygenre();
        }
        else if (userInput == "6") {
            movieData.algorithmComparision();
        }
        else if (userInput == "7") {
            movieData.searchTitles();
        }
        else if (userInput == "8") {
            break;
        }



        }
    }



