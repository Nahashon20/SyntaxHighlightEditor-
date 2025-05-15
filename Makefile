CC = g++
CFLAGS = -std=c++17 -Wall -g

# The source files
SRC = main.cpp text_buffer.cpp file_io.cpp syntax_highlighter.cpp undo_redo.cpp

# The object files
OBJ = $(SRC:.cpp=.o)

# The final executable
EXE = main.exe

# Targets
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXE)

debug: CFLAGS += -DDEBUG
debug: all