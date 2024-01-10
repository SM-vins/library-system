# Define the compiler
CXX = g++

# Define compiler flags
CXXFLAGS = -Wall -g

# Define the final executable name
TARGET = librarian_program

# Define object files
OBJ = main.o librarian.o member.o book.o

# Define the default rule for make
all: $(TARGET)

# Define the rule for linking the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Define the rules for compiling source files to object files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

librarian.o: librarian.cpp
	$(CXX) $(CXXFLAGS) -c librarian.cpp

member.o: member.cpp
	$(CXX) $(CXXFLAGS) -c member.cpp

book.o: book.cpp
	$(CXX) $(CXXFLAGS) -c book.cpp

# Define a clean rule to remove compiled files
clean:
	rm -f $(TARGET) $(OBJ)
