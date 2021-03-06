#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "headers.hpp"

class Object {
    public:
        bool create;
        char move = 0;
        unsigned char type;
        float sec, speed = MIN_SPEED, jump_speed = -1.0f;
        sf::Vector2f position, start_pos, falling_start_pos;
        sf::Clock clock, jump_clock, falling_clock;
        sf::Sprite sprite;
        float left_limit=780, right_limit=0;
        float accel=ACCEL, max_speed=MAX_SPEED;

    public:
        Object (unsigned char type);
        void setPosition (int x, int y);
        sf::Vector2f getPosition();
        void startMoving (Direction dir);
        void stopMoving ();
        void startFalling ();
        void resetFalling ();
        void stopFalling ();
        void jump ();
        void disableJump ();
        void enableJump ();
        void reverseDirection();
        void setAccel(float accel);
        void setMaxSpeed(float speed);
        bool execute ();
        int colision (Object &obj);
        void setTexture (sf::Texture &tex);
        void update ();
        sf::FloatRect getSize ();
};

#endif
