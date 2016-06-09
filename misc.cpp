#include <fstream>
#include "headers.hpp"
#include "misc.hpp"

bool loadMap (Object &player, Object &castle, Shared &shared) {
    bool is_player = false, is_castle = false;
    std::ifstream file(MAP_PATH);

    if(file.is_open()) {
        int x = 780, y;
        std::string str;

        while(std::getline(file, str)) {
            y = 40;
            for(char &c: str){
                switch(c) {
                    case 'X':
                        shared.objects.push_back(new Object(ObjectType::Rock));
                        shared.objects.back()->setPosition(x, y);
                        break;
                    case 'P':
                        if(is_player) {
                            fprintf(stderr, "ERROR: Player can be placed only once\n");
                            return false;
                        }
                        player.setPosition(x, y);
                        is_player = true;
                        break;
                    case 'E':
                        shared.enemies.push_back(new Object(ObjectType::Enemy));
                        shared.enemies.back()->setPosition(x, y);
                        shared.enemies.back()->startFalling();
                        shared.enemies.back()->startMoving(Direction::Right);
                        shared.enemies.back()->setAccel(200.0f);
                        shared.enemies.back()->setMaxSpeed(100.0f);
                        break;
                    case 'C':
                        shared.bg_objects.push_back(new Object(ObjectType::Cloud));
                        shared.bg_objects.back()->setPosition(x, y);
                        break;
                    case 'F':
                        if(is_castle) {
                            fprintf(stderr, "ERROR: Castle can be placed only once\n");
                            return false;
                        }
                        castle.setPosition(x, y);
                        is_castle = true;
                        break;
                    case 'G':
                        shared.objects.push_back(new Object(ObjectType::Rock));
                        shared.objects.back()->setPosition(x, y);
                        shared.objects.push_back(new Object(ObjectType::Grass));
                        shared.objects.back()->setPosition(x, y);
                        break;
                }
                y += 40;
            }
            x -= 40;
        }
    } else {
        fprintf(stderr, "ERROR: Cannot load map");
        return false;
    }
    file.close();
    return true;
}

