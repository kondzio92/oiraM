#ifndef MISC_HPP
#define MISC_HPP

#include "object.hpp"

struct Shared{
    std::vector<Object*> objects, bg_objects, enemys;
    unsigned char game_state;
};

#endif
