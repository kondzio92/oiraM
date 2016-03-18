#include "ThreadWindow.hpp"

ThreadWindow::ThreadWindow(int w, int h, std::string title, Shared *shared):
thread(&ThreadWindow::main, this){
	this->width = w;
    this->height = h;
    this->title = title;
    this->shared = shared;

    start_button = new sf::RectangleShape(sf::Vector2f(90, 90));
    start_button->setPosition(10,10);

    if(!player_tex.loadFromFile(PLAYER_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", PLAYER_PATH);
        exit(-1);
    }
    if(!grass_tex.loadFromFile(GRASS_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", GRASS_PATH);
        exit(-1);
    }
    if(!rock_tex.loadFromFile(ROCK_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", ROCK_PATH);
        exit(-1);
    }
    if(!sky_tex.loadFromFile(SKY_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", SKY_PATH);
        exit(-1);
    }
    
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

    sf::Event event;// = shared->event;
    //sf::Clock clock;
   // sf::Time time = clock.getElapsedTime();
    window = new sf::RenderWindow(sf::VideoMode(width,height,32), title, sf::Style::Titlebar | sf::Style::Close);

    //window->setKeyRepeatEnabled(false);
    //window->setFramerateLimit(60);
    open = true;
    while(window->isOpen()){
        while(window->pollEvent(event)){
            switch(event.type) {
                case sf::Event::Closed:
                    open = false;
                    window->close();
                    break;
                    case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            shared->move |= 0b1;  ///powrot do bitowego przekazywania kierunku. to co nizej przeniesc do watku glownego
                            shared->move &= ~0b10;
                            break;
                        case sf::Keyboard::Right:
                            shared->move |= 0b100;
                            shared->move &= ~0b1000;
                            break;
                        case sf::Keyboard::Space:
                            shared->move |= 0b10000;
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            shared->move |= 0b10;
                            shared->move &= ~0b1;
                            break;
                        case sf::Keyboard::Right:
                            shared->move |= 0b1000;
                            shared->move &= ~0b100;
                            break;
                        default:
                            break;
                    }
                    break;
                }

        }

        window->clear(sf::Color(200,200,219,255));
        if(shared->game_state == 1){
            for(Object *o :  shared->objects){
                if(o->create){
                    o->create = false;
                    switch(o->type){
                        case ObjectType::player:
                            o->sprite.setTexture(player_tex);
                            break;
                        case ObjectType::grass:
                            o->sprite.setTexture(grass_tex);
                            break;
                        case ObjectType::rock:
                            o->sprite.setTexture(rock_tex);
                            break;
                        case ObjectType::sky:
                            o->sprite.setTexture(sky_tex);
                            break;
                    }
                }
                window->draw(o->sprite);
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
    return open;
}

sf::RenderWindow* ThreadWindow::getWindow(){
    return window;
}