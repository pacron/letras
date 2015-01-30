CC = g++
CPPFLAGS = -Wall -g -I$(INCLUDE) 
SRC = ./src
INCLUDE = ./include
OBJ = ./obj
BIN = ./bin
DOC = ./doc
SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(OBJ)/%.o)
MAIN_OBJECTS := $(patsubst $(SRC)/mains/%.cpp, $(OBJ)/%.o, $(wildcard $(SRC)/mains/*.cpp))

all: $(BIN)/testdiccionario $(BIN)/letras

$(BIN)/letras: $(OBJECTS) $(OBJ)/letras.o
	$(CC) $(CPPFLAGS) -o $@ $^

$(BIN)/testdiccionario: $(OBJECTS) $(OBJ)/testdiccionario.o
	$(CC) $(CPPFLAGS) -o $@ $^

$(BIN)/cantidad_letras: $(OBJECTS) $(OBJ)/cantidad_letras.o
	$(CC) $(CPPFLAGS) -o $@ $^

$(OBJECTS): $(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

$(MAIN_OBJECTS): $(OBJ)/%.o: $(SRC)/mains/%.cpp
	$(CC) $(CPPFLAGS) -o $@ -c $<

doc:
	doxygen $(DOC)/doxys/Doxyfile

clean:
	rm -f $(OBJ)/*

mrproper: clean
	rm -fR $(BIN)/* $(DOC)/doxygen

.PHONY: all clean mrproper doc