#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath>
#include <cerrno>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "headers.hpp"
#include "object.hpp"
#include "misc.hpp"
#include "ThreadWindow.hpp"
#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main (int argc, char **argv) {
#ifdef __linux__
    XInitThreads();
#endif
    char move=0;
    Shared shared;
    Object player(ObjectType::Player);

    player.startFalling();
    shared.objects.push_back(&player);
    if(!loadMap(player, shared))
        return 1;
    shared.game_state = 1; // start screen - main menu or game

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
            }else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                move &= ~2;
            }

            if((move & 3) ==0){
                player.stopMoving();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                move |= 4;
                player.jump();
            }else{
                player.enableJump();
            }

            player.execute();

            bool on_floor = false;
            for(Object *o : shared.objects){
                if(o!=&player){
                    if((player.colision(*o) & 4) !=0)
                        on_floor = true;
                }
            }
            if(on_floor)
                player.enableJump();
            else
                player.disableJump();
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

