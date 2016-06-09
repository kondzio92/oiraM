#ifndef THREADWINDOW_HPP
#define THREADWINDOW_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <list>
#include <string.h>
#include "headers.hpp"
#include "object.hpp"
#include "misc.hpp"

class ThreadWindow{
    public:
        ThreadWindow(int width, int height, std::string title, Shared *shared);
        virtual ~ThreadWindow();
        void wait();
        void setShared(Shared *shared);
        bool isOpen();
        sf::RenderWindow* getWindow();
        void setViewCenter(float x, float y);
        sf::Vector2f getViewCenter();
        sf::View view;

    protected:
        virtual void main();
        bool open = false;
        int width, height;
        std::string title;
        sf::Font font;
        sf::Text text;
        sf::Thread thread;
        sf::RenderWindow *window;
        sf::Texture player_tex, grass_tex, rock_tex, cloud_tex, castle_tex, enemy_tex;
        sf::RectangleShape *start_button;
        Shared *shared;
};

#endif
