# Sudoku Solver
A command line program to solve sudoku puzzles. Sudokus are solved with the backtrace algorithm.

Written by David Wiebe.

# Build
To build run the following:
```console
make
```
This will produce the CLI file

# Run

## Solve
To solve a sudoku file:
```console
./CLI --Solve-File <Filepath>
```

## Print
To print a sudoku file:
```console
./CLI --Print-File <Filepath>
```

## Generate
To generate a sudoku of a size from a seed:
```console
./CLI --Generate <size> <optional: seed>
```

## Test
To run a single test:
```console
./CLI --Test-File <Input Filepath> <Compair Filepath>
```

To run a test script file:
```console
./CLI --Test-Script <Script Filepath>
```

## Help
For help:
```console
./CLI help
```
