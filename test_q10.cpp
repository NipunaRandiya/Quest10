#include <iostream>
using namespace std;

int Random_array(int count)
{
    int c;
    c = rand() % (count * count);
    return c;
}

class Game
{
public:
    int row, col;
    char arr[20][20];
    Game(int in_row, int in_col, int bomb_count);
    void print_arr();
    void bomb_count();
};

Game::Game(int in_row, int in_col, int bomb_count)
{
    row = in_row;
    col = in_col;
    for (int i = 0; i < in_row; i++)
    {
        for (int j = 0; j < in_col; j++)
        {
            arr[i][j] = 'C';
        }
    }
    for (int i = 0; i < bomb_count; i++)
    {
        int position;
        int selected_row, selected_col;
        position = Random_array(in_row);
        selected_row = position / in_row;
        selected_col = position % in_row;
        if (arr[selected_row][selected_col] == 'C')
        {
            arr[selected_row][selected_col] = 'M';
        }
        else
        {
            i--;
        }
    }
}
void Game::print_arr()
{
    for (int i = 0; i < row; i++)
    {
        cout << "      ";
        for (int j = 0; j < col; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}
void Game::bomb_count()
{
    for (int i = 0; i < row; i++)
    {

        for (int j = 0; j < col; j++)
        {
            int No_of_bombsAround = 0;
            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (arr[m][n] == 'M')
                    {

                        No_of_bombsAround++;
                    }
                }
            }
            if (arr[i][j] != 'M')
            {
                if (No_of_bombsAround == 0)
                {
                    arr[i][j] = '.';
                }
                else
                {
                    arr[i][j] = char(No_of_bombsAround + 48);
                }
            }
        }
    }
}

int main()
{
    int option;
    Game game1(10, 10, 12);
    Game game2(12, 12, 18);
    Game game3(20, 20, 24);
    cout << "                           --------------------" << endl;
    cout << "                             Mine Sweeper game" << endl;
    cout << "                           --------------------" << endl;
    cout << endl;
    cout << "     Field Option             Size (grid size)             No. of Mines" << endl;
    cout << "       1                        10-by-10                     12        " << endl;
    cout << "       2                        15-by-15                     18        " << endl;
    cout << "       3                        20-by-20                     24        " << endl;
    cout << endl;
    cout << "Enter the Option you want to select: ";
    cin >> option;
    switch (option)
    {
    case 1:
        cout << "Selected Option 1 - Grid size 10-by-10" << endl;
        game1.bomb_count();
        game1.print_arr();
        break;
    case 2:
        cout << "Selected Option 2 - Grid size 12-by-12" << endl;
        game2.bomb_count();
        game2.print_arr();
        break;
    case 3:
        cout << "Selected Option 3 - Grid size 20-by-20" << endl;
        game3.bomb_count();
        game3.print_arr();
        break;
    default:
        cout << "Error : Invalid Input" << endl;
        break;
    }
    return 0;
}
