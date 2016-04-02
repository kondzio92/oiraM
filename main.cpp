#include "defines.h"
#include "ThreadWindow.hpp"
#include <iostream>
#include <SFML/System.hpp>

#define WIDTH           800
#define HEIGHT          600

int main (int argc, char **argv) {
	Shared shared;
	shared.move = 0;
	ThreadWindow window(WIDTH, HEIGHT, "oiraM");
	window.setShared(&shared);


	sf::Clock clock;
	clock.restart();

	while(window.isOpen()){
		if(shared.move != 0 && clock.getElapsedTime()>sf::milliseconds(100)){
			clock.restart();
			//std::cout<<"while..."<<std::endl;
			if(shared.move & 1){
				//move left
				std::cout<<"move left"<<std::endl;
			}else if(shared.move & 2){
				//move right
				std::cout<<"move right"<<std::endl;
			}
			if(shared.move & 4){
				//jump
				std::cout<<"jump"<<std::endl;
			}
		}

	}

    return 0;
}

