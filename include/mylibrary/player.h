//
// Created by tessa on 4/21/2020.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>

namespace myLibrary {
  class player {
  public:
    player(std::string name, int attack, int health, ci::vec2 loc, po::SpritesheetAnimationRef sprite) {
      player_name = name;
      player_attack = attack;
      player_health = health;
      player_loc = loc;
      current_sprite = sprite;
    }
    player(){ }
    std::string getName();
    int getAttack();
    int getHealth();
    po::SpritesheetAnimationRef getSprite();
    ci::vec2 getLoc();
    void setHealth(int set_health);
    void setSprite(po::SpritesheetAnimationRef set_sprite);
    void setLoc(ci::vec2 set_loc);
    void draw();
  private:
    std::string player_name;
    int player_attack;
    int player_health;
    ci::vec2 player_loc;
    po::SpritesheetAnimationRef current_sprite;

  };

}

#endif //FINALPROJECT_PLAYER_H
