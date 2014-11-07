CC      = /usr/bin/g++
CFLAGS  = -Wall -pedantic -std=c++0x
LDFLAGS = -lSDL2

SRC_FOLDER = ./src
BIN_FOLDER = ./bin

# SRC := $(wildcard *.cpp)
SRC = $(shell find $(SRC_FOLDER) -type f -name '*.cpp')
OBJ := $(patsubst $(SRC_FOLDER)/%.cpp, $(BIN_FOLDER)/%.o, $(SRC))

all: bin SpamViewer

SpamViewer: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN_FOLDER)/SpamViewer $(OBJ) $(LDFLAGS)

$(BIN_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p "$(@D)"
	$(CC) $(CFLAGS) -c $< -o $@
	
bin:
	mkdir $(BIN_FOLDER)
	
clean:
	rm -r $(BIN_FOLDER)