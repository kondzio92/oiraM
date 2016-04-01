CC = g++
FLAGS = $(CXXFLAGS)
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main sqgen

sqgen:
	$(CC) $(FLAGS) sq-gen.cpp -o sq-gen sq-gen-cmdline.c $(SFML_LIBS) -lX11

main:
	$(CC) $(FLAGS) main.cpp -o oiraM $(SFML_LIBS) -lX11

clean:
	rm -f sq-gen oiraM

.PHONY: all clean
