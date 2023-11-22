/*
Sudoku File Parser
Written by David Wiebe
*/

#include "sudoku.h"

Sudoku *sudokuFromFile(const char *filePath);

bool fileExists(const char *filePath);

char **split(const char *input, const char *delimiter);

bool match(const char *source, const char *compair);

void replaceChar(char *input, char find, char replace);

char *loadText(const char *filePath);

int *selectNumbers(const char **tokens);

bool isNumber(const char *string);