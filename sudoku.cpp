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
Sudoku::Sudoku(const Sudoku *input)
{
    size = input->Size();
    cells = new Cell[NumberOfCells()];
    for (int i = 0; i < NumberOfCells(); i++)
    {
        int val = input->cells[i].GetValue();
        cells[i] = Cell(val);
    }
}
Sudoku::~Sudoku()
{
    delete cells;
}

bool Sudoku::IsSolved() const
{
    if (IsValid() == false)
        return false;
    for (int col = 0; col < GroupSize(); col++)
    {
        for (int row = 0; row < GroupSize(); row++)
        {
            if (GetCellValue(col, row) == 0)
            {
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::IsValid() const
{
    for (int i = 0; i < GroupSize(); i++)
    {
        bool valid = true;
        valid &= IsValid(ROW, i);
        valid &= IsValid(COLUMN, i);
        valid &= IsValid(BOX, i);
        if (valid == false)
            return false;
    }
    return true;
}
bool Sudoku::IsValid(Group group, int number) const
{
    int cellValues[GroupSize()];
    switch (group)
    {
    case ROW:
        for (int col = 0; col < GroupSize(); col++)
        {
            cellValues[col] = GetCellValue(col, number);
        }
    case COLUMN:
        for (int row = 0; row < GroupSize(); row++)
        {
            cellValues[row] = GetCellValue(number, row);
        }
    case BOX:
        int i = 0;
        int xOffset = (number % size) * size;
        int yOffset = (number / size) * size;
        for (int col = xOffset; col < size + xOffset; col++)
        {
            for (int row = yOffset; row < size + yOffset; row++)
            {
                cellValues[i] = GetCellValue(col, row);
                i++;
            }
        }
    }
    for (int i = 0; i < GroupSize(); i++)
    {
        int val = cellValues[i];
        if (val == 0)
            continue;
        for (int j = i + 1; j < GroupSize(); j++)
        {
            int otherVal = cellValues[j];
            if (val == otherVal)
            {
                return false;
            }
        }
    }
    return true;
}
bool Sudoku::IsValidPlacement(int x, int y, int val) const
{
    if (IsCellGiven(x, y) == true)
    {
        return false;
    }
    int rowValues[GroupSize()];
    int colValues[GroupSize()];
    int boxValues[GroupSize()];

    for (int col = 0; col < GroupSize(); col++)
    {
        colValues[col] = GetCellValue(col, y);
    }
    for (int row = 0; row < GroupSize(); row++)
    {
        rowValues[row] = GetCellValue(x, row);
    }
    int box = 0;
    int xOffset = (x / size) * size;
    int yOffset = (y / size) * size;
    for (int col = xOffset; col < size + xOffset; col++)
    {
        for (int row = yOffset; row < size + yOffset; row++)
        {
            boxValues[box] = GetCellValue(col, row);
            box++;
        }
    }
    for (int i = 0; i < GroupSize(); i++)
    {
        bool valid = true;
        valid &= val != rowValues[i];
        valid &= val != colValues[i];
        valid &= val != boxValues[i];
        if (valid == false)
        {
            return false;
        }
    }
    return true;
}
bool Sudoku::IsCellGiven(int x, int y) const
{
    int index = x + y * GroupSize();
    return cells[index].IsGiven();
}
int Sudoku::GetCellValue(int x, int y) const
{
    int index = x + y * GroupSize();
    return cells[index].GetValue();
}
void Sudoku::SetCellValue(int x, int y, int val)
{
    int index = x + y * GroupSize();
    cells[index].SetValue(val);
}
int Sudoku::NumberOfCells() const
{
    return size * size * size * size;
}
int Sudoku::GroupSize() const
{
    return size * size;
}
int Sudoku::Size() const
{
    return size;
}
Sudoku *Sudoku::Solution() const
{
    Sudoku *sudoku = new Sudoku(this);
    int index = 0;
    int x = index % sudoku->GroupSize();
    int y = index / sudoku->GroupSize();
    while (sudoku->IsCellGiven(x, y) == true)
    {
        index++;
        x = index % sudoku->GroupSize();
        y = index / sudoku->GroupSize();
    }
    while (index >= 0 && index < sudoku->NumberOfCells())
    {
        x = index % sudoku->GroupSize();
        y = index / sudoku->GroupSize();
        bool ableToItterate = false;
        for (int value = sudoku->GetCellValue(x, y) + 1; value <= sudoku->GroupSize(); value++)
        {
            if (sudoku->IsValidPlacement(x, y, value))
            {
                sudoku->SetCellValue(x, y, value);
                ableToItterate = true;
                break;
            }
        }
        if (ableToItterate)
        {
            index++;
            x = index % sudoku->GroupSize();
            y = index / sudoku->GroupSize();
            while (sudoku->IsCellGiven(x, y) == true)
            {
                index++;
                x = index % sudoku->GroupSize();
                y = index / sudoku->GroupSize();
            };
        }
        else
        {
            sudoku->SetCellValue(x, y, 0);
            index--;
            x = index % sudoku->GroupSize();
            y = index / sudoku->GroupSize();
            while (sudoku->IsCellGiven(x, y) == true)
            {
                index--;
                x = index % sudoku->GroupSize();
                y = index / sudoku->GroupSize();
            };
        }
    }
    return sudoku;
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

bool test(const Sudoku *input, const Sudoku *compair)
{
    Sudoku *solution = input->Solution();
    long solutionHash = solution->Hash();
    long compairHash = compair->Hash();

    delete solution;
    return solutionHash == compairHash;
}