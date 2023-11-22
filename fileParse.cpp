/*
Sudoku File Parser
Written by David Wiebe
*/

#include "sudoku.h"
#include "fileParse.h"
#include <string.h>
#include <unistd.h>
#include <fstream>

Sudoku *sudokuFromFile(const char *filePath)
{
    char *file = loadText(filePath);
    replaceChar(file, '\n', ' ');
    const char **tokens = (const char **)split(file, " ");
    int *numbers = selectNumbers(tokens);
    int size = 3;

    Sudoku *sudoku = new Sudoku(size, numbers);
    delete file;
    for (int i = 0; tokens[i] != nullptr; i++)
    {
        delete tokens[i];
    }
    delete tokens;
    delete numbers;

    return sudoku;
}
bool fileExists(const char *filePath)
{
    return (access(filePath, F_OK) != -1);
}
char **split(const char *input, const char *delimiter)
{
    int delimiterLength = strlen(delimiter);

    char **output = new char *[100000];
    int count = 0;
    const char *start = input;
    int runLength = 0;
    while (*input != 0)
    {
        if (match(input, delimiter))
        {
            if (runLength > 0)
            {
                char *token = new char[runLength + 1];
                output[count] = token;
                memccpy(token, input - runLength, 0, runLength);
                token[runLength] = 0;
                count++;
                runLength = 0;
                input += delimiterLength;
            }
            else
            {
                input += delimiterLength;
            }
        }
        else
        {
            input++;
            runLength++;
        }
    }
    char *token = new char[runLength + 1];
    output[count] = token;
    memccpy(token, input - runLength, 0, runLength);
    token[runLength] = 0;
    count++;
    output[count] = NULL;
    return output;
}
bool match(const char *source, const char *compair)
{
    while (*compair != 0)
    {
        if (*source != *compair)
        {
            return false;
        }
        source++;
        compair++;
    }
    return true;
}
void replaceChar(char *input, char find, char replace)
{
    for (; *input != 0; input++)
    {
        if (*input == find)
            *input = replace;
    }
}
char *loadText(const char *filePath)
{
    FILE *f = fopen(filePath, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = new char[fsize + 1];
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;
    return string;
}
int *selectNumbers(const char **tokens)
{
    int *numbers = new int[100000];
    int foundNumbers = 0;
    for (int i = 0; tokens[i] != nullptr; i++)
    {
        const char *string = tokens[i];
        if (isNumber(string))
        {
            numbers[foundNumbers] = atoi(string);
            foundNumbers++;
        }
    }
    return numbers;
}
bool isNumber(const char *string)
{
    int i = 0;

    if (isdigit(string[0]) == false && (string[0] != '-' || isdigit(string[1]) == false))
    {
        return false;
    }
    for (int i = 1; string[i] != 0; i++)
    {
        if (isdigit(string[i]) == false)
        {
            return false;
        }
    }
    return true;
}