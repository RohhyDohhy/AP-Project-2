/*
* ========== Naming Convention Guideline ==========
* Classes, Structs & Enums: PascalCase
* Functions: camelCase
* Variables: lower_snake_case
* Constants: UPPER_SNAKE_CASE
* =================================================
*/

#include <iostream>
#include <array>

const int SIZE = 8;
const int EMPTY = -1;

using Board = std::array<std::array<char, SIZE>, SIZE>;
using Queens = std::array<int, SIZE>;


bool canPlaceQueen(const Queens& queens, int row, int col)
{
    // Check row
    if (queens[row] != EMPTY)
        return false;

    // Check column
    for (int i = 0; i < SIZE; i++)
        if (queens[i] == col)
            return false;
    
    // Check all 4 diagonals directions
    for (int i: {-1, 1}) // Row directions
    {
        for (int j: {-1, 1}) // Column directions
        {
            int x = row + i, y = col + j;
            while (x >= 0 && x < SIZE && y >= 0 && y < SIZE) // Check if (x, y) is inside the board
            {                
                if (queens[x] == y)
                    return false;

                x += i;
                y += j;
            }
        }
    }
    
    return true;
}

int solve(const Board& board, Queens& queens, int row)
{
    if (row == SIZE) // Board is filled correctly so we return 1
        return 1;

    int result = 0;

    for (int col = 0; col < SIZE; col++)
    {
        if (board[row][col] == '*' || !canPlaceQueen(queens, row, col))
            continue;

        queens[row] = col;

        result += solve(board, queens, row + 1);

        queens[row] = EMPTY;
    }

    return result;
}

void readBoard(Board& board)
{
    for (std::array<char, SIZE>& row: board)
        for (char& c: row)
            std::cin >> c;
}

int main()
{
    Board board;
    Queens queens;

    queens.fill(EMPTY);

    readBoard(board);

    std::cout << solve(board, queens, 0) << '\n';

    return 0;
}