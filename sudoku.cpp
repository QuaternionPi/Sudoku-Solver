/*
Sudoku Solver
Written by David Wiebe
*/

#include <stdexcept>
#include <string.h>
#include <string>
#include "sudoku.h"

Sudoku::Sudoku(int _size, const int *input)
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
        cells[i] = Cell(val);
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
    int index = x + y * GroupSize();
    return cells[index].GetValue();
}
int Sudoku::SetCellValue(int x, int y, int val)
{
    return -2;
}
int Sudoku::NumberOfCells() const
{
    return size * size * size * size;
}
int Sudoku::GroupSize() const
{
    return size * size;
}
Sudoku *Sudoku::Solution() const
{
    int values[81];
    return new Sudoku(3, values);
}
std::string Sudoku::ToString() const
{
    std::string output;
    for (int row = 0; row < GroupSize(); row++)
    {
        if (row != 0 && (row / size) * size == row)
        {
            for (int col = 0; col < GroupSize(); col++)
            {
                if (col != 0 && (col / size) * size == col)
                {
                    output.append("| ");
                }
                output.append("- ");
            }
            output.append("\n");
        }
        for (int col = 0; col < GroupSize(); col++)
        {
            if (col != 0 && (col / size) * size == col)
            {
                output.append("| ");
            }
            output.append(std::to_string(GetCellValue(col, row)));
            output.append(" ");
        }
        output.append("\n");
    }
    return output;
}

long Sudoku::Hash() const
{
    long hash_value = 0;
    for (Cell *cell = cells; cell < cells + NumberOfCells(); cell++)
    {
        hash_value *= 3;
        hash_value += cell->GetValue();
    }
    return hash_value;
}

Sudoku::Cell::Cell()
{
    isGiven = false;
    value = 0;
}
Sudoku::Cell::Cell(int val)
{
    isGiven = (val != UNKNOWN_VALUE);
    value = val;
}
bool Sudoku::Cell::IsGiven() const
{
    return isGiven;
}
int Sudoku::Cell::GetValue() const
{
    return value;
}
void Sudoku::Cell::SetValue(int val)
{
    value = val;
}

bool test(Sudoku *input, Sudoku *compair)
{
    Sudoku *solution = input->Solution();
    long solutionHash = solution->Hash();
    long compairHash = compair->Hash();

    delete solution;
    return solutionHash == compairHash;
}