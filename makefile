CC=cc
CXX=g++
LDLIBS= -lm

%.o : %.cpp
	$(CXX) -c $(CCFLAGS) $<

sudoku: generator.o fileParse.o sudoku.o CLI.o 
	$(CXX) -o CLI CLI.o sudoku.o fileParse.o generator.o $(LDLIBS)
	rm -f *.o sudoku

clean:
	rm -f *.o sudoku