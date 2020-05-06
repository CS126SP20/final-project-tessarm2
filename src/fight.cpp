//
// Created by tessa on 5/5/2020.
//

#include "mylibrary/fight.h"
#include <cinder/gl/gl.h>

namespace myLibrary {


  fight::fight(myLibrary::NPC *set_enemy, myLibrary::player *set_player) {
    enemy = set_enemy;
    player = set_player;
  }

  void fight::drawPlayer() {
    //draws the sprite on the right side of the screen
    ci::gl::pushModelMatrix();
    ci::gl::translate( ci::vec2(600 ,320) );
    player->getSprite()->draw();
    //draws the healthbar
    cinder::gl::color(0,1,0);
    if (player->getHealth() < 0) {
      player->setHealth(0);
    }
    ci::gl::drawSolidRect(ci::Rectf(ci::vec2(0, -20), ci::vec2(player->getHealth(), -15)));
    cinder::gl::color(1,1,1);
    //draws the player name
    PrintText(player->getName(), ci::ColorA(1,1,1,1),
              ci::ColorA(0,0,0,0), ci::ivec2(ci::TextBox::GROW,ci::TextBox::GROW), ci::vec2(-20, -100));

    ci::gl::popModelMatrix();
  }

  void fight::drawEnemy() {
    //draws the sprite on the left side of the screen
    ci::gl::pushModelMatrix();
    ci::gl::translate( ci::vec2(200 ,320) );
    enemy->getSprite()->draw();
    //draws the health bar
    cinder::gl::color(0,1,0);
    if (enemy->getHealth() < 0) {
      enemy->setHealth(0);
    }
    ci::gl::drawSolidRect(ci::Rectf(ci::vec2(0, -20), ci::vec2(enemy->getHealth(), -15)));
    cinder::gl::color(1,1,1);
    //draws the enemy name
    PrintText(enemy->getName(), ci::ColorA(1,0,0,1),
        ci::ColorA(0,0,0,0), ci::ivec2(ci::TextBox::GROW,ci::TextBox::GROW), ci::vec2(-20, -100));

    ci::gl::popModelMatrix();
  }

  void fight::drawMenu() {
    //prints the 3 menu options
    for (int i = 0; i < 3; i++) {
      if (menu_index == i) {
        //the current index matches the index the player is on, so the text is yellow
        PrintText(menu_options[i],
                  ci::ColorA(1,1,0,1),
                  ci::ColorA(0,0,0,0),
                  cinder::ivec2(140,140), cinder::vec2(600, 450 + i*40.0));
      } else {
        PrintText(menu_options[i],
                  ci::ColorA(1,1,1,1),
                  ci::ColorA(0,0,0,0),
                  cinder::ivec2(140,140), cinder::vec2(600, 450 + i*40.0));
      }
    }
  }

  void fight::drawFlavorText() {
    PrintText(flavor_text, ci::ColorA(1,1,1,1), ci::ColorA(0,0,0,0), cinder::ivec2(300,300), cinder::vec2(300, 500));
  }
  //TAKEN FROM SNAKE GAME
  void fight::PrintText(const std::string& text, const ci::ColorA& color, const ci::ColorA& bg_color, const cinder::ivec2& size,
                        const cinder::vec2& loc) {

    auto box = cinder::TextBox()
        .alignment(cinder::TextBox::CENTER)
        .font(cinder::Font("Comic Sans MS", 40))
        .size(size)
        .color(color)
        .backgroundColor(bg_color)
        .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2.0, loc.y - box_size.y / 2.0};
    const auto texture = cinder::gl::Texture::create(box.render());
    cinder::gl::draw(texture, locp);
  }

  void fight::selectOption() {
    //sets up player action for back and forth in battle
    switch(menu_index) {
      case 0:
        flavor_text = "you attack!";
        player_action = PlayerAction::kAttack;
            break;
      case 1:
        flavor_text = "you rest...";
        player_action = PlayerAction::kRest;
        break;
      case 2:
        flavor_text = "you flee as fast as your little chicken legs can go";
        player_action = PlayerAction::kRun;
        break;
    }
  }

  void fight::step() {
    if (printed_end) {
      //the fight is exited after the end-text is printed
      fight_over = true;
      return;
    }
    if (enemy->getHealth() <= 0) {
      flavor_text = "you killed " + enemy->getName();
      //prints end so fight is exited on next 'step'
      printed_end = true;
      return;
    }
    if (player->getHealth() <= 0) {
      flavor_text = "Damn, " + enemy->getName() + " got you good... RIP";
      //prints end so fight is exited on next 'step'
      printed_end = true;
      return;
    }

    if (player_turn && player_action != PlayerAction::kRun) {
      //generates random num 1-15
      int rand_num = rand() % 15 + 1;
      int damage = rand_num + player->getAttack();
      if (player_action == PlayerAction::kRest) {
        player->setHealth(player->getHealth() + rand_num + 15);
        //player cant exceed max health when healing
        if (player->getHealth() > 100) {
          player->setHealth(100);
        }
        flavor_text = "you regain " + std::to_string(rand_num + 15)+" health";
        player_turn = false;
        return;
      } else {
        enemy->setHealth(enemy->getHealth() - damage);
        flavor_text = "you peck at the enemy for " + std::to_string(damage) + " damage";
        player_turn = false;
        return;
      }
    }

    if (enemy_turn) {
      //generates random num 1-15
      int rand_num = rand() % 15 + 1;
      int damage = rand_num + enemy->getAttack();
      flavor_text = "ouch, you suffer " + std::to_string(damage) +  " damage";
      player->setHealth(player->getHealth() - damage);
      enemy_turn = false;
      player_turn = true;
      return;
    }
    //its the enemy's turn, sets the flavor text and then the enemy attacks on the next 'step'
    flavor_text = enemy->getAttackDesc();
    enemy_turn = true;

  }

  bool fight::isTurnsOver() {
    //if either fighter is in a turn, this will return false
    return player_turn && !enemy_turn;
  }

  bool fight::isPlayerDead() {
    //used to make sure the death text is written out before changing screen
    return fight_over && player->getHealth() <= 0;
  }

  bool fight::isEnemyDead() {
    //used to make sure the death text is written out before changing screen
    return fight_over && enemy->getHealth() <= 0;
  }


}