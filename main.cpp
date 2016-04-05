#include "headers.h"
#include "ThreadWindow.hpp"
#include <iostream>
#include <SFML/System.hpp>

#define WIDTH           800
#define HEIGHT          600

int main (int argc, char **argv) {
	Shared shared;
	shared.move = 0;
	shared.game_state = 2; // main menu
	shared.objects.push_back(Object(1)); //create player
	ThreadWindow window(WIDTH, HEIGHT, "oiraM");
	window.setShared(&shared);


	sf::Clock clock;
	clock.restart();

	while(window.isOpen()){
		if(shared.game_state == 1){		//game
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
		}else if(shared.game_state == 2){	// main menu screen
			if(shared.click_pos.x > 10 && shared.click_pos.x < 100 && 	//start button
			   shared.click_pos.y > 10 && shared.click_pos.y < 100){
				shared.game_state = 1;
			}

		}

	}

    return 0;
}

