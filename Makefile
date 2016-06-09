CC = g++
FLAGS = $(CXXFLAGS) -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: object threadwindow main

object:
	$(CC) $(FLAGS) object.cpp -c $(SFML_LIBS)

threadwindow:
	$(CC) $(FLAGS) ThreadWindow.cpp -c $(SFML_LIBS) -lX11

main: object threadwindow
	$(CC) $(FLAGS) main.cpp object.o ThreadWindow.o -o oiraM $(SFML_LIBS) -lX11

clean:
	rm -f object.o ThreadWindow.o oiraM

.PHONY: all clean
