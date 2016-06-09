#ifndef MISC_HPP
#define MISC_HPP

#include "object.hpp"

struct Shared{
    bool win, game_over;
    std::vector<Object*> objects, bg_objects, enemys;
    unsigned char game_state;
};

bool loadMap (Object &player, Object &castle, Shared &shared);

#endif
