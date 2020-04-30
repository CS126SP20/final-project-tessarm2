//
// Created by tessa on 4/21/2020.
//

#include "mylibrary/NPC.h"
#include <cinder/gl/gl.h>


namespace myLibrary {

  void NPC::draw() {
    ci::gl::pushModelMatrix();
    ci::gl::translate(location);
    sprite->draw();
    ci::gl::popModelMatrix();
  }
  void NPC::setHealth(int setHealth) {
    health = setHealth;
  }
  void NPC::setIsEnemy(bool isEnemy) {
    is_enemy = isEnemy;
  }
  void NPC::setDesc(std::string setDesc) {
    desc = setDesc;
  }
  int NPC::getHealth() {
    return health;
  }
  int NPC::getIsEnemy() {
    return is_enemy;
  }
  int NPC::getAttack() {
    return attack;
  }
  std::string NPC::getName() {
    return name;
  }
  std::string NPC::getDesc() {
    return desc;
  }
  std::string NPC::getAttackDesc() {
    return attack_desc;
  }

  void NPC::setLoc(ci::vec2 setLoc) {
    location = setLoc;
  }

  ci::vec2 NPC::getLoc() {
    return location;
  }

  cinder::gl::Texture2dRef NPC::getTex() {
    return obj_tex;
  }

  void NPC::setSprite(po::SpritesheetAnimationRef set_sprite) {
    sprite = set_sprite;
    sprite->play();
  }

  po::SpritesheetAnimationRef NPC::getSprite() {
    return sprite;
  }
}