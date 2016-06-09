#ifndef HEADERS_HPP
#define HEADERS_HPP

#define WIDTH           800
#define HEIGHT          600
#define ROCK_HEIGHT     4
#define PLAYER_POSITION_X 600.0f
#define PLAYER_POSITION_Y (HEIGHT-(ROCK_HEIGHT+1)*SIZE)
#define MIN_SPEED       100.0f
#define MAX_SPEED       400.0f
#define ACCEL           600.0f
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
#define MAP_PATH        "map"

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

enum ObjectType{
    Player,
    Grass,
    Rock,
    Sky,
    Castle
};

enum Direction{
    Left,
    Right
};

#endif
