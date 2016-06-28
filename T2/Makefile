SOURCE_DIR=source
INCLUDE_DIR=include
OBJ_DIR=obj

CC=g++
CFLAGS=-I$(INCLUDE_DIR)/

LIBS=-lm

_DEPS=inc_system.hpp
DEPS=$(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ=gera_index.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

_SOURCE=gera_index.cpp
SOURCE=$(patsubst %,$(SOURCE_DIR)/%,$(_SOURCE))

TARGET=gera_index

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET)
