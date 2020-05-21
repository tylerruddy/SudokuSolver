//
//  main.cpp
//  sudoku_solver
//
//  Created by Tyler Ruddy on 5/21/20.
//  Copyright © 2020 Tyler Ruddy. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

bool violation(int (&board)[9][9], int row, int col);

void solver(int (&board)[9][9], int row, int col, bool& solution);

void print_board(int (&board)[9][9]);

int main() {
    cout << setprecision(5) << fixed;
    int easy[9][9] = { { 0, 3, 0, 0, 1, 0, 0, 6, 0 },
                         { 7, 5, 0, 0, 3, 0, 0, 4, 8 },
                         { 0, 0, 6, 9, 8, 4, 3, 0, 0 },
                         { 0, 0, 3, 0, 0, 0, 8, 0, 0 },
                         { 9, 1, 2, 0, 0, 0, 6, 7, 4 },
                         { 0, 0, 4, 0, 0, 0, 5, 0, 0 },
                         { 0, 0, 1, 6, 7, 5, 2, 0, 0 },
                         { 6, 8, 0, 0, 9, 0, 0, 1, 5 },
                         { 0, 9, 0, 0, 4, 0, 0, 3, 0 }};

    // MAYBE TRY TO CODE DIAGONAL AND KNIGHT CHESS
    /*int hard[9][9] = {{ 8, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 3, 6, 0, 0, 0, 0, 0 },
                      { 0, 7, 0, 0, 9, 0, 2, 0, 0 },
                      { 0, 5, 0, 0, 0, 7, 0, 0, 0 },
                      { 0, 0, 0, 0, 4, 5, 7, 0, 0 },
                      { 0, 0, 0, 1, 0, 0, 0, 3, 0 },
                      { 0, 0, 1, 0, 0, 0, 0, 6, 8 },
                      { 0, 0, 8, 5, 0, 0, 0, 1, 0 },
                      { 0, 9, 0, 0, 0, 0, 4, 0, 0 }};*/
    
    bool solution = false;
    auto start = chrono::high_resolution_clock::now();
    solver(easy, 0, 0, solution);
    if (solution)
        print_board(easy);
    else
        cout << "No Solution!\n";
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Elapsed time: " << elapsed.count() << " seconds!" << endl;
    return 0;
}

bool violation(int (&board)[9][9], int row, int col) {
    // Adjust row and column so you are checking the position that was updated
    int curr_val = board[row][col];
    if (curr_val == 0)
        return false;
    
    // Check other rows and columns to see if violation
    for (int i = 0; i < 8; ++i) {
        if (i != row) {
            if (board[i][col] == curr_val)
                return true;
        }
        if (i != col) {
            if (board[row][i] == curr_val)
                return true;
        }
    } // for i
    
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

// Recursively solves the puzzle
void solver(int (&board)[9][9], int row, int col, bool& solution) {
    // If not a viable solution stop trying this path
    if (violation(board, row, col - 1))
        return;
    
    // Adjust column and rows
    if (col == 9) {
        col = 0;
        row++;
    }
    
    // If end of puzzle
    if (row == 9 && col == 0) {
        solution = true;
        return;
    } // if end of puzzle
    
    
    // Recursively try values for open squares
    if (board[row][col] != 0) {
        solver(board, row, col + 1, solution);
    }
    else {
        for (int val = 1; val < 10; ++val) {
            board[row][col] = val;
            solver(board, row, col + 1, solution);
            if (solution)
                return;
        } // for i
        board[row][col] = 0;
    } // else
} // solver()

// Prints solution
void print_board(int (&board)[9][9]) {
    for (size_t row = 0; row < 9; ++row) {
        if (row % 3 == 0 && row != 0)
        cout << "---------------------" << endl;
        for (size_t col = 0; col < 9; ++col) {
            if (col % 3 == 0 && col != 0)
                cout << "| ";
            if (col != 8)
                cout << board[row][col] << " ";
            else
                cout << board[row][col];
        } // for col
        cout << endl;
        
    } // for row
} // print_grid()

