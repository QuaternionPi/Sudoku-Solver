/*
Sudoku File Parser
Written by David Wiebe
*/

#include "sudoku.h"

Sudoku *sudokuFromFile(const char *filePath);

bool fileExists(const char *filePath);

const char **split(const char *input, const char *delimiter);

bool match(const char *source, const char *compair);

const char *loadText(const char *filePath);

int *selectNumbers(const char **tokens);