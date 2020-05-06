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
    //constructors
    fight(myLibrary::NPC *set_enemy, myLibrary::player *set_player);
    fight() { }

    //draws the player sprite, health, and name on the right side of screen
    void drawPlayer();
    //draws the enemy sprite, health, and name on left side of screen
    void drawEnemy();
    //draws the three options in the menu in lower right of screen
    void drawMenu();
    //draws descriptive text to the left of the menu
    void drawFlavorText();
    //sets the flavor text to describe the action and the player_action to what
    //is selected in the menu
    void selectOption();
    //plays the next step based on what is happening in the battle. Returns so player
    //can press z to continue the fight
    void step();
    //returns true if both the player and enemy went, so my_app can open the menu again
    bool isTurnsOver();
    //returns true if the player is dead and the end text is printed
    bool isPlayerDead();
    //returns true if the enemy is dead and the end text is printed
    bool isEnemyDead();
    //the index for scrolling through the menu
    int menu_index = 0;
    //the action the player selected
    PlayerAction player_action;


  private:
    //menu options that are printed on screen
    std::string menu_options[3] { "attack", "rest", "run!"};
    //pointer to an NPC object that the player is fighting
    myLibrary::NPC *enemy;
    //pointer to the player object that is fighting
    myLibrary::player *player;
    //text that describes action of fight
    std::string flavor_text = "What would you like to do?";
    //same print text as in my_app for ease of formatting
    void PrintText(const std::string &text, const cinder::ColorA &color,
                   const cinder::ColorA &bg_color, const glm::ivec2 &size,
                   const glm::vec2 &loc);
    //flag for if the player is going
    bool player_turn = true;
    //flag for if the enemy is going
    bool enemy_turn = false;
    //flag for if the end text is one screen
    bool printed_end = false;
    //flag for if the fight is over and player has read the end text
    bool fight_over = false;
  };

}


#endif //FINALPROJECT_FIGHT_H
