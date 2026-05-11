/*
* ========== Naming Convention Guideline ==========
* Classes & Enums: PascalCase
* Functions: camelCase
* Variables: lower_snake_case
* Constants: UPPER_SNAKE_CASE
* =================================================
*/

#include <iostream>
#include <array>

const int SIZE = 9;

using Board = std::array<std::array<int, SIZE>, SIZE>;

enum class SolveResult
{
    SOLVABLE,
    UNSOLVABLE
};

void readInput(Board& board)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            std::cin >> board[i][j];
}


bool solveImpl(Board& board)
{
    // ...
}


SolveResult solve(Board& board) // Wrapper function
{
    return solveImpl(board) ? SolveResult::SOLVABLE : SolveResult::UNSOLVABLE;
}

void printBoard(const Board& board)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            std::cout << board[i][j] << ' ';

        std::cout << std::endl;
    }
}

int main()
{
    Board board;

    readInput(board);

    SolveResult result = solve(board);

    if (result == SolveResult::SOLVABLE)
        printBoard(board);
    else
        std::cout << "No solution exists" << std::endl;

    return 0;
}