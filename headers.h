#ifndef DEFINES_H
#define DEFINES_H
#include <SFML/Graphics.hpp>
#include <vector>

#define WIDTH           800
#define HEIGHT          600
#define ROCK_HEIGHT     4
#define PLAYER_POSITION_X 600.0f
#define PLAYER_POSITION_Y (HEIGHT-(ROCK_HEIGHT+1)*SIZE)
#define MIN_SPEED       100.0f
#define MAX_SPEED       400.0f
#define ACCEL           200.0f
#define G_ACCEL         1000.0f /* gravity acceleration */
#define CUT_SPEED       200.0f /* how much to slow down on direction change */
#define MIN_JUMP_SPEED  250.0f

#define IMAGES_PREFIX   "images/"
#define SIZE            40
#define to_str(foo)     #foo
#define var_to_str(foo) to_str(foo)
#define SIZE_STR        var_to_str(SIZE)
#define PLAYER_PATH     IMAGES_PREFIX "player-" SIZE_STR ".png"
#define GRASS_PATH      IMAGES_PREFIX "grass-" SIZE_STR ".bmp"
#define ROCK_PATH       IMAGES_PREFIX "rock-" SIZE_STR ".png"
#define SKY_PATH        IMAGES_PREFIX "sky-" SIZE_STR ".bmp"

#define NONE            0
#define LEFT            1
#define RIGHT           2

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#include <iostream> //for debug

static bool float_is_equal (float a, float b) {
    return std::abs(a - b) <= 0.00001f;
} /* float_is_different */

enum ObjectType{player, grass, rock, sky};
enum Direction{Left, Right};
class Object{
	public:
		Object(unsigned char type){
			sprite.setOrigin(20,0);
			this->type = type;
			create = true;
			clock.restart();
		}

		void startMoving(Direction dir){
			clock.restart();
			start_pos.x = sprite.getPosition().x;
			
			if (dir == Direction::Left){
				move |= 1;
				move &= ~2;
				sprite.setScale(1,1);
            }else if(dir == Direction::Right){
            	move |= 2;
				move &= ~1;
				sprite.setScale(-1,1);
            }
		}

		void stopMoving(){
			move &= ~3;
		}

		void jump(){
			if((move & 4) == 0){
				jump_speed = MAX(speed, MIN_JUMP_SPEED) * 2.0f;
				if((move & 3) !=0)
					jump_speed = MAX(speed + MIN(ACCEL * clock.getElapsedTime().asSeconds(), MAX_SPEED - speed), MIN_JUMP_SPEED) * 2.0f;
	            start_pos.y = sprite.getPosition().y;
	            jump_clock.restart();
	            move |= 4;
			}
		}

		void execute(){
			last_pos = sprite.getPosition();
			if((move & 1) != 0){
				sec = clock.getElapsedTime().asSeconds();
				way_diff = -(speed + ACCEL * MIN(sec, MAX_SPEED/ACCEL)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where ACCEL = a/2 v */	
			}else if((move & 2) != 0){
				sec = clock.getElapsedTime().asSeconds();
				way_diff = (speed + ACCEL * MIN(sec, MAX_SPEED/ACCEL)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where ACCEL = a/2 v */
			}

			if((move & 3) != 0){
				sprite.setPosition(start_pos.x + way_diff, sprite.getPosition().y);
                if(sprite.getPosition().x < 0.0f)
                    sprite.setPosition(0.0f, sprite.getPosition().y);
                if(sprite.getPosition().x > 800)
                    sprite.setPosition(800, sprite.getPosition().y);
            }

            if((move & 4) != 0){
            	sec = jump_clock.getElapsedTime().asSeconds();
				way_diff = jump_speed * sec - G_ACCEL * sec * sec;
				sprite.setPosition(sprite.getPosition().x, start_pos.y - way_diff); /* Y axis is inverted in the computer */

				if(sprite.getPosition().y > PLAYER_POSITION_Y) {
                	sprite.setPosition(sprite.getPosition().x, PLAYER_POSITION_Y);
                	move &= ~4;
           		}
			}

		}

		bool colision(Object *o){
			if(abs(o->sprite.getPosition().x-sprite.getPosition().x)<SIZE &&
				abs(o->sprite.getPosition().y-sprite.getPosition().y)<SIZE)
				return true;
			return false;

		}

		void backToLastCorrectPosition(){
			move &= ~3;
			sprite.setPosition(last_pos);
		}

		float sec, way_diff, speed = MIN_SPEED, jump_speed = -1.0f;
		sf::Vector2f start_pos, last_pos;
		sf::Clock clock, jump_clock;
		char move = 0;
		bool create;
		unsigned char type;
		sf::Sprite sprite;
};

struct Shared{
	std::vector<Object*> objects;
	unsigned char game_state;
	sf::Vector2i click_pos;
	bool jumping = false;
    int direction = 0;
    unsigned char move = 0;
    sf::Event event;
};

#endif