//
// Created by tessa on 4/21/2020.
//

#ifndef FINALPROJECT_NPC_H
#define FINALPROJECT_NPC_H

#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>

namespace myLibrary {
  class NPC {
  public:
    void draw();
  private:
    std::string name;
    std::string desc;
    std::string attack_desc;
    int health;
    int attack;
    int armor_class;
    bool is_enemy;
  };

}


#endif //FINALPROJECT_NPC_H
