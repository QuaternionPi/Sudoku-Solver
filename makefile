CC=cc
CXX=g++
LDLIBS= -lm

%.o : %.cpp
	$(CXX) -c $(CCFLAGS) $<

sudoku: sudoku.o CLI.o
	$(CXX) -o sudoku CLI.o sudoku.o $(LDLIBS)
	rm -f *.o sudoku

clean:
	rm -f *.o sudoku