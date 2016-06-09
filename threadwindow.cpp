#include "threadwindow.hpp"

ThreadWindow::ThreadWindow(int w, int h, std::string title, Shared *shared):
    thread(&ThreadWindow::main, this){
        this->width = w;
        this->height = h;
        this->title = title;
        this->shared = shared;

        start_button = new sf::RectangleShape(sf::Vector2f(90, 90));
        start_button->setPosition(10,10);

        this->font.loadFromFile("Morbodoni.ttf");
        this->text.setFont(font);
        this->text.setColor(sf::Color::Red);
        this->text.setCharacterSize(60);
        this->text.setString("Game Over");
        this->text.setPosition((WIDTH - text.getLocalBounds().width) / 2.0f , (HEIGHT - text.getLocalBounds().height) / 2.0f - 100.0f);


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
        if(!castle_tex.loadFromFile(CASTLE_PATH)) {
            fprintf(stderr, "ERROR: Cannot load '%s' image\n", CASTLE_PATH);
            exit(-1);
        }

        thread.launch();
    }

ThreadWindow::~ThreadWindow()
{
    //dtor
}

void ThreadWindow::main(){
    sf::Event event;

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
                default: break;
            }
        }

        window->clear(sf::Color(200,200,219,255));
        if(shared->game_state == 1){
            for(Object *o :  shared->bg_objects){
                if(o->create){
                    o->create = false;
                    switch(o->type){
                        case ObjectType::Player:
                            o->setTexture(player_tex);
                            break;
                        case ObjectType::Grass:
                            o->setTexture(grass_tex);
                            break;
                        case ObjectType::Rock:
                            o->setTexture(rock_tex);
                            break;
                        case ObjectType::Sky:
                            o->setTexture(sky_tex);
                            break;
                        case ObjectType::Castle:
                            o->setTexture(castle_tex);
                            break;
                    }
                }
                window->draw(o->sprite);
            } 
            for(Object *o :  shared->objects){
                if(o->create){
                    o->create = false;
                    switch(o->type){
                        case ObjectType::Player:
                            o->setTexture(player_tex);
                            break;
                        case ObjectType::Grass:
                            o->setTexture(grass_tex);
                            break;
                        case ObjectType::Rock:
                            o->setTexture(rock_tex);
                            break;
                        case ObjectType::Sky:
                            o->setTexture(sky_tex);
                            break;
                        case ObjectType::Castle:
                            o->setTexture(castle_tex);
                            break;
                    }
                }
                window->draw(o->sprite);
            }
            for(Object *o :  shared->enemys){
                if(o->create){
                    o->create = false;
                    switch(o->type){
                        case ObjectType::Player:
                            o->setTexture(player_tex);
                            break;
                        case ObjectType::Grass:
                            o->setTexture(grass_tex);
                            break;
                        case ObjectType::Rock:
                            o->setTexture(rock_tex);
                            break;
                        case ObjectType::Sky:
                            o->setTexture(sky_tex);
                            break;
                        case ObjectType::Castle:
                            o->setTexture(castle_tex);
                            break;
                    }
                }
                window->draw(o->sprite);
            }
            if(shared->game_over)
                window->draw(text);
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
