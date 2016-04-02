#include "ThreadWindow.hpp"

ThreadWindow::ThreadWindow(int w, int h, std::string title):
thread(&ThreadWindow::main, this){
	this->width = w;
    this->height = h;
    this->title = title;

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