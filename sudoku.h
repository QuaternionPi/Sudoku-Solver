/*
Sudoku Solver
Written by David Wiebe
*/

#pragma once
#include <string>

#define UNKNOWN_VALUE 0

class Sudoku
{
public:
    enum Group
    {
        ROW,
        COLUMN,
        BOX
    };
    Sudoku(int _size, int *input);
    ~Sudoku();
    bool IsSolved() const;
    bool IsSolved(Group group, int number) const;
    bool IsCellOkay(int x, int y) const;
    bool IsCellGiven(int x, int y) const;
    int GetCellValue(int x, int y) const;
    int SetCellValue(int x, int y, int val);
    int NumberOfCells() const;
    int GroupSize() const;
    Sudoku *Solution() const;
    std::string ToString() const;
    long Hash() const;

private:
    class Cell
    {
    public:
        Cell();
        Cell(int val);
        bool IsGiven() const;
        int GetValue() const;
        void SetValue(int val);

    private:
        bool isGiven;
        int value;
    };
    Cell *cells;
    int size;
};

bool test(Sudoku *sudoku);