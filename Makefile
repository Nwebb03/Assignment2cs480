CXX = g++
CXXFLAGS = -Wall -g   # enable warnings and debug info
TARGET = xsh

SRC = xsh.cpp parser.cpp exec.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lreadline

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
