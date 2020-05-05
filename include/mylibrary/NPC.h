//
// Created by tessa on 4/21/2020.
//

#ifndef FINALPROJECT_NPC_H
#define FINALPROJECT_NPC_H

#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>
#include <cinder/gl/gl.h>
#include <cinder/app/App.h>


namespace myLibrary {
  class NPC {
  public:
    NPC(std::string sName, std::string sDesc, std::string atDesc, int sHealth,
        int sAttack, bool enemy, cinder::gl::Texture2dRef tex, ci::vec2 sLoc) {
      name = sName;
      desc = sDesc;
      attack_desc = atDesc;
      health = sHealth;
      attack = sAttack;
      is_enemy = enemy;
      obj_tex = tex;
      location = sLoc;
    }
    NPC(){ }
    void draw();
    void setHealth(int health);
    void setIsEnemy(bool isEnemey);
    void setDesc(std::string desc);
    void setLoc(ci::vec2 setLoc);
    void setSprite(po::SpritesheetAnimationRef set_sprite);
    po::SpritesheetAnimationRef getSprite();
    int getHealth();
    int getIsEnemy();
    int getAttack();
    std::string getName();
    std::string getDesc();
    std::string getAttackDesc();
    ci::vec2 getLoc();
    cinder::gl::Texture2dRef getTex();


  private:
    std::string name;
    std::string desc;
    std::string attack_desc;
    int health;
    int attack;
    bool is_enemy;
    ci::vec2 location;
    cinder::gl::Texture2dRef obj_tex;
    po::SpritesheetAnimationRef sprite;


  };

}


#endif //FINALPROJECT_NPC_H
