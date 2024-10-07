IDIR=hpp
SDIR=cpp
ODIR=obj

VERBOSE=1
CC=g++
CFLAGS=-I $(IDIR) -std=c++17 -g
LIBS=-lX11 -lGL -lpthread -lpng -lstdc++fs 

DEPS = $(shell find $(IDIR) -name *.hpp)

SRC = $(shell find . -name *.cpp)

dummy_build_folder := $(shell mkdir -p $(ODIR))

_OBJ = $(subst $(SDIR)/,$(ODIR)/,$(SRC))
OBJ = $(patsubst %.cpp,%.o,$(_OBJ))

obj/%.o: cpp/%.cpp $(DEPS)
	$(CC) -c -std=c++20 -o $@ $< 

all:$(OBJ)
	$(CC) -o sly_make $^  $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
