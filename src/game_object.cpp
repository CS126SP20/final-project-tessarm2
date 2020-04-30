//
// Created by tessa on 4/29/2020.
//

#include <string>
#include "mylibrary/game_object.h"

namespace myLibrary {

  std::string game_object::getDesc() {
    return obj_desc;
  }

  ci::vec2 game_object::getLoc() {
    return obj_location;
  }

  cinder::gl::Texture2dRef game_object::getTex() {
    return obj_tex;
  }

  void game_object::setLoc(ci::vec2 new_loc) {
    obj_location = new_loc;
  }

  void game_object::draw() {
    ci::gl::pushModelMatrix();
    ci::gl::translate(obj_location);
    ci::gl::draw(obj_tex);
    ci::gl::popModelMatrix();
  }
} //namespace myLibrary