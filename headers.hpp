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
#define PLAYER_PATH     IMAGES_PREFIX "player.png"
#define GRASS_PATH      IMAGES_PREFIX "grass.png"
#define ROCK_PATH       IMAGES_PREFIX "rock.png"
#define CLOUD_PATH      IMAGES_PREFIX "cloud.bmp"
#define CASTLE_PATH     IMAGES_PREFIX "castle.png"
#define MAP_PATH        "map"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

enum ObjectType{
    Player,
    Grass,
    Rock,
    Cloud,
    Castle
};

enum Direction{
    Left,
    Right
};

#endif
