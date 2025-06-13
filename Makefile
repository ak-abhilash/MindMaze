CXX = g++
CXXFLAGS = -Iinclude -std=c++17 -Wall
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
EXEC = mindmaze

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC)

clean:
	del /Q src\*.o $(EXEC).exe 2>NUL

run: all
	./$(EXEC)
