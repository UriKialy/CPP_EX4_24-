# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -Wextra -I. -Wno-comment

# Define the target executable for the main program
TREE = tree

# Define the target executable for the tests
TEST = test

# Define the source files for the main program
SRCS = main.cpp Complex.cpp

# Define the source files for the tests
TEST_SRCS = test.cpp Complex.cpp

# Define the object files for the main program
OBJS = main.o complex.o

# Define the object files for the tests
TEST_OBJS = test.o complex.o

# Default target to build the main program
all: $(TREE) $(TEST)

# Rule to build the target executable for the main program
$(TREE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TREE) $(OBJS) -lsfml-graphics -lsfml-window -lsfml-system

# Rule to build the target executable for the tests
$(TEST): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(TEST_OBJS)

# Rule to build object files from source files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

complex.o: Complex.cpp
	$(CXX) $(CXXFLAGS) -c Complex.cpp -o complex.o

test.o: test.cpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

# Rule to clean up the build artifacts
clean:
	rm -f $(TREE) $(TEST) $(OBJS) $(TEST_OBJS)

# Rule to run the main program
run: $(TREE)
	./$(TREE)

.PHONY: all clean run
