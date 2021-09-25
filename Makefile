IDIR=hpp
SDIR=cpp
ODIR=obj

VERBOSE=1
CC=g++
CFLAGS=-I $(IDIR) -std=c++17 -g
LIBS=-lX11 -lGL -lpthread -lpng -lstdc++fs

DEPS = $(shell find $(IDIR) -name *.hpp)

SRC = $(shell find . -name *.cpp)

_OBJ = $(subst $(SDIR)/,$(ODIR)/,$(SRC))
OBJ = $(patsubst %.cpp,%.o,$(_OBJ))

obj/%.o: cpp/%.cpp $(DEPS)
	$(CC) -c -std=c++17 -o $@ $< 

sly_make:$(OBJ) 
	$(CC) -o $@ $^  $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
