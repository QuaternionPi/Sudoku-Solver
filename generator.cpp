/*
Sudoku Generator
Written by David Wiebe
*/

#include <stdexcept>
#include <random>
#include "generator.h"
#include "sudoku.h"

Sudoku *generateSudoku(int size, int seed)
{
    srand(seed);
    const int numberOfCells = size * size * size * size;
    const int groupSize = size * size;
    int initialValues[numberOfCells];
    for (int i = 0; i < numberOfCells; i++)
    {
        initialValues[i] = 0;
    }
    for (int i = 0; i < groupSize; i++)
    {
        initialValues[i] = i + 1;
    }
    for (int i = 0; i < groupSize; i++)
    {
        initialValues[i] = i + 1;
    }
    for (int i = 0; i < groupSize; i++)
    {
        for (int j = i + 1; j < groupSize; j++)
        {
            bool swap = (rand() % 2) == 0;
            if (swap)
            {
                int temp = initialValues[i];
                initialValues[i] = initialValues[j];
                initialValues[j] = temp;
            }
        }
    }
    Sudoku *initialSudoku = new Sudoku(size, initialValues);
    Sudoku *solution = initialSudoku->Solution();
    delete initialSudoku;

    int index = 0;
    int x = 0;
    int y = 0;
    int replacedValue = 0;
    while (solution->NumberOfSolutions() == 1)
    {
        index = rand() % numberOfCells;
        x = index % groupSize;
        y = index / groupSize;
        if (solution->IsCellGiven(x, y))
        {
            continue;
        }
        replacedValue = solution->GetCellValue(x, y);
        solution->SetCellValue(x, y, UNKNOWN_VALUE);
    }
    solution->SetCellValue(x, y, replacedValue);

    return solution;
}