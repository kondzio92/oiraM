CC = g++
FLAGS = $(CXXFLAGS)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: threadwindow main

threadwindow:
	$(CC) $(FLAGS) ThreadWindow.cpp -c $(SFML_LIBS) -lX11 -std=c++11

main: threadwindow
	$(CC) $(FLAGS) main.cpp ThreadWindow.o -o oiraM $(SFML_LIBS) -lX11 -std=c++11

clean:
	rm -f ThreadWindow.o oiraM

.PHONY: all clean
