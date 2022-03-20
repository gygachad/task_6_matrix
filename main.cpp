// task_6_matrix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <vector>
#include <array>

#include "matrix.h"

#define DBG_CHECK(condition) if(!(condition)){__debugbreak();}

int main()
{    
    matrix<int, 1, -1> mt1;
    mt1[6] = 6;
    DBG_CHECK(mt1[0] == -1);
    DBG_CHECK(mt1[6] == 6);
    DBG_CHECK(mt1[0] == -1);
    mt1[5] = 5;
    DBG_CHECK(mt1[2] == -1);
    DBG_CHECK(mt1[5] == 5);

    mt1[6] = -1;
    DBG_CHECK(mt1[6] != 6);
    DBG_CHECK(mt1[6] == -1);
    
    matrix<int, 2, -1> mt2;
    mt2[5][6] = 56;
    DBG_CHECK(mt2[0][0] == -1);
    DBG_CHECK(mt2[1][0] == -1);
    DBG_CHECK(mt2[5][7] == -1);
    DBG_CHECK(mt2[5][6] == 56);
    mt2[5][7] = 57;
    DBG_CHECK(mt2[5][6] == 56);
    DBG_CHECK(mt2[6][6] == -1);
    DBG_CHECK(mt2[5][7] == 57);
    DBG_CHECK(mt2[1][0] == -1);
    mt2[5][6] = -1;
    DBG_CHECK(mt2[5][6] == -1);
    DBG_CHECK(mt2[5][7] == 57);
    mt2[5][7] = -1;
    DBG_CHECK(mt2[5][7] != 57);
    DBG_CHECK(mt2[5][7] == -1);

    matrix<int, 3, -1> mt3;
    mt3[5][6][7] = 567;
    DBG_CHECK(mt3[5][6][7] == 567);
    DBG_CHECK(mt3[6][6][7] == -1);
    DBG_CHECK(mt3[5][5][7] == -1);
    DBG_CHECK(mt3[5][6][8] == -1);
    mt3[5][6][8] = 568;
    mt3[5][6][9] = 569;
    mt3[6][6][7] = 667;
    mt3[5][7][7] = 577;

    DBG_CHECK(mt3[5][6][8] == 568);
    DBG_CHECK(mt3[5][6][9] == 569);
    DBG_CHECK(mt3[0][0][0] == -1);
    DBG_CHECK(mt3[6][6][7] == 667);
    DBG_CHECK(mt3[5][7][7] == 577);
    mt3[5][7][7] = -1;
    DBG_CHECK(mt3[5][7][7] == -1);
    mt3[7][6][7] = -1;
    DBG_CHECK(mt3[7][6][7] == -1);

    mt3[5][6][7] = -1;
    mt3[5][6][8] = -1;
    mt3[5][6][9] = -1;
    
    DBG_CHECK(mt3[5][6][7] == -1);
    DBG_CHECK(mt3[5][6][8] == -1);
    DBG_CHECK(mt3[5][6][9] == -1);
    DBG_CHECK(mt3[5][6][9] == -1);

    return 0;
}
