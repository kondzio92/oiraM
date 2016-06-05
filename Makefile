CC = g++
FLAGS = $(CXXFLAGS)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: sqgen threadwindow main

sqgen:
	$(CC) $(FLAGS) sq-gen.cpp -o sq-gen sq-gen-cmdline.c $(SFML_LIBS) -lX11

threadwindow:
	$(CC) $(FLAGS) ThreadWindow.cpp -c $(SFML_LIBS) -lX11 -std=c++11

main: threadwindow
	$(CC) $(FLAGS) main.cpp ThreadWindow.o -o oiraM $(SFML_LIBS) -lX11 -std=c++11

clean:
	rm -f sq-gen ThreadWindow.o oiraM

.PHONY: all clean
