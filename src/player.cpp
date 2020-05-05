//
// Created by tessa on 4/21/2020.
//

#include "mylibrary/player.h"
namespace myLibrary {
  void myLibrary::player::draw() {
    ci::gl::pushModelMatrix();
    ci::gl::translate( player_loc );
    current_sprite->draw();
    ci::gl::popModelMatrix();
  }

  std::string player::getName() {
    return player_name;
  }

  int player::getAttack() {
    return player_attack;
  }

  int player::getHealth() {
    return player_health;
  }

  po::SpritesheetAnimationRef player::getSprite() {
    return current_sprite;
  }

  ci::vec2 player::getLoc() {
    return player_loc;
  }

  void player::setHealth(int set_health) {
    player_health = set_health;
  }

  void player::setSprite(po::SpritesheetAnimationRef set_sprite) {
    current_sprite = set_sprite;
  }

  void player::setLoc(ci::vec2 set_loc) {
    player_loc = set_loc;
  }

}

