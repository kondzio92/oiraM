#ifndef MISC_HPP
#define MISC_HPP

#include "object.hpp"

struct Shared{
    bool game_over;
    std::vector<Object*> objects, bg_objects, enemys;
    unsigned char game_state;
};

bool loadMap (Object &player, Shared &shared);

#endif
