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

bool violation(vector<vector<int>>& board, int row, int col);

void solver(vector<vector<int>>& board, int row, int col, bool& solution);

void print_grid(vector<vector<int>>& board);

void update_square(int& row, int& col);

void revert_square(int& row, int& col);

int main() {
    vector<vector<int>> example = { { 0, 3, 0, 0, 1, 0, 0, 6, 0 },
                                    { 7, 5, 0, 0, 3, 0, 0, 4, 8 },
                                    { 0, 0, 6, 9, 8, 4, 3, 0, 0 },
                                    { 0, 0, 3, 0, 0, 0, 8, 0, 0 },
                                    { 9, 1, 2, 0, 0, 0, 6, 7, 4 },
                                    { 0, 0, 4, 0, 0, 0, 5, 0, 0 },
                                    { 0, 0, 1, 6, 7, 5, 2, 0, 0 },
                                    { 6, 8, 0, 0, 9, 0, 0, 1, 5 },
                                    { 0, 9, 0, 0, 4, 0, 0, 3, 0 }};
    bool solution = false;
    solver(example, 0, 0, solution);
    if (solution)
        print_grid(example);
    else
        cout << "No Solution!\n";
    return 0;
}

bool violation(vector<vector<int>>& board, int row, int col) {
    revert_square(row, col);
    int curr_val = board[row][col];
    if (curr_val == 0)
        return false;
    
    // Check other rows to see if violation
    for (int r = 0; r < 8; ++r) {
        if (r != row) {
            if (board[r][col] == curr_val)
                return true;
        }
    } // for r
    
    // Check other columns to see if violation
    for (int c = 0; c < 8; ++c) {
        if (c != col) {
            if (board[row][c] == curr_val)
                return true;
        }
    } // for r
    
    // Check 3x3 box for violation
    int r_pos = row / 3;
    int c_pos = col / 3;
    for (int r = r_pos * 3; r < (r_pos + 1) * 3; ++r) {
        for (int c = c_pos * 3; c < (c_pos + 1) * 3; ++c) {
            if (row != r && col != c) {
                if (curr_val == board[r][c])
                    return true;
            }
            
        } // for f
    } // for r
    
    // If no violations, return false
    return false;
} // violation();

void solver(vector<vector<int>>& board, int row, int col, bool& solution) {
    // If no violations
    if (violation(board, row, col))
        return;
    
    
    // If end of puzzle
    if (row == 9 && col == 0) {
        solution = true;
        return;
    } // if end of puzzle
    
    if (board[row][col] != 0) {
        update_square(row, col);
        solver(board, row, col, solution);
    }
    else {
        for (int val = 1; val < 10; ++val) {
            board[row][col] = val;
            update_square(row, col);
            solver(board, row, col, solution);
            revert_square(row, col);
            if (solution)
                return;
        } // for i
        board[row][col] = 0;
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

void update_square(int& row, int& col) {
    if (col == 8) {
        col = 0;
        row++;
    }
    else
        col++;
} // update_square()

void revert_square(int& row, int& col) {
    if (col == 0 && row != 0) {
        col = 8;
        row--;
    }
    else if (col != 0)
        col--;
}
