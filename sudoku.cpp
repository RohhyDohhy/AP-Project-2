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
#include <algorithm>

constexpr int SIZE = 9;
constexpr int BOX_SIZE = 3;

using Board = std::array<std::array<int, SIZE>, SIZE>;

enum class SolveResult
{
    SOLVABLE,
    UNSOLVABLE
};

struct Position
{
    int row;
    int col;
};


void readInput(Board& board)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            std::cin >> board[i][j];
}

Position nextPos(Position cur)
{
    auto [row, col] = cur;

    if (col + 1 == SIZE)
        return Position{ row + 1, 0 };

    return Position{ row, col + 1 };
}

bool isRowValid(const Board& board, int row)
{
    bool seen[SIZE + 1] = {};

    for (int j = 0; j < SIZE; j++)
    {
        int val = board[row][j];

        if (val && seen[val])
            return false;

        seen[val] = true;
    }

    return true;
}

bool isColValid(const Board& board, int col)
{
    bool seen[SIZE + 1] = {};

    for (int i = 0; i < SIZE; i++)
    {
        int val = board[i][col];

        if (val && seen[val])
            return false;

        seen[val] = true;
    }

    return true;
}

bool isBoxValid(const Board& board, int box_row, int box_col)
{
    // calculate the top left cordinate of the corresponding box
    int x = box_row * BOX_SIZE;
    int y = box_col * BOX_SIZE;

    bool seen[SIZE + 1] = {};

    for (int i = 0; i < BOX_SIZE; i++)
    {
        for (int j = 0; j < BOX_SIZE; j++)
        {
            int val = board[x + i][y + j];

            if (val && seen[val])
                return false;

            seen[val] = true;
        }
    }

    return true;
}


bool canPlaceNumber(const Board& board, Position pos, int num)
{
    auto [row, col] = pos;
    
    for (int j = 0; j < SIZE; j++)
        if (board[row][j] == num)
            return false;
    
    for (int i = 0; i < SIZE; i++)
        if (board[i][col] == num)
            return false;
        
    int start_row = (row / BOX_SIZE) * BOX_SIZE;
    int start_col = (col / BOX_SIZE) * BOX_SIZE;


    for (int i = 0; i < BOX_SIZE; i++)
        for (int j = 0; j < BOX_SIZE; j++)
            if (board[start_row + i][start_col + j] == num)
                return false;

    return true;
}

bool solveImpl(Board& board, Position pos)
{
    auto [row, col] = pos;

    if (row == SIZE) // Reached the end of the board
        return true;

    if (board[row][col] != 0)
        return solveImpl(board, nextPos(pos));


    for (int num = 1; num <= SIZE; num++)
    {
        if (canPlaceNumber(board, pos, num))
        {
            board[row][col] = num;
            
            if (solveImpl(board, nextPos(pos)))
                return true;

            board[row][col] = 0;
        }
    }

    return false;
}

SolveResult solve(Board& board) // Wrapper function
{
    for (int row = 0; row < SIZE; row++)
        if (!isRowValid(board, row))
            return SolveResult::UNSOLVABLE;

    for (int col = 0; col < SIZE; col++)
        if (!isColValid(board, col))
            return SolveResult::UNSOLVABLE;

    for (int box_row = 0; box_row < BOX_SIZE; box_row++)
        for (int box_col = 0; box_col < BOX_SIZE; box_col++)
            if (!isBoxValid(board, box_row, box_col))
                return SolveResult::UNSOLVABLE;
    
    return solveImpl(board, Position{ 0, 0 }) ? SolveResult::SOLVABLE : SolveResult::UNSOLVABLE;
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