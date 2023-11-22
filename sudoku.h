/*
Sudoku Header
Written by David Wiebe
*/

#pragma once
#include <string>

#define UNKNOWN_VALUE -1

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

private:
    class Cell
    {
    public:
        Cell()
        {
            isGiven = false;
            value = 0;
        }
        Cell(int val)
        {
            isGiven = (val != UNKNOWN_VALUE);
            value = val;
        }
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