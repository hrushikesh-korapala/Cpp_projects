#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// extra fuctions used to check or print data
void print_sud(vector<vector<vector<int>>> &a)
{
    for (vector<vector<int>> A : a)
    {
        for (vector<int> B : A)
        {
            if (B.size() == 1)
            {
                cout << B[0] << ' ';
            }
            else
            {
                cout << '0' << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

void print_size(vector<vector<vector<int>>> &a)
{
    for (vector<vector<int>> A : a)
    {
        for (vector<int> B : A)
        {
            cout << B.size() << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

void removes(vector<int> &a, int b)
{
    for (vector<int>::iterator it = a.begin(); it != a.end(); it++)
    {
        if (*it == b)
        {

            a.erase(it);

            break;
        }
    }
}

int blanks(vector<vector<vector<int>>> &a)
{
    int ans = 0;
    for (vector<vector<int>> A : a)
    {
        for (vector<int> B : A)
        {
            if (B.size() != 1)
            {
                ans++;
            }
        }
    }
    return ans;
}

// solvers these reduce the number of possibilities for a cell
int brc_check(vector<vector<vector<int>>> &sud)
{
    int ans = 0;
    // box checking
    int x, y, an, i, j;
    for (int e = 0; e < 3; e++)
    {
        for (int d = 0; d < 3; d++)
        {
            i = e * 3;
            j = d * 3;

            for (int l = 1; l < 10; l++)
            {
                int h = 0;
                for (int m = 0; m < 3; m++)
                {
                    for (int z = 0; z < 3; z++)
                    {
                        if (sud[i + m][j + z].size() != 1)
                        {
                            for (int r : sud[i + m][j + z])
                            {
                                if (r == l)
                                {
                                    h++;
                                    x = i + m, y = j + z, an = r;
                                    break;
                                }
                            }
                        }
                        if (h > 1)
                        {
                            break;
                        }
                    }
                    if (h > 1)
                    {
                        break;
                    }
                }
                if (h == 1 && sud[x][y].size() != 1)
                {
                    ans++;
                    sud[x][y] = vector<int>{an};
                }
                x = -1, y = -1, an = -1;
            }
        }
    }

    // row checking
    for (int i = 0; i < 9; i++)
    {

        for (int l = 1; l < 10; l++)
        {
            int h = 0;
            for (int j = 0; j < 9; j++)
            {
                for (int r : sud[i][j])
                {
                    if (r == l)
                    {
                        h++;
                        x = i, y = j, an = r;
                        break;
                    }
                }
                if (h > 1)
                {
                    break;
                }
            }
            if (h == 1 && sud[x][y].size() != 1)
            {
                ans++;
                sud[x][y] = vector<int>{an};
            }
            x = -1, y = -1, an = -1;
        }
    }

    // column checking
    for (int i = 0; i < 9; i++)
    {

        for (int l = 1; l < 10; l++)
        {
            int h = 0;
            for (int j = 0; j < 9; j++)
            {
                for (int r : sud[j][i])
                {
                    if (r == l)
                    {
                        h++;
                        y = i, x = j, an = r;
                        break;
                    }
                }
                if (h > 1)
                {
                    break;
                }
            }
            if (h == 1 && sud[x][y].size() != 1)
            {
                ans++;
                sud[x][y] = vector<int>{an};
            }
            x = -1, y = -1, an = -1;
        }
    }
    return ans;
}

void element_check(int i, int j, vector<vector<vector<int>>> &sud)
{
    // row
    for (int k = 0; k < 9; k++)
    {

        if (sud[i][k].size() == 1 && j != k)
        {
            removes(sud[i][j], sud[i][k][0]);
            if (sud[i][j].size() == 1)
            {
                return;
            }
        }
        // column
        for (int k = 0; k < 9; k++)
        {

            if (sud[k][j].size() == 1 && i != k)
            {
                removes(sud[i][j], sud[k][j][0]);
                if (sud[i][j].size() == 1)
                {
                    return;
                }
            }
        }
        // box
        int l = i - i % 3, m = j - j % 3;
        for (int h = 0; h < 3; h++)
        {
            for (int g = 0; g < 3; g++)
            {
                if (sud[l + h][m + g].size() == 1 && (l + h != i || m + g != j))
                {
                    removes(sud[i][j], sud[l + h][m + g][0]);
                    if (sud[i][j].size() == 1)
                    {
                        return;
                    }
                }
            }
        }
    }
}
void reduce_check(vector<vector<vector<int>>> &sud)
{
    int o = blanks(sud);
    while (o != 0)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (sud[i][j].size() != 1)
                {
                    element_check(i, j, sud);
                }
            }
        }
        int bl = blanks(sud);

        if (bl == o)
        {

            return;
        }
        else
        {
            o = bl;
        }
    }
}

int main()
{
    vector<vector<vector<int>>> sudoku;

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    vector<vector<int>> temp;

    for (int j = 0; j < 9; j++)
    {
        temp.push_back(nums);
    }
    for (int i = 0; i < 9; i++)
    {
        sudoku.push_back(temp);
    }
    int x = 0, y = 0, val, n;
    n = 81;
    while (n--)
    {
        cin >> val;

        if (y > 8)
        {
            x++;
            y = 0;
        }
        if (val != 0)
        {
            sudoku[x][y] = vector<int>{val};
        }
        y++;
    }

    int condition = 1;
    while (condition != 0)
    {
        reduce_check(sudoku);
        condition = brc_check(sudoku);
    }

    if (blanks(sudoku) != 0)
    {
        cout << "ERROR :: This is Fucking hard sudoku: " <<blanks(sudoku)<< endl;
        print_size(sudoku);
    }
    else
    {
        print_sud(sudoku);
    }
    
    return 0;
}