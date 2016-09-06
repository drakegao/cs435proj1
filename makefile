#DIR1 = /afs/umbc.edu/users/k/h/khirsc1/home/cs341proj/proj2/src/
CXX = g++
CXXFLAGS = -g -ansi -Wall #-I . -I $(DIR1)
OBJS = Main.o Export.o Polygun.o ReadFile.o Shape.o Vertex.o

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o Driver.out

Main.o: Main.cpp
	$(CXX) $(CXXFLAGS) -c Main.cpp

Export.o: Export.h Export.cpp Polygun.h
	$(CXX) $(CXXFLAGS) -c Manager.cpp

Polygun.o: Polygun.h Polygun.cpp
	$(CXX) $(CXXFLAGS) -c Polygun.cpp

ReadFile.o: ReadFile.h ReadFile.cpp
	$(CXX) $(CXXFLAGS) -c ReadFile.cpp

Shape.o: Shape.h Shape.cpp
	$(CXX) $(CXXFLAGS) -c Shape.cpp

Vertex.o: Vertex.h Vertex.cpp
	$(CXX) $(CXXFLAGS) -c Food.cpp

clean:
	rm *.o* results.txt

run:
	./Main.out $(STORE) $(ORDERS)
