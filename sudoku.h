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
    Sudoku(int _size, const int *input);
    Sudoku(const Sudoku *input);
    ~Sudoku();
    bool IsSolved() const;
    bool IsValid() const;
    bool IsValid(Group group, int number) const;
    bool IsValidPlacement(int x, int y, int val) const;
    bool IsCellGiven(int x, int y) const;
    int GetCellValue(int x, int y) const;
    void SetCellValue(int x, int y, int val);
    int NumberOfSolutions() const;
    int NumberOfCells() const;
    int GroupSize() const;
    int Size() const;
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

bool test(const Sudoku *input, const Sudoku *compair);