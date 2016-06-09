#include <fstream>
#include "headers.hpp"
#include "misc.hpp"

bool loadMap (Object &player, Shared &shared) {
    std::ifstream file(MAP_PATH);

    if(file.is_open()) {
        int x = 780, y = 0;
        std::string str;

        while(std::getline(file, str)) {
            y = 0;
            for(char &c: str){
                switch(c) {
                    case 'X':
                        shared.objects.push_back(new Object(ObjectType::Rock));
                        shared.objects.back()->setPosition(x, y);
                        break;
                    case 'P':
                        player.setPosition(x, y);
                        break;
                    case 'C':
                        shared.bg_objects.push_back(new Object(ObjectType::Sky));
                        shared.bg_objects.back()->setPosition(x, y);
                        break;
                    case 'G':
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

