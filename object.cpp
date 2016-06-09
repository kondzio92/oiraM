#include <cmath>
#include "object.hpp"

Object::Object (unsigned char type) {
    this->type = type;
    this->create = true;
    this->clock.restart();
}

void Object::setPosition (int x, int y) {
    this->sprite.setPosition(x, y - this->sprite.getGlobalBounds().height / 2);
    this->position = sf::Vector2f(x, y - this->sprite.getGlobalBounds().height / 2);
    this->start_pos.x = this->position.x;
    this->clock.restart();
}

sf::Vector2f Object::getPosition () {
    return sf::Vector2f(this->position.x, this->position.y + this->sprite.getGlobalBounds().height / 2);
}

void Object::startMoving (Direction dir) {
    this->start_pos.x = this->position.x;
    this->clock.restart();

    if(dir == Direction::Left) {
        if((this->move & 2) != 0) {
            this->speed = MAX(this->speed + accel * MIN(this->clock.getElapsedTime().asSeconds(), max_speed/accel) - CUT_SPEED, MIN_SPEED);
            this->start_pos.x = this->position.x;
        }
        this->move |= 1;
        this->move &= ~2;
        this->sprite.setScale(1.0f, 1.0f);
    }else if(dir == Direction::Right){
        if((this->move & 1) != 0){
            this->speed = MAX(this->speed + accel * MIN(this->clock.getElapsedTime().asSeconds(), max_speed/accel) - CUT_SPEED, MIN_SPEED);
            this->start_pos.x = this->position.x;
        }
        this->move |= 2;
        this->move &= ~1;
        this->sprite.setScale(-1.0f, 1.0f);
    }
}

void Object::stopMoving () {
    if((this->move & 3) !=0){
        this->move &= ~3;
        this->start_pos.x = this->position.x;
    }
}

void Object::startFalling () {
    this->falling_clock.restart();
    this->start_pos.y = this->position.y;
    this->move |= 16;
}

void Object::resetFalling () {
    this->falling_clock.restart();
    this->start_pos.y = this->position.y;
}

void Object::stopFalling () {
    this->move &= ~16;
    this->start_pos.y = this->position.y;
}

void Object::jump () {
    if((this->move & 4) == 0 && (this->move & 8) == 0){	// 4 is for jumping, 8 lock for jump
        this->jump_speed = MAX(MIN_SPEED, MIN_JUMP_SPEED) * 2.0f;
        if((this->move & 3) != 0)
            this->jump_speed = MAX(this->speed + MIN(accel * this->clock.getElapsedTime().asSeconds(), max_speed - this->speed), MIN_JUMP_SPEED) * 2.0f;
        this->start_pos.y = this->position.y;
        this->jump_clock.restart();
        this->move |= 4;
        this->move |= 8;
    }
}

void Object::disableJump () {
    this->move |= 8;
}

void Object::enableJump () {
    this->move &= ~8;
}

void Object::reverseDirection(){
    if(this->move & 1)
        startMoving(Direction::Right);
    else
        startMoving(Direction::Left);
}

void Object::setAccel(float accel){
    this->accel = accel;    
}

void Object::setMaxSpeed(float speed){
    this->max_speed = speed;
}

bool Object::execute () {
    bool ret = false; // game over check
    sf::Vector2f way_diff = sf::Vector2f(0.0f, 0.0f);

    way_diff = sf::Vector2f(0,0);
    if((this->move & 1) != 0){
        sec = this->clock.getElapsedTime().asSeconds();
        way_diff.x = -(this->speed + accel * MIN(sec, max_speed/accel)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where accel = a/2 v */
    }else if((this->move & 2) != 0){
        this->sec = clock.getElapsedTime().asSeconds();
        way_diff.x = (this->speed + accel * MIN(sec, max_speed/accel)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where accel = a/2 v */
    }

    if((this->move & 4) != 0){
        sec = this->jump_clock.getElapsedTime().asSeconds();
        way_diff.y -= this->jump_speed * sec;
    }

    if((this->move & 16) != 0){
        sec = this->falling_clock.getElapsedTime().asSeconds();
        way_diff.y += G_ACCEL * sec * sec;
    }
    this->position = this->start_pos + way_diff;

    if(type==ObjectType::Player){
        if(this->position.x < left_limit)
            this->position.x = left_limit;
        if(this->position.x > right_limit)
            this->position.x = right_limit;
    }
    if(this->position.y > HEIGHT) {
        this->position.y = ((int)this->position.y) % (int)HEIGHT;
        ret = true;
    }
    return ret;
}

int Object::colision (Object &obj) {
    float w = this->sprite.getGlobalBounds().width;
    float h = this->sprite.getGlobalBounds().height;
    float w1 = obj.sprite.getGlobalBounds().width;
    float h1 = obj.sprite.getGlobalBounds().height;

    if(fabs(obj.position.x - this->position.x) <= w1 / 2.0f + w / 2.0f &&
            fabs(obj.position.y-this->position.y) <= h1 / 2.0f + h / 2.0f) {
        float m1 = MIN(this->position.x + w / 2.0f, obj.position.x + w1 / 2.0f) - MAX(this->position.x - w / 2.0f, obj.position.x - w1 / 2.0f);
        float m2 = MIN(this->position.y + h / 2.0f, obj.position.y + h1 / 2.0f) - MAX(this->position.y - h / 2.0f, obj.position.y - h1 / 2.0f);
        // m1- dlugosc krawedzi x prostokata przeciecia
        // m2- dlugosc krawedzi y prostokata przeciecia
        if(m1 < 3.0f && m2 < 3.0f)
            return 0; // no collision

        if(m1 > m2) {
            this->position.y = obj.position.y + (this->position.y > obj.position.y ? 1.0f : -1.0f) * (h1 / 2.0f + h / 2.0f);
            if(this->position.y < obj.position.y) { // collision from bottom
                this->move &= ~4;
                this->move &= ~8;
                this->resetFalling();
                return 4; // collision from bottom
            } else { // collision from top
                this->move &= ~4;
                this->resetFalling();
                return 8; // collision from top
            }
        } else { // vertical cross
            this->position.x = obj.position.x + (this->position.x > obj.position.x ? 1.0f : -1.0f) * (w1 / 2.0f + w / 2.0f + 1.0f);
            this->start_pos.x = this->position.x;
            this->clock.restart();
            return 3; // vertical collision (b01 for left, b10 for right)
        }
    }
    return 0; // no collision
}

void Object::setTexture (sf::Texture &tex) {
    this->sprite.setTexture(tex);
    this->sprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
    this->position.y -= this->sprite.getGlobalBounds().height / 2;
    this->sprite.setPosition(this->position);
}

void Object::update () {
    this->sprite.setPosition(this->position);
}

sf::FloatRect Object::getSize () {
    return this->sprite.getGlobalBounds();
}

