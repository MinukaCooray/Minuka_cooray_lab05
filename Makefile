CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET = matrix_ops

all: $(TARGET)

$(TARGET): main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o $(TARGET)