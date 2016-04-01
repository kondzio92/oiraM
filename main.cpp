#include <cstdio> 
#include <cstdlib> 
#include <cstring> 
#include <cmath>
#include <cerrno>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

/* TODO:
 - use absolute paths to load stuff
*/

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
#define PLAYER_PATH     IMAGES_PREFIX "player-" SIZE_STR ".bmp"
#define GRASS_PATH      IMAGES_PREFIX "grass-" SIZE_STR ".bmp"
#define ROCK_PATH       IMAGES_PREFIX "rock-" SIZE_STR ".bmp"
#define SKY_PATH        IMAGES_PREFIX "sky-" SIZE_STR ".bmp"

#define NONE            0
#define LEFT            1
#define RIGHT           2

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

static bool float_is_equal (float a, float b) {
    return std::abs(a - b) <= 0.00001f;
} /* float_is_different */

int main (int argc, char **argv) {
    bool jumping = false;
    int direction = 0;
    float sec, speed = MIN_SPEED, jump_speed = -1.0f, way_diff;
    sf::Vector2f player;
    sf::Clock clock, jump_clock;
    sf::Texture player_tex, grass_tex, rock_tex, sky_tex;
    sf::Sprite player_spr, grass_spr, rock_spr, sky_spr;
    sf::RenderWindow window;
    sf::Event event;

    memset(&player, 0, sizeof(player));
    if(!player_tex.loadFromFile(PLAYER_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", PLAYER_PATH);
        return -1;
    }
    player_spr.setTexture(player_tex);
    if(!grass_tex.loadFromFile(GRASS_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", GRASS_PATH);
        return -1;
    }
    grass_spr.setTexture(grass_tex);
    if(!rock_tex.loadFromFile(ROCK_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", ROCK_PATH);
        return -1;
    }
    rock_spr.setTexture(rock_tex);
    if(!sky_tex.loadFromFile(SKY_PATH)) {
        fprintf(stderr, "ERROR: Cannot load '%s' image\n", SKY_PATH);
        return -1;
    }
    sky_spr.setTexture(sky_tex);
    window.create(sf::VideoMode(WIDTH, HEIGHT, 32), "oiraM", sf::Style::Titlebar | sf::Style::Close);
    window.setKeyRepeatEnabled(false);
    for(int x=0; x<WIDTH; x+=SIZE)
        for(int y=0; y<HEIGHT; y+=SIZE) {
            sky_spr.setPosition(x, y);
            window.draw(sky_spr);
        }
    for(int x=0; x<WIDTH; x+=SIZE)
        for(int y=HEIGHT-ROCK_HEIGHT*SIZE; y<HEIGHT; y+=SIZE) {
            rock_spr.setPosition(x, y);
            window.draw(rock_spr);
        }
    for(int x=0; x<WIDTH; x+=SIZE) {
        grass_spr.setPosition(x, HEIGHT-ROCK_HEIGHT*SIZE);
        window.draw(grass_spr);
    }
    player_spr.setPosition(PLAYER_POSITION_X, HEIGHT-(ROCK_HEIGHT+1)*SIZE);
    window.draw(player_spr);
    window.display();
    while(window.isOpen()) {
        if(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            if(direction != RIGHT) {
                                direction = LEFT;
                                player.x = player_spr.getPosition().x;
                                clock.restart();
                            }
                            break;
                        case sf::Keyboard::Right:
                            if(direction != LEFT) {
                                direction = RIGHT;
                                player.x = player_spr.getPosition().x;
                                clock.restart();
                            }
                            break;
                        case sf::Keyboard::Space:
                            if(float_is_equal(player_spr.getPosition().y, PLAYER_POSITION_Y)) {
                                jumping = true;
                                jump_speed = MAX(speed + MIN(ACCEL * clock.getElapsedTime().asSeconds(), MAX_SPEED - speed), MIN_JUMP_SPEED) * 2.0f;
                                player.y = player_spr.getPosition().y;
                                jump_clock.restart();
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                case sf::Event::KeyReleased:
                    switch(event.key.code) {
                        case sf::Keyboard::Left:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                                direction = RIGHT;
                                player.x = player_spr.getPosition().x;
                                speed = MAX(speed + ACCEL * MIN(clock.getElapsedTime().asSeconds(), MAX_SPEED/ACCEL) - CUT_SPEED, MIN_SPEED);
                            } else {
                                direction = NONE;
                            }
                            clock.restart();
                            break;
                        case sf::Keyboard::Right:
                            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                                direction = LEFT;
                                player.x = player_spr.getPosition().x;
                                speed = MAX(speed + ACCEL * MIN(clock.getElapsedTime().asSeconds(), MAX_SPEED/ACCEL) - CUT_SPEED, MIN_SPEED);
                            } else {
                                direction = NONE;
                            }
                            clock.restart();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        if(direction != NONE) {
            sec = clock.getElapsedTime().asSeconds();
            sky_spr.setPosition(player_spr.getPosition());
            window.draw(sky_spr);
            way_diff = (speed + ACCEL * MIN(sec, MAX_SPEED/ACCEL)) * sec; /* s = vt + (at^2)/2  ->  s = (t + at/2) * t,  where ACCEL = a/2 v */
            if(direction == RIGHT) {
                player_spr.setPosition(player.x + way_diff, player_spr.getPosition().y);
                if(player_spr.getPosition().x + SIZE > WIDTH)
                    player_spr.setPosition(WIDTH - SIZE, player_spr.getPosition().y);
            } else if(direction == LEFT) {
                player_spr.setPosition(player.x - way_diff, player_spr.getPosition().y);
                if(player_spr.getPosition().x < 0.0f)
                    player_spr.setPosition(0.0f, player_spr.getPosition().y);
            }
            window.draw(player_spr);
        } else {
            speed = MIN_SPEED;
        }

        if(jumping) {
            sec = jump_clock.getElapsedTime().asSeconds();
            sky_spr.setPosition(player_spr.getPosition());
            window.draw(sky_spr);
            way_diff = jump_speed * sec - G_ACCEL * sec * sec;
            player_spr.setPosition(player_spr.getPosition().x, player.y - way_diff); /* Y axis is inverted in the computer */
            if(player_spr.getPosition().y > PLAYER_POSITION_Y) {
                player_spr.setPosition(player_spr.getPosition().x, PLAYER_POSITION_Y);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    jump_speed = MAX(speed, MIN_JUMP_SPEED) * 2.0f;
                    player.y = player_spr.getPosition().y;
                    jump_clock.restart();
                } else {
                    jumping = false;
                }
            }
            window.draw(player_spr);
        }
        window.display();
    }
    return 0;
}

