/*
Sudoku Solver Command Line Interface
Written by David Wiebe
*/

#include "sudoku.h"
#include <iostream>
#include <string.h>
#include <string>

enum InputCase
{
    UNKNOWN = 0,
    HELP,
    SOLVE,
    SOLVE_FILE,
    TEST_FILE,
    TEST_SCRIPT
};

int solveHelper(int argc, char **argv);
int solveFileHelper(int argc, char **argv);
int testFileHelper(int argc, char **argv);
int testScriptHelper(int argc, char **argv);
void lower(char *str);
void printHelp();
InputCase parseFirstInput(char *input);

int main(int argc, char *argv[])
{
    if (argc <= 0)
    {
        printHelp();
        return 0;
    }

    char *arg_1 = argv[1];
    lower(arg_1);
    const InputCase input = parseFirstInput(arg_1);
    switch (input)
    {
    case (UNKNOWN):
    case (HELP):
        printHelp();
        return 0;
    case (SOLVE):
        solveHelper(argc, argv);
        return 0;
    case (SOLVE_FILE):
        solveFileHelper(argc, argv);
        return 0;
    case (TEST_FILE):
        testFileHelper(argc, argv);
        return 0;
    case (TEST_SCRIPT):
        testScriptHelper(argc, argv);
        return 0;
    }
}

int solveHelper(int argc, char **argv)
{
    std::cout
        << "Solve\n";
    return 0;
}
int solveFileHelper(int argc, char **argv)
{
    std::cout
        << "Solve File\n";
    return 0;
}
int testFileHelper(int argc, char **argv)
{
    std::cout
        << "Test File\n";
    return 0;
}
int testScriptHelper(int argc, char **argv)
{
    std::cout
        << "Test Script\n";
    return 0;
}

void lower(char *str)
{
    if (str == nullptr)
    {
        throw std::invalid_argument("str cannot be null");
    }
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
}

void printHelp()
{
    std::cout
        << "Sudoku Solver Written by David Wiebe\n"
        << "To use run one of: \n"
        << "--Solve\n"
        << "--Solve-File <Input>\n"
        << "--Test-File <Input> <Compair>\n"
        << "--Test-Script <Test Script>\n"
        << std::endl;
}

InputCase parseFirstInput(char *input)
{

    if (strcmp(input, "-h") == 0 || strcmp(input, "h") == 0 || strcmp(input, "help") == 0 || strcmp(input, "-help") == 0)
    {
        return HELP;
    }
    if (strcmp(input, "--solve") == 0)
    {
        return SOLVE;
    }
    if (strcmp(input, "--solve-file") == 0)
    {
        return SOLVE_FILE;
    }
    if (strcmp(input, "--test-file") == 0)
    {
        return TEST_FILE;
    }
    if (strcmp(input, "--test-script") == 0)
    {
        return TEST_SCRIPT;
    }
    return UNKNOWN;
}