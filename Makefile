CC = g++
FLAGS = $(CXXFLAGS) -std=c++11
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: object threadwindow main

misc:
	$(CC) $(FLAGS) misc.cpp -c $(SFML_LIBS)

object:
	$(CC) $(FLAGS) object.cpp -c $(SFML_LIBS)

threadwindow:
	$(CC) $(FLAGS) ThreadWindow.cpp -c $(SFML_LIBS) -lX11

main: misc object threadwindow
	$(CC) $(FLAGS) main.cpp misc.o object.o ThreadWindow.o -o oiraM $(SFML_LIBS) -lX11

clean:
	rm -f misc.o object.o ThreadWindow.o oiraM

.PHONY: all clean
