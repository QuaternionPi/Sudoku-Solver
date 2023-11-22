/*
Sudoku File Parser
Written by David Wiebe
*/

#include "sudoku.h"
#include "fileParse.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

Sudoku *sudokuFromFile(const char *filePath)
{
    const char *file = loadText(filePath);
    const char **tokens = split(file, " ");
    const int *numbers = selectNumbers(tokens);
    int size = 0;

    int inputs[size * size * size * size];

    return new Sudoku(1, NULL);
}

bool fileExists(const char *filePath)
{
    return (access(filePath, F_OK) != -1);
}

const char **split(const char *input, const char *delimiter)
{
    int delimiterLength = strlen(delimiter);

    const char **output = new const char *[10000];
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
                token[runLength + 1] = 0;
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
    output[count + 1] = NULL;
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

const char *loadText(const char *filePath)
{
    FILE *f = fopen("textfile.txt", "rb");
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
    return NULL;
}