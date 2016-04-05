#include "ThreadWindow.hpp"

ThreadWindow::ThreadWindow(int w, int h, std::string title):
thread(&ThreadWindow::main, this){
	this->width = w;
    this->height = h;
    this->title = title;

    start_button = new sf::RectangleShape(sf::Vector2f(90, 90));
    start_button->setPosition(10,10);

    thread.launch();
}

ThreadWindow::~ThreadWindow()
{
    //dtor
}

void ThreadWindow::main(){
    #ifdef __linux__
    XInitThreads();
    #endif

    sf::Event event;
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    window = new sf::RenderWindow(sf::VideoMode(width,height,32), title, sf::Style::Titlebar | sf::Style::Close);

    window->setFramerateLimit(30);

    while(window->isOpen()){
        while(window->pollEvent(event)){
            switch(event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Left) {
                        shared->move |= 1;
                        //std::cout<<"left"<<std::endl;
                    } else if(event.key.code == sf::Keyboard::Right) {
                        shared->move |= 2;
                        //std::cout<<"right"<<std::endl;
                    } else if(event.key.code == sf::Keyboard::Up) {
                        shared->move |= 4;
                        //std::cout<<"up"<<std::endl;
                    }
                    break;
                case sf::Event::KeyReleased:
                    if(event.key.code == sf::Keyboard::Left) {
                        shared->move &= ~(char)(1);
                    } else if(event.key.code == sf::Keyboard::Right) {
                        shared->move &= ~(char)(2);
                    } else if(event.key.code == sf::Keyboard::Up) {
                        shared->move &= ~(char)(4);
                    }
                    break;
                default:
                    break;
            }

        }

        window->clear(sf::Color(200,200,219,255));
        if(shared->game_state == 1){
            for(Object o :  shared->objects){
                if(o.create){
                    o.create = false;
                    switch(o.type){
                        case 1:
                            o.sprite.setTexture(player_tex);
                            break;
                        case 2:
                            o.sprite.setTexture(grass_tex);
                            break;
                        case 3:
                            o.sprite.setTexture(rock_tex);
                            break;
                        case 4:
                            o.sprite.setTexture(sky_tex);
                            break;
                    }
                }
                window->draw(o.sprite);
            } 
        }else if(shared->game_state == 2){
            window->draw(*start_button);
        }
        

        window->display();
    }
}

void ThreadWindow::wait(){
    thread.wait();
}

void ThreadWindow::setShared(Shared *shared){
    this->shared = shared;
}

bool ThreadWindow::isOpen(){
    return window->isOpen();
}