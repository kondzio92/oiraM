#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath>
#include <cerrno>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "headers.hpp"
#include "object.hpp"
#include "misc.hpp"
#include "threadwindow.hpp"
#ifdef __linux__
#include <X11/Xlib.h>
#endif

int main (int argc, char **argv) {
#ifdef __linux__
    XInitThreads();
#endif
    char move=0;
    sf::Vector2f finish;
    sf::Music theme, win, gameover;
    Shared shared;
    Object player(ObjectType::Player), castle(ObjectType::Castle);

    shared.win = shared.game_over = false;
    shared.objects.push_back(&player);
    if(!loadMap(player, castle, shared))
        return 1;
    shared.bg_objects.push_back(&castle);
    shared.game_state = 1; // start screen - main menu or game

    if(!theme.openFromFile(M_THEME_PATH)) {
        std::cerr<<"ERROR: Cannot load '"<<M_THEME_PATH<<"' image"<<std::endl;
        return 1;
    }
    theme.setLoop(true);
    if(!win.openFromFile(M_WIN_PATH)) {
        std::cerr<<"ERROR: Cannot load '"<<M_WIN_PATH<<"' image"<<std::endl;
        return 1;
    }
    if(!gameover.openFromFile(M_DEAD_PATH)) {
        std::cerr<<"ERROR: Cannot load '"<<M_DEAD_PATH<<"' image"<<std::endl;
        return 1;
    }

    ThreadWindow window(WIDTH, HEIGHT, "oiraM", &shared);

    while(!window.isOpen());
    theme.play();
    player.startFalling();
    while(window.isOpen()){
        if(!shared.win && shared.game_state == 1) { //game
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

            if(player.execute()) {
                if(!shared.game_over) {
                    theme.stop();
                    gameover.play();
                }
                shared.game_over = true;
            }


            for(Object *enemy: shared.enemies)
                if(!enemy->killed) {
                    enemy->execute();
                    enemy->update();
                    for(Object *object : shared.objects) {
                        if(enemy->colision(*object) & 7){ //any vertical collision (right or left), or bottom
                            if(object->type == ObjectType::Player) {
                                if(!shared.game_over) {
                                    theme.stop();
                                    gameover.play();
                                }
                                shared.game_over = true;
                            }
                            enemy->reverseDirection();
                        }
                        if(object->type == ObjectType::Player && enemy->colision(*object) & 8)
                            enemy->killed = true;
                    }
                }

            if(!shared.game_over && player.getPosition().x < window.getViewCenter().x - window.view.getSize().x/4 &&
            	fabs(player.getPosition().x - castle.getPosition().x) > 100.0f){
            	window.setViewCenter(player.getPosition().x + window.view.getSize().x/4 ,300);
            	player.right_limit = window.getViewCenter().x + window.view.getSize().x/2 - 20;
            	player.left_limit = window.getViewCenter().x - window.view.getSize().x/2 + 20;
            }

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

            if(!shared.game_over && fabs(player.getPosition().x - castle.getPosition().x) < 3.0f && fabs(player.getPosition().y - castle.getPosition().y) < 3.0f) {
                if(!shared.win) {
                    theme.stop();
                    win.play();
                }
                shared.win = true;
            }

        }else if(shared.game_state == 2) { // main menu screen
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i clickPosition = sf::Mouse::getPosition(*window.getWindow());
                if(clickPosition.x > 10 && clickPosition.x < 100 && // start button
                        clickPosition.y > 10 && clickPosition.y < 100){
                    shared.game_state = 1;
                }
            }
        }
    }

    return 0;
}

