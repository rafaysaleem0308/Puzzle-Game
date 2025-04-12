#include <iostream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include<fstream>
#include<Windows.h>
using namespace std;
int arr[5][5];
int initialState[5][5];
int goalState[5][5];
const int KEY_READER = 224;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_RIGHT = 77;
const int KEY_LEFT = 75;
string path;
void init(int arr[5][5]);
void goal(int arr[5][5]);
bool is_Solvable(int initialState[5][5], int goalState[5][5]);
void make_moves(int arr[5][5], int arr1[5][5]);
void findInInitial(int arr[5][5], char key);
bool findInGoal(int num, int arr[5][5]);
void display(int arr[5][5], int arr1[5][5]);
void print_path();
bool boolgoal(int init[5][5], int goal[5][5]);
string error = "";
int main()
{
    string save_reader;
    char choice;
    system("Color B5");
    int initialState[5][5], goalState[5][5];
    srand(time(NULL));
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t[1] Start Game: " << endl;
    cout << "\t\t\t\t\t\t[2] Resume the Game: " << endl;

    choice = _getch();
    system("cls");
    if (choice == '1')
    {
        init(initialState);
        goal(goalState);
    }
    else if (choice == '2')
    {
        ifstream reader;
        reader.open("game.txt", ios::in);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5;)
            {
                reader >> save_reader;
                if (save_reader != " ")
                {
                    initialState[i][j] = atoi(save_reader.c_str());
                    j++;
                }
            }
        }
        reader.close();
        reader.open("goalstate.txt", ios::in);
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5;)
            {
                reader >> save_reader;
                if (save_reader != " ")
                {
                    goalState[i][j] = atoi(save_reader.c_str());
                    j++;
                }
            }
        }
        reader.close();
        reader.open("printpath.txt", ios::in);
        for (int i = 0; path[i] != '\0'; i++)
            reader >> path[i];
        reader.close();
    }
    else
    {
        cout << "You've Enter Wrong Input: " << endl;
        Sleep(2000);
        system("cls");
        main();
    }
    system("Color 05");
    make_moves(initialState, goalState);

    cout << endl;
    system("pause");
    return 0;
}
void init(int arr[5][5])
{
    srand(time(0));
    int num = 0, ran, i, j, s = 0, t = 0, temp, l, m;
    cout << "       Initial Board      " << endl;
    cout << "--------------------------" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            arr[i][j] = num;
            num++;
        }
    }
    for (int k = 0; k < 100; k++)
    {
        ran = rand() % 5;
        i = ran;
        ran = rand() % 5;
        j = ran;
        ran = rand() % 5;
        l = ran;
        ran = rand() % 5;
        m = ran;

        temp = arr[i][j];
        arr[i][j] = arr[l][m];
        arr[l][m] = temp;
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "|";
        for (int j = 0; j < 5; j++)
        {
            if (arr[i][j] == 0)
            {
                cout << setw(3) << " " << setw(2) << "|";
            }
            else
                cout << setw(3) << arr[i][j] << setw(2) << "|";
        }
        cout << endl;
        cout << "--------------------------";
        cout << endl;
    }
    for(int i = 0; i < 5; i++)
    {
    	for(int j = 0; j < 5; j++)
    		initialState[i][j] = arr[i][j];
	}
}
void goal(int arr[5][5])
{
    srand(time(0));
    int num = 0, ran, i, j, s = 0, t = 0, temp, l, m;
    cout << "         GOAL BOARD       " << endl;
    cout << "--------------------------" << endl;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            arr[i][j] = num;
            num++;
        }
    }
    for (int k = 0; k < 500; k++)
    {
        ran = rand() % 5;
        i = ran;
        ran = rand() % 5;
        j = ran;
        ran = rand() % 5;
        l = ran;
        ran = rand() % 5;
        m = ran;

        temp = arr[i][j];
        arr[i][j] = arr[l][m];
        arr[l][m] = temp;
    }

    for (int i = 0; i < 5; i++)
    {
        cout << "|";
        for (int j = 0; j < 5; j++)
        {
            if (arr[i][j] == 0)
            {
                cout << setw(3) << " " << setw(2) << "|";
            }
            else
                cout << setw(3) << arr[i][j] << setw(2) << "|";
        }
        cout << endl;
        cout << "--------------------------";
        cout << endl;
    }
    for(int i = 0; i < 5; i++)
    {
    	for(int j = 0; j < 5; j++)
    		goalState[i][j] = arr[i][j];
	}

}
bool boolgoal(int init[5][5], int goal[5][5])
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (init[i][j] == goal[i][j])
            {
                count++;
            }
        }
    }
    if (count == 25)
    {

        return false;
    }
    else
    {
        return true;
    }
}
bool is_Solvable(int initialState[5][5], int goalState[5][5])
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (findInGoal(initialState[i][j], goalState) == false)
            {
                return false;
            }
        }
    }
    return true;
}

bool findInGoal(int num, int arr[5][5])
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (num == arr[i][j]) {
                return true;
            }
        }
    }
    return false;
}
void legal_moves(char key, int arr[5][5])
{
    char checkkey = 0;
    bool stop = false;
    bool check_25 = true, up = true, down = true, left = true, right = true;
    int state[5][5] = {}, check_i = 0, check_j = 0, j = 0, i = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (arr[i][j] == 0)
            {
                //checking if cursor is empty//

                if ((i == 0 && j == 0) && (key == KEY_LEFT || key == KEY_UP))
                {
                    error = "YOU CAN MOVE ONLY RIGHT AND DOWNWARD";
                    stop = true;
                    break;
                }
                if ((i == 0 && j == 1) && (key == KEY_UP))
                {
                    error = "YOU CAN MOVE LEFT,RIGHT AND DOWNWARD ";
                    stop = true;
                    break;
                }
                if ((i == 0 && j == 2) && (key == KEY_UP))
                {
                    error = "YOU CAN MOVE LEFT,RIGHT AND DOWNWARD";
                    stop = true;
                    break;
                }
                if ((i == 0 && j == 3) && (key == KEY_UP))
                {
                    error = "YOU CAN MOVE LEFT,RIGHT AND DOWNWARD";
                    stop = true;
                    break;

                }
                if ((i == 0 && j == 4) && (key == KEY_UP || key == KEY_RIGHT))
                {
                    error = "YOU CAN MOVE LEFT AND DOWNWARD";
                    stop = true;
                    break;

                }
                if ((i == 1 && j == 0) && (key == KEY_LEFT))
                {
                    error = "YOU CAN MOVE RIGHT,UP AND DOWNWARD";
                    stop = true;
                    break;
                }
                if ((i == 1 && j == 4) && (key == KEY_RIGHT))
                {
                    error = "YOU CAN MOVE LEFT,UP AND DOWNWARD";
                    stop = true;
                    break;

                }
                if ((i == 2 && j == 0) && (key == KEY_LEFT))
                {
                    error = "YOU CAN MOVE UP,RIGHT AND DOWNWARD";
                    stop = true;
                    break;
                }
                if ((i == 2 && j == 4) && (key == KEY_RIGHT))
                {
                    error = "YOU CAN MOVE UP,LEFT AND DOWNWARD";
                    stop = true;
                    break;

                }
                if ((i == 3 && j == 0) && (key == KEY_LEFT))
                {
                    error = "YOU CAN MOVE UP,RIGHT AND DOWNWARD";
                    stop = true;
                    break;

                }
                if ((i == 3 && j == 4) && (key == KEY_RIGHT))
                {
                    error = "YOU CAN MOVE UP,LEFT AND DOWNWARD";
                    stop = true;
                    break;

                }
                if ((i == 4 && j == 0) && (key == KEY_LEFT || key == KEY_DOWN))
                {
                    error = "YOU CAN MOVE UP AND RIGHT";
                    stop = true;
                    break;

                }
                if ((i == 4 && j == 1) && (key == KEY_DOWN))
                {
                    error = "YOU CAN MOVE UP,LEFT AND RIGHT";
                    stop = true;
                    break;

                }
                if ((i == 4 && j == 2) && (key == KEY_DOWN))
                {
                    error = "YOU CAN MOVE UP,LEFT AND RIGHT";
                    stop = true;
                    break;
                }

                if ((i == 4 && j == 3) && key == KEY_DOWN)
                {
                    error = "YOU CAN MOVE UP,LEFT AND RIGHT";
                    stop = true;
                    break;

                }
                if ((i == 4 && j == 4) && (key == KEY_RIGHT || key == KEY_DOWN))
                {
                    error = "YOU CAN MOVE UP AND LEFT";
                    stop = true;
                    break;

                }
            }
        }



        if (stop) {
            break;
        }
    }

}

void make_moves(int arr[5][5], int arr1[5][5])
{
    ofstream out;
    int moves = 0;

    while (true) {

        int c = 0;
        system("cls");

        display(arr, arr1);
        cout << error << endl;
        error = "";
        c = _getch();
            if (c == KEY_READER)
            {
                switch ((c = _getch()))
                {
                case KEY_UP:
                    legal_moves(c, arr);
                    findInInitial(arr, 'd');
                    path += "d, ";
                    moves++;
                    break;
                case KEY_DOWN:
                    legal_moves(c, arr);
                    findInInitial(arr, 'u');
                    path += "u, ";
                    moves++;
                    break;
                case KEY_LEFT:
                    legal_moves(c, arr);
                    findInInitial(arr, 'r');
                    path += "r, ";
                    moves++;
                    break;
                case KEY_RIGHT:
                    legal_moves(c, arr);
                    findInInitial(arr, 'l');
                    path += "l, ";
                    moves++;
                    break;
                }
            }
            else
            {
                switch (c)
                {
                case 'C': case 'c':
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                            initialState[i][j] = goalState[i][j];
                    }
                    break;
                case 's': case 'S':
                    out.open("game.txt", ios::out);
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            out << arr[i][j] << " ";
                        }
                        out << endl;
                    }
                    out.close();
                    out.open("goalstate.txt", ios::out);
                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 5; j++)
                        {
                            out << arr1[i][j] << " ";
                        }
                        out << endl;
                    }
                    out.close();
                    out.open("printpath.txt", ios::out);
                    for (int i = 0; path[i] != '\0'; i++)
                    {
                        out << path[i];
                        if (i % 10)
                            out << endl;
                    }
                    out.close();
                    exit(0);
                    break;
                case 'q': case 'Q':
                    exit(0);
                default:
                    break;
                }
            }
    }
    out.close();
    cout << "Total Moves: " << moves << endl;
    print_path();
}
void display(int arr[5][5], int arr1[5][5]) {
    cout << "      Initial State:\n";
    cout << "--------------------------";
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "|";
        for (int j = 0; j < 5; j++)
        {
            if (arr[i][j] == 0)
            {
                cout << setw(3) << " " << setw(2) << "|";
            }
            else
                cout << setw(3) << arr[i][j] << setw(2) << "|";
        }
        cout << endl;
        cout << "--------------------------";
        cout << endl;
    }
    cout << "\n      Goal State:\n";
    cout << "--------------------------";
    cout << endl;

    for (int i = 0; i < 5; i++)
    {
        cout << "|";
        for (int j = 0; j < 5; j++)
        {
            if (arr1[i][j] == 0)
            {
                cout << setw(3) << " " << setw(2) << "|";
            }
            else
                cout << setw(3) << arr1[i][j] << setw(2) << "|";
        }
        cout << endl;
        cout << "--------------------------";
        cout << endl;
    }
}
void findInInitial(int arr[5][5], char key)
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
        {
            if (key == 'u' && (i - 1) >= 0 && arr[i - 1][j] == 0)
            {
                swap(arr[i][j], arr[i - 1][j]);
                return;
            }
            else if (key == 'd' && (i + 1) < 5 && arr[i + 1][j] == 0)
            {
                swap(arr[i][j], arr[i + 1][j]);
                return;
            }
            else if (key == 'l' && (j - 1) >= 0 && arr[i][j - 1] == 0)
            {
                swap(arr[i][j], arr[i][j - 1]);
                return;
            }
            else if (key == 'r' && (j + 1) < 5 && arr[i][j + 1] == 0)
            {
                swap(arr[i][j], arr[i][j + 1]);
                return;
            }
        }
    }
}
void print_path()
{
    for (int i = 0; path[i] != '\0'; i++)
    {
        cout << path[i] << " ";
        if (i % 10)
            cout << endl;
    }
}