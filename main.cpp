// task_6_matrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <vector>
#include <array>
#include <assert.h>

#include "matrix.h"

int main()
{    
    
    matrix<int, 2, -1> mt0;
    assert(mt0.size() == 0);
    auto a = mt0[0][0];
    assert(a == -1);
    assert(mt0.size() == 0);
    mt0[100][100] = 314;
    assert(mt0[100][100] == 314);
    assert(mt0.size() == 1);
    /*
    for (auto c : mt0)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    */
    matrix<int, 1, -1> mt1;
    mt1[6] = 6;
    assert(mt1[0] == -1);
    assert(mt1[6] == 6);
    assert(mt1[0] == -1);
    mt1[5] = 5;
    assert(mt1[2] == -1);
    assert(mt1[5] == 5);

    mt1[6] = -1;
    assert(mt1[6] != 6);
    assert(mt1[6] == -1);
    
    matrix<int, 2, -1> mt2;
    mt2[5][6] = 56;
    assert(mt2[0][0] == -1);
    assert(mt2[1][0] == -1);
    assert(mt2[5][7] == -1);
    assert(mt2[5][6] == 56);
    mt2[5][7] = 57;
    assert(mt2[5][6] == 56);
    assert(mt2[6][6] == -1);
    assert(mt2[5][7] == 57);
    assert(mt2[1][0] == -1);
    mt2[5][6] = -1;
    assert(mt2[5][6] == -1);
    assert(mt2[5][7] == 57);
    mt2[5][7] = -1;
    assert(mt2[5][7] != 57);
    assert(mt2[5][7] == -1);

    matrix<int, 3, -1> mt3;
    mt3[5][6][7] = 567;
    assert(mt3[5][6][7] == 567);
    assert(mt3[6][6][7] == -1);
    assert(mt3[5][5][7] == -1);
    assert(mt3[5][6][8] == -1);
    mt3[5][6][8] = 568;
    mt3[5][6][9] = 569;
    mt3[6][6][7] = 667;
    mt3[5][7][7] = 577;

    assert(mt3[5][6][8] == 568);
    assert(mt3[5][6][9] == 569);
    assert(mt3[0][0][0] == -1);
    assert(mt3[6][6][7] == 667);
    assert(mt3[5][7][7] == 577);
    mt3[5][7][7] = -1;
    assert(mt3[5][7][7] == -1);
    mt3[7][6][7] = -1;
    assert(mt3[7][6][7] == -1);

    mt3[5][6][7] = -1;
    mt3[5][6][8] = -1;
    mt3[5][6][9] = -1;
    
    assert(mt3[5][6][7] == -1);
    assert(mt3[5][6][8] == -1);
    assert(mt3[5][6][9] == -1);
    assert(mt3[5][6][9] == -1);

    return 0;
}
