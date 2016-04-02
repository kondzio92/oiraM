CC = g++
FLAGS = $(CXXFLAGS)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main:
	$(CC) $(FLAGS) main.cpp ThreadWindow.cpp -o oiraM $(SFML_LIBS) -lX11

clean:
	rm -f oiraM

.PHONY: all clean
