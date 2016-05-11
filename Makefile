SOURCE_DIR=source
INCLUDE_DIR=include
OBJ_DIR=obj

CC=g++
CFLAGS=-I$(INCLUDE_DIR)/

LIBS=-lm

_DEPS=my_drive.h
DEPS=$(patsubst %,$(INCLUDE_DIR)/%,$(_DEPS))

_OBJ=my_drive.o
OBJ=$(patsubst %,$(OBJ_DIR)/%,$(_OBJ))

_SOURCE=my_drive.cpp
SOURCE=$(patsubst %,$(SOURCE_DIR)/%,$(_SOURCE))

TARGET=my_drive


$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) 

.PHONY: clean

clean: 
	rm -f $(OBJ_DIR)/%.o *~ core $(INCLUDE_DIR)/*~