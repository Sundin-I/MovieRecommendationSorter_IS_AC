# Movie Recommendation Sorter

This project is a menu-based C++ CLI program that recommends movies from the
MovieLens 100K dataset. It loads movie information, calculates a recommendation
score for each movie, shows top-ranked movies, searches by title, filters by
genre, and compares two algorithms: a Min Heap Top-K approach and QuickSort.

Think of it like a tiny movie recommendation app that runs in the terminal.
Instead of clicking buttons, you type a number from the menu and press Enter.

## Team

- Isabelle Sundin:  https://github.com/Sundin-I
- Aubrey Corcoran:  https://github.com/CtrlAubDel
- Vincent Pinolini: https://github.com/vpinolini

## What You Need

If you only want to run the already-built program on Windows, you need:

- This project folder
- The MovieData folder that is already included in the project
- A terminal, such as the terminal inside VS Code, Command Prompt, or Aubrey's favorite, Git Bash!

If you want to rebuild the program from the source code, you also need:

- A C++ compiler
- CMake

## Easiest Way to Run the Program

1. Open the project folder.
2. Open a terminal in that folder.
   - In VS Code, you can use Terminal > New Terminal.
   - In Windows File Explorer, you can click the folder path bar, type
     "powershell", and press Enter.
       - Or, also in FIle Explorer, you can right click the root directory of the GitHub repo and click "Open in Git Bash"
3. Make sure your terminal is inside this project folder:

   ```powershell
   C:\[YOURLOCALPATHHERE]\MovieRecommendationSorter_IS_AC_VP
   ```

4. Run the program:

   ```powershell
   .\build\Main.exe
   ```

Important: Make sure to run the command from the main project folder, not from inside the
build folder. The program needs to find the MovieData folder.

## How to Use the Menu

When the program starts, it prints this menu:

```text
------Movie Recommendation Menu: ------
1. Load dataset
2. Display total count of movies and ratings loaded
3. Calculate movie recommendation scores
4. Display top movie recommendations
5. Display top movie recommendations by genre
6. Compare algorithm performance/runtime
7. Search movie by title
8. Exit
Enter choice:
```

Type the number for what you want to do, then press Enter.

For the smoothest experience, use the options in this order first:

1. Type 1 to load the movie dataset.
2. Type 3 to calculate recommendation scores.
3. Type 4, 5, 6, or 7 to use the recommendation features.
4. Type 8 when you are finished.

## Example Walkthrough

Here is a simple first run:

```text
Enter choice:
1
Loaded movie dataset...

Enter choice:
3
Successfully calculated the scores!

Enter choice:
4
Type how many movies you want rated: 10
```

The program will then print the top 10 recommended movies with their scores.

## What Each Option Does

### 1. Load dataset

Loads the movie titles and genre information from the MovieLens dataset.

Use this first!!!

### 2. Display total count of movies and ratings loaded

Shows how many movies were loaded. It also shows how many ratings were loaded,
but the ratings count will only be filled in after option 3.

### 3. Calculate movie recommendation scores

Reads the rating data and calculates a recommendation score for each movie.

Use this before asking for top recommendations.

### 4. Display top movie recommendations

Shows the top k recommended movies overall.

The program will ask:

```text
Type how many movies you want rated:
```

If you want the top 10 movies, type:

```text
10
```

### 5. Display top movie recommendations by genre

Shows the top k recommended movies from one genre.

The program will ask how many movies you want, then ask for a genre. Example:

```text
Type how many movies you want: 5
Type a genre: Comedy
```

Available genres include:

```text
unknown, Action, Adventure, Animation, Children's, Comedy, Crime,
Documentary, Drama, Fantasy, Film-Noir, Horror, Musical, Mystery,
Romance, Sci-Fi, Thriller, War, Western
```

Genre search is not case-sensitive, so "Comedy", "comedy", and "COMEDY" all
work.

### 6. Compare algorithm performance/runtime

Compares the Min Heap Top-K algorithm and QuickSort on the same movie data.

The program prints how long each algorithm took in microseconds and whether
they produced the same Top-K ranking.

### 7. Search movie by title

Searches for movies by a title keyword.

Example:

```text
Type a movie title keyword: toy
```

This can find movies with toy in the title, such as "Toy Story (1995)"".
Search is not case-sensitive.

### 8. Exit

Closes the program.

## If Something Goes Wrong

If you see:

```text
Please load the movie dataset first.
```

Type 1 and press Enter.

If you see:

```text
Please calculate movie recommendation scores first.
```

Type 3 and press Enter.

If you see:

```text
Failed to open file...
```

Make sure:

- You are running the program from the main project folder.
- The MovieData folder is still inside the project.
- The files MovieData/u.item and MovieData/u.data exist.

## How to Rebuild the Program

If the executable is missing or you want to compile the project yourself, run:

```powershell
cmake -S . -B build
cmake --build build
```

Then start the program again:

```powershell
.\build\Main.exe
```

## How to Run the Tests

After building the project, run:

```powershell
.\build\Tests.exe
```

The tests check important project logic, including sorting and heap behavior.

## Dataset Credit

This project uses the MovieLens 100K dataset from GroupLens:

https://grouplens.org/datasets/movielens/100k/

The dataset contains 100,000 user ratings and movie information used by this
program to calculate recommendation scores.
