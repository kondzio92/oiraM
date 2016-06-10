#ifndef HEADERS_HPP
#define HEADERS_HPP

#define WIDTH           800
#define HEIGHT          600
#define MIN_SPEED       100.0f
#define MAX_SPEED       400.0f
#define ACCEL           600.0f
#define G_ACCEL         1000.0f /* gravity acceleration */
#define CUT_SPEED       200.0f /* how much to slow down on direction change */
#define MIN_JUMP_SPEED  250.0f

#define IMAGES_PREFIX   "images/"
#define SOUNDS_PREFIX   "sounds/"
#define PLAYER_PATH     IMAGES_PREFIX "player.png"
#define GRASS_PATH      IMAGES_PREFIX "grass.png"
#define ROCK_PATH       IMAGES_PREFIX "rock.png"
#define CLOUD_PATH      IMAGES_PREFIX "cloud.png"
#define CASTLE_PATH     IMAGES_PREFIX "castle.png"
#define ENEMY_PATH     IMAGES_PREFIX "enemy.png"
#define MAP_PATH        "map"
#define M_THEME_PATH    SOUNDS_PREFIX "overworld.ogg"
#define M_WIN_PATH      SOUNDS_PREFIX "level-complete.ogg"
#define M_DEAD_PATH     SOUNDS_PREFIX "youre-dead.ogg"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

enum ObjectType{
    Player,
    Grass,
    Rock,
    Cloud,
    Castle,
    Enemy
};

enum Direction{
    Left,
    Right
};

#endif
