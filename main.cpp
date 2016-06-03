#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath>
#include <cerrno>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "headers.h"
#include "ThreadWindow.hpp"

int main (int argc, char **argv) {
	#ifdef __linux__
    XInitThreads();
    #endif
	Shared shared;
	char move=0;
	shared.game_state = 1; // main menu
	Object player(ObjectType::player);
	shared.objects.push_back(&player);
	player.setPosition(PLAYER_POSITION_X, PLAYER_POSITION_Y-100);
	player.startFalling();
	Object castle(ObjectType::castle);
	castle.setPosition(2000, PLAYER_POSITION_Y-100);
	for(int i=0 ; i<20 ; i++){
		for(int j=1 ; j<=4 ; j++){
			shared.objects.push_back(new Object(ObjectType::rock));
			shared.objects.back()->setPosition(i*40+20, 620-j*40);
		}
		shared.objects.push_back(new Object(ObjectType::grass));
		shared.objects.back()->setPosition(i*40+20, 440);
	}
	Object klocek(ObjectType::rock);
	shared.objects.push_back(new Object(ObjectType::rock));
	shared.objects.back()->setPosition(400, 400);
	shared.objects.push_back(&klocek);
	shared.objects.back()->setPosition(440, 360);

	shared.bg_objects.push_back(new Object(ObjectType::sky));
	shared.bg_objects.back()->setPosition(380, 390);
	//shared.bg_objects.push_back(&castle);

	ThreadWindow window(WIDTH, HEIGHT, "oiraM", &shared);

	while(!window.isOpen());
	while(window.isOpen()){
		if(shared.game_state == 1){		//game
			if (((move & 1) == 0) && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                move |= 1;
                player.startMoving(Left);
			}else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				move &= ~1;
			}

			if (((move & 2) == 0) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){   
                    move |= 2;
                    player.startMoving(Right);
                    klocek.startFalling();
			}else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				move &= ~2;
			}

			if((move & 3) ==0){
				player.stopMoving();
			}

			if (/*((move & 4) == 0 ) && */sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				std::cout<< int(move)<<std::endl;
				move |= 4;
				player.jump();
			}/*else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
				move &= ~4;
			}*/

			player.execute();
			klocek.execute();
			int i = 0;
			for(Object *o : shared.objects){
				if(o!=&player){
					player.colision(o);

				}
				if(o!=&klocek){
					klocek.colision(o);
				}
			}
			klocek.update();
			player.update();

		}else if(shared.game_state == 2){	// main menu screen
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				sf::Vector2i clickPosition = sf::Mouse::getPosition(*window.getWindow());
				if(clickPosition.x > 10 && clickPosition.x < 100 && 	//start button
				   clickPosition.y > 10 && clickPosition.y < 100){
					shared.game_state = 1;
				}
			}
		}
	}

    return 0;
}

