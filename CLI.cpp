/*
Sudoku Solver Command Line Interface
Written by David Wiebe
*/

#include <iostream>
#include <string.h>
#include <string>
#include <time.h>
#include "sudoku.h"
#include "fileParse.h"
#include "generator.h"

enum InputCase
{
    UNKNOWN = 0,
    HELP,
    PRINT_FILE,
    GENERATE,
    SOLVE_FILE,
    TEST_FILE,
    TEST_SCRIPT
};

int printHelper(int argc, char **argv);
int generateHelper(int argc, char **argv);
int solveFileHelper(int argc, char **argv);
int testFileHelper(int argc, char **argv);
int testScriptHelper(int argc, char **argv);
void lower(char *str);
void printHelp();
InputCase parseFirstInput(char *input);

int main(int argc, char *argv[])
{
    if (argc <= 1)
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
    case (PRINT_FILE):
        printHelper(argc, argv);
        return 0;
    case (GENERATE):
        generateHelper(argc, argv);
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

int printHelper(int argc, char **argv)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Solve-File mode expects 1 argument");
    }
    const char *filePath = argv[2];
    Sudoku *sudoku = sudokuFromFile(filePath);
    std::cout << sudoku->ToString() << std::endl;

    delete sudoku;
    return 0;
}

int generateHelper(int argc, char **argv)
{
    if (argc != 3 && argc != 4)
    {
        throw std::invalid_argument("Solve-File mode expects 1 or 2 arguments");
    }
    const int size = atoi(argv[2]);
    int seed;
    if (argc == 4)
    {
        seed = atoi(argv[3]);
    }
    else
    {
        seed = time(0);
    }

    Sudoku *sudoku = generateSudoku(size, seed);
    std::cout << sudoku->ToString() << std::endl;

    delete sudoku;
    return 0;
}

int solveFileHelper(int argc, char **argv)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Solve-File mode expects 1 argument");
    }
    const char *filePath = argv[2];
    if (filePath == nullptr)
    {
        throw std::invalid_argument("Input file path cannot be null");
    }
    if (fileExists(filePath) == false)
    {
        throw std::invalid_argument("Input file does not exist");
    }

    Sudoku *sudoku = sudokuFromFile(filePath);
    Sudoku *solution = sudoku->Solution();
    std::cout << sudoku->ToString() << std::endl;
    std::cout << solution->ToString() << std::endl;

    delete sudoku;
    delete solution;
    return 0;
}
int testFileHelper(int argc, char **argv)
{
    if (argc != 4)
    {
        throw std::invalid_argument("Test-File mode expects 2 arguments");
    }
    const char *inputFilePath = argv[2];
    if (inputFilePath == nullptr)
    {
        throw std::invalid_argument("Input file path cannot be null");
    }
    if (fileExists(inputFilePath) == false)
    {
        throw std::invalid_argument("Input file does not exist");
    }

    const char *compairFilePath = argv[3];
    if (compairFilePath == nullptr)
    {
        throw std::invalid_argument("Compair file path cannot be null");
    }
    if (fileExists(compairFilePath) == false)
    {
        throw std::invalid_argument("Compair file does not exist");
    }

    Sudoku *input = sudokuFromFile(inputFilePath);
    Sudoku *compair = sudokuFromFile(compairFilePath);

    bool testResult = test(input, compair);

    delete input;
    delete compair;

    std::cout
        << "TEST "
        << (testResult
                ? "PASSED"
                : "FAILED")
        << std::endl;

    return 0;
}

int testScriptHelper(int argc, char **argv)
{
    if (argc != 3)
    {
        throw std::invalid_argument("Test-Script mode expects 1 argument");
    }

    const char *testFilePath = argv[2];
    if (testFilePath == nullptr)
    {
        throw std::invalid_argument("Input file path cannot be null");
    }
    if (fileExists(testFilePath) == false)
    {
        throw std::invalid_argument("Input file does not exist");
    }

    char *fileData = loadText(testFilePath);
    replaceChar(fileData, '\n', ' ');
    const char **filePaths = (const char **)split(fileData, " ");
    for (int i = 0; filePaths[i] != 0; i++)
    {
        const char *filePath = filePaths[i];
        if (fileExists(filePath) == false)
        {
            throw std::invalid_argument("File in test script does not exist");
        }
    }
    for (int i = 0; filePaths[i] != 0; i += 2)
    {
        const char *inputFilePath = filePaths[i];
        const char *compairFilePath = filePaths[i + 1];
        Sudoku *input = sudokuFromFile(inputFilePath);
        Sudoku *compair = sudokuFromFile(compairFilePath);

        bool testResult = test(input, compair);

        delete input;
        delete compair;

        std::cout
            << "TEST NUMBER "
            << i / 2
            << ": "
            << (testResult
                    ? "PASSED"
                    : "FAILED")
            << std::endl;
    }
    delete[] fileData;
    for (int i = 0; filePaths[i] != 0; i++)
    {
        delete[] filePaths[i];
    }
    delete[] filePaths;
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
        << "--Print-File\n"
        << "--Generate <size> <optional: seed>"
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
    if (strcmp(input, "--print-file") == 0)
    {
        return PRINT_FILE;
    }
    if (strcmp(input, "--generate") == 0)
    {
        return GENERATE;
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