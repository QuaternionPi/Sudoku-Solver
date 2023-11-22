/*
Sudoku Solver
Written by David Wiebe
*/

#include <stdexcept>
#include <string>
#include "sudoku.h"

Sudoku::Sudoku(int _size, int *input)
{
    if (_size < 0)
        throw std::invalid_argument("Sudoku size Cannot be negative");
    if (_size > 10)
        throw std::invalid_argument("Sudoku size Cannot be over ten");
    size = _size;
    cells = new Cell[NumberOfCells()];
    for (int i = 0; i < NumberOfCells(); i++)
    {
        int val = input[i];
        cells[i] = Cell(i);
    }
}
Sudoku::~Sudoku()
{
    delete cells;
}

bool Sudoku::IsSolved() const
{
    return false;
}
bool Sudoku::IsSolved(Group group, int number) const
{
    return false;
}
bool Sudoku::IsCellOkay(int x, int y) const
{
    return false;
}
bool Sudoku::IsCellGiven(int x, int y) const
{
    return false;
}
int Sudoku::GetCellValue(int x, int y) const
{
    return -2;
}
int Sudoku::SetCellValue(int x, int y, int val)
{
    return -2;
}
int Sudoku::NumberOfCells() const
{
    return -2;
}
int Sudoku::GroupSize() const
{
    return -2;
}
Sudoku *Sudoku::Solution() const
{
    int values[81];
    return new Sudoku(3, values);
}
std::string Sudoku::ToString() const
{
    return "";
}

bool Sudoku::Cell::IsGiven() const
{
    return false;
}
int Sudoku::Cell::GetValue() const
{
    return -2;
}
void Sudoku::Cell::SetValue(int val)
{
}