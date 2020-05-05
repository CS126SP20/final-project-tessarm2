//
// Created by tessa on 5/5/2020.
//

#include "mylibrary/fight.h"
#include <cinder/gl/gl.h>

namespace myLibrary {


  fight::fight(myLibrary::NPC set_enemy, myLibrary::player set_player) {
    enemy = set_enemy;
    player = set_player;
  }

  void fight::drawPlayer() {
    ci::gl::pushModelMatrix();
    ci::gl::translate( ci::vec2(600 ,320) );
    player.getSprite()->draw();
    cinder::gl::color(0,1,0);
    ci::gl::drawSolidRect(ci::Rectf(ci::vec2(0, -20), ci::vec2(player.getHealth(), -15)));
    cinder::gl::color(1,1,1);
    PrintText(player.getName(), ci::ColorA(1,1,1,1),
              ci::ColorA(0,0,0,0), ci::ivec2(ci::TextBox::GROW,ci::TextBox::GROW), ci::vec2(-20, -100));

    ci::gl::popModelMatrix();
  }

  void fight::drawEnemy() {
    ci::gl::pushModelMatrix();
    ci::gl::translate( ci::vec2(200 ,320) );
    enemy.getSprite()->draw();
    cinder::gl::color(0,1,0);
    ci::gl::drawSolidRect(ci::Rectf(ci::vec2(0, -20), ci::vec2(enemy.getHealth(), -15)));
    cinder::gl::color(1,1,1);
    PrintText(enemy.getName(), ci::ColorA(1,0,0,1),
        ci::ColorA(0,0,0,0), ci::ivec2(ci::TextBox::GROW,ci::TextBox::GROW), ci::vec2(-20, -100));

    ci::gl::popModelMatrix();
  }

  void fight::drawMenu() {
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
    //player action
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
    //player does their thing
    if (printed_end) {
      fight_over = true;
      return;
    }
    if (enemy.getHealth() <= 0) {
      flavor_text = "You killed " + enemy.getName();
      printed_end = true;
      return;
    }
    if (player.getHealth() <= 0) {
      flavor_text = "Damn, " + enemy.getName() + " got you good... RIP";
      printed_end = true;
      return;
    }
    
    if (player_turn) {
      if (player_action == PlayerAction::kRest) {
        player.setHealth(player.getHealth() + 25);
        if (player.getHealth() > 100) {
          player.setHealth(100);
        }
        flavor_text = "you regain some health";
        player_turn = false;
        return;
      } else {
        enemy.setHealth(enemy.getHealth() - player.getAttack());
        flavor_text = "you peck at the enemy";
        player_turn = false;
        return;
      }
    }

    if (enemy_turn) {
      flavor_text = "You suffer damage";
      player.setHealth(player.getHealth() - enemy.getAttack());
      enemy_turn = false;
      player_turn = true;
      return;
    }
    //its the enemy's turn
    flavor_text = enemy.getAttackDesc();
    enemy_turn = true;

  }

  bool fight::isTurnsOver() {
    //if either fighter is in a turn, this will return false
    return player_turn && !enemy_turn;
  }

  bool fight::isPlayerDead() {
    if (fight_over && player.getHealth() <= 0) {
      return true;
    }
    return false;
  }

  bool fight::isEnemyDead() {
    if (fight_over && enemy.getHealth() <= 0) {
      return true;
    }
    return false;
  }


}