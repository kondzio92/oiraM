#ifndef DEFINES_H
#define DEFINES_H
#include <SFML/Graphics.hpp>
#include <vector>

class Object{
	public:
		Object(unsigned char type){
			this->type = type;
			create = true;
		}
		bool create;
		unsigned char type;
		sf::Sprite sprite;
};

struct Shared{
	unsigned char move;
	std::vector<Object> objects;
	unsigned char game_state;
	sf::Vector2i click_pos;
};

#endif