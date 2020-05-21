//
//  main.cpp
//  sudoku_solver
//
//  Created by Tyler Ruddy on 5/21/20.
//  Copyright © 2020 Tyler Ruddy. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool is_promising(vector<vector<int>>& board, int row, int col);

void solver(vector<vector<int>>& board, int row, int col, bool solution);

void print_grid(vector<vector<int>>& board);

int main(/*int argc, const char * argv[]*/) {
    vector<vector<int>> example = { { 0, 3, 0, 0, 1, 0, 0, 6, 0 },
                                    { 7, 5, 0, 0, 3, 0, 0, 4, 8 },
                                    { 0, 0, 6, 9, 8, 4, 3, 0, 0 },
                                    { 0, 0, 3, 0, 0, 0, 8, 0, 0 },
                                    { 9, 1, 2, 0, 0, 0, 6, 7, 4 },
                                    { 0, 0, 4, 0, 0, 0, 5, 0, 0 },
                                    { 0, 0, 1, 6, 7, 5, 2, 0, 0 },
                                    { 6, 8, 0, 0, 9, 0, 0, 1, 5 },
                                    { 0, 9, 0, 0, 4, 0, 0, 3, 0 }};
    
    print_grid(example);
    return 0;
}

bool is_promising(vector<vector<int>>& board, int row, int col) {
    
    return false;
} // is_promising();

void solver(vector<vector<int>>& board, int row, int col, bool solution) {
    // if promising
    if (row == 8 && col == 8) {
        solution = true;
        return;
    } // if end of puzzle
    
    
    // Update row and column to next position
    if (col == 8) {
        row++;
        col = 0;
    } // if
    else
        col++;
    
    if (board[row][col] != 0)
        solver(board, row, col, solution);
    else {
        for (int val = 1; val < 10; ++val) {
            board[row][col] = val;
            solver(board, row, col, solution);
            
            if (solution)
                return;
        } // for i
    } // else
} // solver()



void print_grid(vector<vector<int>>& board) {
    for (size_t row = 0; row < 9; ++row) {
        for (size_t col = 0; col < 9; ++col) {
            if (col != 8)
                cout << board[row][col] << " ";
            else
                cout << board[row][col];
        } // for col
        cout << endl;
    } // for row
} // print_grid()
