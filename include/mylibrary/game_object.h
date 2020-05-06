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
    //the description and texture should not be changed after creation
    void setLoc(ci::vec2 new_loc);

    //draws the game object on the screen
    void draw();

  private:
    //description of object for interaction
    std::string obj_desc;
    //location of object
    ci::vec2 obj_location;
    //texture of object
    cinder::gl::Texture2dRef obj_tex;

  };

} //namespace myLibrary

#endif //FINALPROJECT_GAME_OBJECT_H
