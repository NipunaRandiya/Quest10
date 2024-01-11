#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Class representing a cell in the Minesweeper board
class Cell 
{
public:
    bool isMine;
    bool isRevealed;
    bool isFlagged;
    int adjacentMines;

    Cell() : isMine(false), isRevealed(false), isFlagged(false), adjacentMines(0) {}
};

// Class representing the Minesweeper game board
class MinesweeperGame 
{
private:
    int numRows;
    int numCols;
    vector<vector<Cell>> gameBoard;

    // Place mines randomly on the board
    void placeMines(int numMines) 
    {
        int totalCells = numRows * numCols;
        while (numMines > 0) 
        {
            int randRow = rand() % numRows;
            int randCol = rand() % numCols;
            if (!gameBoard[randRow][randCol].isMine) 
            {
                gameBoard[randRow][randCol].isMine = true;
                numMines--;
            }
        }
    }

    // Calculate the number of adjacent mines for each cell on the board
    void calculateAdjacentMines() 
    {
        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < numCols; ++j) 
            {
                if (!gameBoard[i][j].isMine) 
                {
                    for (int ni = -1; ni <= 1; ++ni) 
                    {
                        for (int nj = -1; nj <= 1; ++nj) 
                        {
                            int niCoord = i + ni;
                            int njCoord = j + nj;
                            if (niCoord >= 0 && niCoord < numRows && njCoord >= 0 && njCoord < numCols &&
                                gameBoard[niCoord][njCoord].isMine) 
                                {
                                gameBoard[i][j].adjacentMines++;
                            }
                        }
                    }
                }
            }
        }
    }

public:
    // Constructor to initialize the Minesweeper game
    MinesweeperGame(int rows, int cols, int mines) : numRows(rows), numCols(cols) 
    {
        gameBoard.resize(numRows, vector<Cell>(numCols, Cell()));
        placeMines(mines);
        calculateAdjacentMines();
    }

    // Display the current state of the Minesweeper game
    void displayGame() 
    {
        cout << "----------------MINE SWEEPER GAME-----------------" << endl;
        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < numCols; ++j) 
            {
                if (gameBoard[i][j].isRevealed) 
                {
                    if (gameBoard[i][j].isMine) 
                    {
                        cout << " * ";
                    }
                    else {
                        cout << " " << gameBoard[i][j].adjacentMines << " ";
                    }
                }
                else if (gameBoard[i][j].isFlagged) 
                {
                    cout << " F ";
                }
                else 
                {
                    cout << " C ";  // C represents a covered (unrevealed) cell
                }
            }
            cout << endl;
        }
    }

    // Reveal a cell on the board
    void revealCell(int row, int col) 
    {
        if (row >= 0 && row < numRows && col >= 0 && col < numCols && !gameBoard[row][col].isRevealed &&
            !gameBoard[row][col].isFlagged) 
            {
            gameBoard[row][col].isRevealed = true;
            if (gameBoard[row][col].adjacentMines == 0) 
            {
                for (int ni = -1; ni <= 1; ++ni) 
                {
                    for (int nj = -1; nj <= 1; ++nj) 
                    {
                        revealCell(row + ni, col + nj);
                    }
                }
            }
        }
    }

    // Toggle flag on a cell
    void toggleFlag(int row, int col) 
    {
        if (row >= 0 && row < numRows && col >= 0 && col < numCols) 
        {
            gameBoard[row][col].isFlagged = !gameBoard[row][col].isFlagged;
        }
    }

    // Check if the game is won
    bool isGameWon() 
    {
        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < numCols; ++j) 
            {
                if (!gameBoard[i][j].isRevealed && !gameBoard[i][j].isMine) 
                {
                    return false;
                }
            }
        }
        return true;
    }

    // Check if the game is lost
    bool isGameLost() 
    {
        for (int i = 0; i < numRows; ++i) 
        {
            for (int j = 0; j < numCols; ++j) 
            {
                if (gameBoard[i][j].isRevealed && gameBoard[i][j].isMine) 
                {
                    return true;
                }
            }
        }
        return false;
    }
};

// Function to convert a letter (column) to its corresponding index
int convertLetterToIndex(char letter, int max) 
{
    // Note: Assumes input is uppercase letter
    switch (letter) 
    {
    case 'A':
        return 0;
    case 'B':
        return 1;
        // ... Repeat for other letters
    default:
        return -1;  // Invalid input
    }
}

int main() 
{
    srand(static_cast<unsigned>(time(nullptr)));

    //defining variables
    int numRows, numCols, numMines;
    int level_selection;
    int status_check;

    //first user interface defining
    cout << "----------------MINE SWEEPER GAME-----------------" << endl;
    cout << endl;
    cout << "Conditions of the game are as follows:"<< endl;
    cout << "\t1. Player wins the game if he corretly flags all the mine buried points" << endl;
    cout << "\t2. Player looses the game if he uncovered a mine buried location" << endl;
    cout << "\t3. If player reveal a location with a mine, the updated map will be displayed to the player and current player will leave the game" << endl;
    cout << "would you like to continue? .Enter the index please(1.yes and 2.no)" << endl;
    cin  >> status_check;

    //classification based on the difficulty level
    if (status_check==1)
    { 
        cout << "Difficulty Levels: " << endl;
        cout << "\t1. Easy (10x10 grid with 12 mines)" << endl;
        cout << "\t2. Medium (15x15 grid with 18 mines)" << endl;
        cout << "\t3. Hard (20x20 grid with 24 mines)" << endl;
        cout << "Enter Difficulty Level: ";
        cin >> level_selection;

        if (level_selection == 1) 
        {
            numRows = 10;
            numCols = 10;
            numMines = 12;
        }
        else if (level_selection == 2) 
        {
            numRows = 15;
            numCols = 15;
            numMines = 18;
        }
        else if (level_selection == 3) 
        {
            numRows = 20;
            numCols = 20;
            numMines = 24;
        }
        else 
        {
            cout << "Error: Invalid Difficulty Level selected. please try again." << endl;
            return 1;
        }
    
        MinesweeperGame game(numRows, numCols, numMines);

        while (true) 
        {
            game.displayGame();

            string command;
            cout << "Enter the command:\nCOmmand sholud be given in the order <row_number> <column_number> <command> \n(e.g., {A B R} to reveal, {A B F} to flag):\n ";
            char row, col;
            cin >> row >> col;
            int iRow = convertLetterToIndex(row, numRows);
            int iCol = convertLetterToIndex(col, numCols);
            cin >> command;

            if (command == "F") 
            {
                game.toggleFlag(iRow, iCol);
            }
            else if (command == "R") 
            {
                if (game.isGameLost()) 
                {
                    cout << "Game Over! You hit a mine." << endl;
                    break;
                }
                game.revealCell(iRow, iCol);
                if (game.isGameWon()) 
                {
                    cout << "Congratulations! You cleared the board without hitting any mines." << endl;
                    break;
                }
            }
        }
    }
    else if (status_check==2)
    {
        cout << "Thank you for participating the game. see you" << endl;
    }
    else
    {
        cout << "Wrong input. sorry. try again" <<endl;
        return(0);
    }

    return 0;
}
