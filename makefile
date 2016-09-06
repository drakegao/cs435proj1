#DIR1 = /afs/umbc.edu/users/k/h/khirsc1/home/cs341proj/proj2/src/
CXX = g++
CXXFLAGS = -g -ansi -Wall #-I . -I $(DIR1)
OBJS = Main.o ReadFile.o Vector.o View.o WorldInfo.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o Main.out

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c Main.cpp

ReadFile.o: ReadFile.h ReadFile.cpp
	$(CXX) $(CXXFLAGS) -c ReadFile.cpp

Vector.o: Vector.h Vector.cpp
	$(CXX) $(CXXFLAGS) -c Vector.cpp

View.o: View.h View.cpp
	$(CXX) $(CXXFLAGS) -c View.cpp

WorldInfo.o: WorldInfo.h WorldInfo.cpp
	$(CXX) $(CXXFLAGS) -c WorldInfo.cpp

clean:
	rm *.o* results.txt

run:
	./Main.out $(FILENAME)
