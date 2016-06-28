SOURCE_DIR=source
INCLUDE_DIR=include
OBJ_DIR=obj

CC=g++
CFLAGS=-I$(INCLUDE_DIR)/

LIBS=-lm

_DEPS=Unb_system.hpp
DEPS=$(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ=Unb_system.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

_SOURCE=Unb_system.cpp
SOURCE=$(patsubst %,$(SOURCE_DIR)/%,$(_SOURCE))

TARGET=Unb_system


$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ) $(TARGET)
