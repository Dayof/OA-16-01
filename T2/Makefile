SOURCE_DIR=source
INCLUDE_DIR=include
OBJ_DIR=obj

CC=g++ -std=c++11
CFLAGS=-I$(INCLUDE_DIR)/

LIBS=-lm

DEPS=$(patsubst %,$(INCLUDE_DIR)/%,inc_system.hpp)

OBJ_INDEX=$(patsubst %,$(OBJ_DIR)/%,gera_index.o)
OBJ_SYSTEM=$(patsubst %,$(OBJ_DIR)/%,Unb_system.o)

SOURCE_INDEX=$(patsubst %,$(SOURCE_DIR)/%,gera_index.cpp)
SOURCE_SYSTEM=$(patsubst %,$(SOURCE_DIR)/%,Unb_system.cpp)

INDEX_TARGET=gera_index
SYSTEM_TARGET=Unb_system

all: index system
index: $(INDEX_TARGET)
system: $(SYSTEM_TARGET)

$(OBJ_INDEX): $(SOURCE_INDEX) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_SYSTEM): $(SOURCE_SYSTEM) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(INDEX_TARGET): $(OBJ_INDEX)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(SYSTEM_TARGET): $(OBJ_SYSTEM)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ_INDEX) $(OBJ_SYSTEM) $(INDEX_TARGET) $(SYSTEM_TARGET)
