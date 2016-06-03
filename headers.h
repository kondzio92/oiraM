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
#define CASTLE_PATH     IMAGES_PREFIX "castle.png"

#define NONE            0
#define LEFT            1
#define RIGHT           2

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))


static bool float_is_equal (float a, float b) {
    return std::abs(a - b) <= 0.00001f;
} /* float_is_different */

enum ObjectType{player, grass, rock, sky, castle};
enum Direction{Left, Right};
class Object{
	public:
		Object(unsigned char type){
			sprite.setOrigin(sprite.getLocalBounds().width/2,0);
			this->type = type;
			create = true;
			clock.restart();
		}

		void setPosition(int x, int y){
			sprite.setPosition(x, y);
			position = sf::Vector2f(x, y);
			clock.restart();
			start_pos.x = position.x;
		}

		void startMoving(Direction dir){
			clock.restart();
			start_pos.x = position.x;
			
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
			if((move & 3) !=0){
				move &= ~3;
				start_pos.x = position.x;
			}
		}

		void startFalling(){
			falling_clock.restart();
			start_pos.y = position.y;
			move |= 8;
		}

		void resetFalling(){
			falling_clock.restart();
			start_pos.y = position.y;
		}

		void stopFalling(){
			move &= ~8;
			start_pos.y = position.y;
		}

		void jump(){
			if((move & 4) == 0){
				jump_speed = MAX(speed, MIN_JUMP_SPEED) * 2.0f;
				if((move & 3) !=0)
					jump_speed = MAX(speed + MIN(ACCEL * clock.getElapsedTime().asSeconds(), MAX_SPEED - speed), MIN_JUMP_SPEED) * 2.0f;
	            start_pos.y = position.y;
	            jump_clock.restart();
	            move |= 4;
			}
		}

		void execute(){
			last_pos = position;
			way_diff = sf::Vector2f(0,0);
			if((move & 1) != 0){
				sec = clock.getElapsedTime().asSeconds();
				way_diff.x = -(speed + ACCEL * MIN(sec, MAX_SPEED/ACCEL)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where ACCEL = a/2 v */	
			}else if((move & 2) != 0){
				sec = clock.getElapsedTime().asSeconds();
				way_diff.x = (speed + ACCEL * MIN(sec, MAX_SPEED/ACCEL)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where ACCEL = a/2 v */
			}

           if((move & 4) != 0){
            	sec = jump_clock.getElapsedTime().asSeconds();
				way_diff.y -= jump_speed * sec;
			}

			if((move & 8) != 0){
				sec = falling_clock.getElapsedTime().asSeconds();
				way_diff.y += G_ACCEL * sec * sec;
			}
			position = start_pos + way_diff;
			
            if(position.x < 0.0f)
                position.x = 0.0f;
            if(position.x > 800)
                position.x = 800;
		}

		bool colision(Object *o){
			float w = sprite.getGlobalBounds().width;
			float h = sprite.getGlobalBounds().height;
			float w1 = o->sprite.getGlobalBounds().width;
			float h1 = o->sprite.getGlobalBounds().height;

			if(fabs(o->position.x-position.x)<=w1/2+w/2 &&
				fabs(o->position.y-position.y)<=h1/2+h/2){
				float m1 = MIN(position.x+w/2, o->position.x+w1/2)-MAX(position.x-w/2, o->position.x-w1/2);
				float m2 = MIN(position.y+h/2, o->position.y+h1/2) -MAX(position.y-h/2, o->position.y-h1/2);
				if(m1<1 && m2<1)
					return false;
				float a, b;
				if(m1 > m2){
					position.y = o->position.y + (position.y>o->position.y?1:-1) * (h1/2 + h/2);
				}else{
					position.x = o->position.x + (position.x>o->position.x?1:-1) * (w1/2 + w/2 +1);
					start_pos.x = position.x;
					clock.restart();					
				}
				
				move &= ~4;
				resetFalling();
				return true;
			}
				
			return false;

		}

		void backToLastCorrectPosition(){
			move &= ~3;
			sprite.setPosition(last_pos);
		}

		void setTexture(sf::Texture &t){
			sprite.setTexture(t);
			sprite.setOrigin(t.getSize().x/2, t.getSize().y/2);
		}

		void update(){
			sprite.setPosition(position);
		}

		float sec, speed = MIN_SPEED, jump_speed = -1.0f;
		sf::Vector2f position, way_diff=sf::Vector2f(0,0), start_pos, last_pos, falling_start_pos;
		sf::Clock clock, jump_clock, falling_clock;
		char move = 0;
		bool create;
		unsigned char type;
		sf::Sprite sprite;
};

struct Shared{
	std::vector<Object*> objects, bg_objects, enemys;
	unsigned char game_state;
};

#endif
