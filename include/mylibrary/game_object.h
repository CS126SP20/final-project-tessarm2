//
// Created by tessa on 4/29/2020.
//

#ifndef FINALPROJECT_GAME_OBJECT_H
#define FINALPROJECT_GAME_OBJECT_H

#include <cinder/gl/gl.h>
#include <cinder/app/App.h>


namespace myLibrary {

  class game_object {
  public:
    //constructor
    game_object(cinder::gl::Texture2dRef tex, ci::vec2 location, std::string desc) {
      obj_location = location;
      obj_desc = desc;
      obj_tex = tex;
    }

    //getters
    std::string getDesc();
    ci::vec2 getLoc();
    cinder::gl::Texture2dRef getTex();

    //setter
    void setLoc(ci::vec2 new_loc);

    void draw();

  private:
    std::string obj_desc;
    ci::vec2 obj_location;
    cinder::gl::Texture2dRef obj_tex;

  };

} //namespace myLibrary

#endif //FINALPROJECT_GAME_OBJECT_H
