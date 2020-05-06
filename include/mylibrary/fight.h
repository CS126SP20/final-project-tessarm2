//
// Created by tessa on 5/5/2020.
//

#ifndef FINALPROJECT_FIGHT_H
#define FINALPROJECT_FIGHT_H

#include "NPC.h"
#include "player.h"

namespace myLibrary {

  enum class PlayerAction {
    kAttack,
    kRun,
    kRest
  };

  class fight {
  public:
    fight(myLibrary::NPC *set_enemy, myLibrary::player *set_player);
    fight() { }
    void drawPlayer();
    void drawEnemy();
    void drawMenu();
    void drawFlavorText();
    void selectOption();
    void step();
    bool isTurnsOver();
    bool isPlayerDead();
    bool isEnemyDead();
    int menu_index = 0;
    PlayerAction player_action;


  private:
    std::string menu_options[3] { "attack", "rest", "run!"};
    myLibrary::NPC *enemy;
    myLibrary::player *player;
    std::string flavor_text = "What would you like to do?";
    void PrintText(const std::string &text, const cinder::ColorA &color,
                   const cinder::ColorA &bg_color, const glm::ivec2 &size,
                   const glm::vec2 &loc);
    bool player_turn = true;
    bool enemy_turn = false;
    bool printed_end = false;
    bool fight_over = false;
  };

}


#endif //FINALPROJECT_FIGHT_H
