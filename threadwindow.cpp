#include "threadwindow.hpp"

ThreadWindow::ThreadWindow(int w, int h, std::string title, Shared *shared):
    thread(&ThreadWindow::main, this){
        this->width = w;
        this->height = h;
        this->title = title;
        this->shared = shared;

        this->shared->view = &this->view;
        this->view.setCenter(WIDTH/2, HEIGHT/2);
        this->view.setSize(WIDTH, HEIGHT);

        start_button = new sf::RectangleShape(sf::Vector2f(90, 90));
        start_button->setPosition(10,10);

        this->font.loadFromFile("Morbodoni.ttf");
        this->text.setFont(font);
        this->text.setCharacterSize(60);

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
        if(!cloud_tex.loadFromFile(CLOUD_PATH)) {
            fprintf(stderr, "ERROR: Cannot load '%s' image\n", CLOUD_PATH);
            exit(-1);
        }
        if(!castle_tex.loadFromFile(CASTLE_PATH)) {
            fprintf(stderr, "ERROR: Cannot load '%s' image\n", CASTLE_PATH);
            exit(-1);
        }
        if(!enemy_tex.loadFromFile(ENEMY_PATH)) {
            fprintf(stderr, "ERROR: Cannot load '%s' image\n", ENEMY_PATH);
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
    window->setView(this->view);
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

        window->clear(sf::Color(190,220,255,255));
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
                        case ObjectType::Cloud:
                            o->setTexture(cloud_tex);
                            break;
                        case ObjectType::Castle:
                            o->setTexture(castle_tex);
                            break;
                        case ObjectType::Enemy:
                            o->setTexture(enemy_tex);
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
                        case ObjectType::Cloud:
                            o->setTexture(cloud_tex);
                            break;
                        case ObjectType::Castle:
                            o->setTexture(castle_tex);
                            break;
                        case ObjectType::Enemy:
                            o->setTexture(enemy_tex);
                            break;
                    }
                }
                window->draw(o->sprite);
            }
            for(Object *o :  shared->enemies){
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
                        case ObjectType::Cloud:
                            o->setTexture(cloud_tex);
                            break;
                        case ObjectType::Castle:
                            o->setTexture(castle_tex);
                            break;
                        case ObjectType::Enemy:
                            o->setTexture(enemy_tex);
                            break;
                    }
                }
                window->draw(o->sprite);
            }
            if(shared->win) {
                this->text.setColor(sf::Color::Green);
                this->text.setString("You Win !");
                this->text.setPosition(view.getCenter().x - text.getLocalBounds().width / 2.0f , (HEIGHT - text.getLocalBounds().height) / 2.0f - 200.0f);
                window->draw(text);
            }
            if(shared->game_over) {
                this->text.setColor(sf::Color::Red);
                this->text.setString("Game Over");
                this->text.setPosition(view.getCenter().x - text.getLocalBounds().width / 2.0f , (HEIGHT - text.getLocalBounds().height) / 2.0f - 200.0f);
                window->draw(text);
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

void ThreadWindow::setViewCenter(float x, float y){
    this->view.setCenter(x, y);
    this->window->setView(this->view);
}

sf::Vector2f ThreadWindow::getViewCenter(){
    return this->view.getCenter();
}
