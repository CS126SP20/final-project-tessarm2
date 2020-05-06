// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>
#include <cinder/Json.h>
#include <mylibrary/fight.h>


namespace myapp {

using cinder::app::KeyEvent;
//for ease of access, player sprites and background image are saved globally
  cinder::gl::Texture2dRef		mTex;
  po::SpritesheetAnimationRef chick_right_sprite;
  po::SpritesheetAnimationRef chick_left_sprite;
  po::SpritesheetAnimationRef chick_forward_sprite;
  po::SpritesheetAnimationRef chick_backward_sprite;


  MyApp::MyApp() { }

void MyApp::setup() {
    //set up background image
  auto img = loadImage( loadAsset( "basic_bg.png" ) );
  mTex = cinder::gl::Texture2d::create( img );

  //set up the player sprites
  chick_right_sprite = SetUpSprite("chicken_right.png", "chicken_right.json");
  chick_left_sprite = SetUpSprite("chicken_left.png", "chicken_left.json");
  chick_forward_sprite = SetUpSprite("chicken_forward.png", "chicken_forward.json");
  chick_backward_sprite = SetUpSprite("chicken_backward.png", "chicken_backward.json");

  //set up objects
  auto yellow_img = loadImage( loadAsset( "yellow_block.png" ) );
  auto yellow_tex = cinder::gl::Texture2d::create( yellow_img );
  game_objects.push_back(myLibrary::game_object(yellow_tex, ci::vec2(200,200), "A small plot of seeds. Protect this from squirrels with your life."));

  auto blue_img = loadImage( loadAsset( "blue_block.png" ) );
  auto blue_tex = cinder::gl::Texture2d::create( blue_img );
  game_objects.push_back(myLibrary::game_object(blue_tex, ci::vec2(400,400), "A beautiful blue block! What's it doin' on a farm like this?"));

  auto h_fence_img = loadImage( loadAsset( "height_fence.png" ) );
  auto h_fence_tex = cinder::gl::Texture2d::create( h_fence_img );
  game_objects.push_back(myLibrary::game_object(h_fence_tex, ci::vec2(0,0), "It's a strong fence."));
  game_objects.push_back(myLibrary::game_object(h_fence_tex, ci::vec2(1870,0), "It's a strong fence."));

  auto w_fence_img = loadImage( loadAsset( "width_fence.png" ) );
  auto w_fence_tex = cinder::gl::Texture2d::create( w_fence_img );
  game_objects.push_back(myLibrary::game_object(w_fence_tex, ci::vec2(0,0), "It's a strong fence."));
  game_objects.push_back(myLibrary::game_object(w_fence_tex, ci::vec2(0,1030), "It's a strong fence."));

  //set up npcs
  auto bimg = loadImage( loadAsset( "brown_chick.png" ) );
  auto btex = cinder::gl::Texture2d::create(bimg);
  myLibrary::NPC brown_chick = myLibrary::NPC("Friendly Guy", "Hi there, could you help me? These demon guys are mean! Go take the 3 of em out.", "none", 5, 5, false, btex, ci::vec2(380, 320));
  brown_chick.setSprite(SetUpSprite("brown_chick_s.png", "brown_chick_s.json"));
  NPC_list.push_back(brown_chick);

  auto mDemon = loadImage( loadAsset( "mouth_demon_1.png" ) );
  auto demTex = cinder::gl::Texture2d::create(mDemon);
  myLibrary::NPC mouth_demon = myLibrary::NPC("The Chomper", "He's due for a dentist.", "It gnashes it's teeth and attacks!", 50, 10, true, demTex, ci::vec2(500, 400));
  mouth_demon.setSprite(SetUpSprite("mouth_demon_s.png", "mouth_demon_s.json"));
  NPC_list.push_back(mouth_demon);

  auto big_demon = loadImage( loadAsset( "chunky_demon_1.png" ) );
  auto big_dem_tex = cinder::gl::Texture2d::create(big_demon);
  myLibrary::NPC large_demon = myLibrary::NPC("Big Boi", "He big.", "He swings a boulder-sized fist at you.", 50, 20, true, big_dem_tex, ci::vec2(1000, 400));
  large_demon.setSprite(SetUpSprite("big_demon_s.png", "big_demon_s.json"));
  NPC_list.push_back(large_demon);

  auto tall_d = loadImage( loadAsset( "tall_2.png" ) );
  auto tall_tex = cinder::gl::Texture2d::create(tall_d);
  myLibrary::NPC tall_demon = myLibrary::NPC("Legs for Days", "She tall.", "She extends a leg and smacks ya.", 30, 40, true, tall_tex, ci::vec2(50, 900));
  tall_demon.setSprite(SetUpSprite("tall_demon_s.png", "tall_demon_s.json"));
  NPC_list.push_back(tall_demon);
}

void MyApp::update() {
    //update all the sprites
    if (player.getSprite()) {
      player.getSprite()->update();
      for (auto & NPC : NPC_list) {
        NPC.getSprite()->update();
      }
    }
}

void MyApp::draw() {
  if (UI_state == UIState::kInputText) {
    cinder::gl::clear();
    drawTextInput();
  } //end text-input

  if (game_state == GameState::kOpener){
    cinder::gl::clear();
    //make a new player object?
    PrintText("hello, " + player_name + "\n welcome to the farm!",
        ci::ColorA(1,1,1,1),
        ci::ColorA(0,0,0,1),
        cinder::ivec2(cinder::TextBox::GROW, cinder::TextBox::GROW),
        cinder::vec2(getWindowCenter()));
  } //end opener

  if (game_state == GameState::kOverworld) {
    cinder::gl::clear();
    drawBg();
    player.draw();
    drawObjects();
    //an object has been encountered and the UI state has been switched to textbox
    if (UI_state == UIState::kTextbox && object_facing_index != -1) {
      if (is_NPC) {
        drawTextbox(NPC_list.at(object_facing_index).getName() + ": " +
        NPC_list.at(object_facing_index).getDesc());
        if (NPC_list.at(object_facing_index).getIsEnemy()) {
          //the NPC is hostile, so start a new fight
          game_state = GameState::kFight;
          UI_state = UIState::kSelectingOption;
          player.setSprite(chick_left_sprite);
          player.getSprite()->play();

          //make a new fight object with the monster
          current_fight = myLibrary::fight(&NPC_list.at(object_facing_index), &player);
        }
      } else {
        drawTextbox(game_objects.at(object_facing_index).getDesc());
      }
    }
  } //end overworld

  if (game_state == GameState::kFight) {
    //changes color of the background between red and purple during fight
    float red_change = sin( getElapsedSeconds() ) * 0.2f + 0.2f;
    float blue_change = cos( getElapsedSeconds() ) * 0.2f + 0.2f;
    cinder::gl::clear(ci::Color(red_change,0,blue_change));

    current_fight.drawPlayer();
    current_fight.drawEnemy();
    current_fight.drawFlavorText();
    if (UI_state == UIState::kSelectingOption) {
      current_fight.drawMenu();
    }
  }
  if (game_state == GameState::kGameOver) {
    cinder::gl::clear();
    drawTextbox("Better luck next time, " + player.getName());
  } //end fight
}

void MyApp::keyDown(KeyEvent event) {

  if (UI_state == UIState::kInputText) {
    //navigate through 2D array of alphabet with keyboard, press z to select
    if (event.getCode() == KeyEvent::KEY_RIGHT) {
      if (text_input.current_col < 6) {
        text_input.current_col++;
      }
    }
    if (event.getCode() == KeyEvent::KEY_LEFT) {
      if (text_input.current_col > 0) {
        text_input.current_col--;
      }
    }
    if (event.getCode() == KeyEvent::KEY_UP) {
      if (text_input.current_row > 0) {
        text_input.current_row--;
      }
    }
    if (event.getCode() == KeyEvent::KEY_DOWN) {
      if (text_input.current_row < 3) {
        text_input.current_row++;
      }
    }
    if (event.getCode() == KeyEvent::KEY_z) {
      //user is done inputing, change world state
      if (text_input.text_options[text_input.current_row][text_input.current_col] == "OK") {
        cinder::gl::clear();
        UI_state = UIState::kClose;
        game_state = GameState::kOpener;
        return;
        //user is deleting text
      } else if (text_input.text_options[text_input.current_row][text_input.current_col] == "DEL") {
        if (!player_name.empty()) {
          player_name.pop_back();
        }
      } else {
        //max 10 char limit
        if (player_name.size() <= 9) {
          player_name += text_input.text_options[text_input.current_row][text_input.current_col];
        }
      }
    }
  } //end input text state

  if (game_state == GameState::kOpener) {
    //set up player during opening
    player = myLibrary::player(player_name, 10, 100, ci::vec2(400, 320), chick_forward_sprite);
    player.getSprite()->play();

    if (event.getCode() == KeyEvent::KEY_z) {
      game_state = GameState::kOverworld;
      return;
    }
  } //end opener state

  if (game_state == GameState::kOverworld) {
    if (event.getCode() == KeyEvent::KEY_z) {
      if (UI_state == UIState::kTextbox) {
        //close the open textbox
        UI_state = UIState::kClose;
      }
      if (canInteract()) {
        //update the UI with a lil text box!!
        UI_state = UIState::kTextbox;
      }
    }
    //manipulate the player sprite based on what key was pressed
    if (event.getCode() == KeyEvent::KEY_RIGHT) {
      UI_state = UIState::kClose;
      current_direction = Direction::kRight;
      if (player.getSprite() != chick_right_sprite) {
        player.setSprite(chick_right_sprite);
        player.getSprite()->play();
      }
      if (!(canInteract())) {
        if (player.getLoc().x < 700) {
          player.setLoc(ci::vec2(player.getLoc().x + kSpeed, player.getLoc().y));
        } else {
          bg_loc.x += -kSpeed;
          updateObjects(-kSpeed,0);
        }
      }

    } else if (event.getCode() == KeyEvent::KEY_LEFT) {
      UI_state = UIState::kClose;
      current_direction = Direction::kLeft;
      if (player.getSprite() != chick_left_sprite) {
        player.setSprite(chick_left_sprite);
        player.getSprite()->play();
      }
      if (!(canInteract())) {
        if (player.getLoc().x > 100) {
          player.setLoc(ci::vec2(player.getLoc().x - kSpeed, player.getLoc().y));
        } else {
          bg_loc.x += kSpeed;
          updateObjects(kSpeed,0);
        }
      }


    } else if (event.getCode() == KeyEvent::KEY_UP) {
      UI_state = UIState::kClose;
      current_direction = Direction::kUp;
      if (player.getSprite() != chick_backward_sprite) {
        player.setSprite(chick_backward_sprite);
        player.getSprite()->play();
      }
      if ((!canInteract())) {
        if (player.getLoc().y > 100) {
          player.setLoc(ci::vec2(player.getLoc().x, player.getLoc().y - kSpeed));
        } else {
          bg_loc.y += kSpeed;
          updateObjects(0, kSpeed);
        }
      }

    } else if (event.getCode() == KeyEvent::KEY_DOWN) {
      UI_state = UIState::kClose;
      current_direction = Direction::kDown;
      if (player.getSprite() != chick_forward_sprite) {
        player.setSprite(chick_forward_sprite);
        player.getSprite()->play();
      }
      if (!(canInteract())) {
        if (player.getLoc().y < 540) {
          player.setLoc(ci::vec2(player.getLoc().x, player.getLoc().y + kSpeed));
        } else {
          bg_loc.y += -kSpeed;
          updateObjects(0, -kSpeed);
        }
      }
    }
  } //end overworld state

  if (game_state == GameState::kFight) {
    if (UI_state == UIState::kSelectingOption) {
      //navigate fight menu with arrow-keys
      if (event.getCode()== KeyEvent::KEY_DOWN && current_fight.menu_index < 2) {
        current_fight.menu_index++;
      }
      if (event.getCode() == KeyEvent::KEY_UP && current_fight.menu_index > 0) {
        current_fight.menu_index--;
      }
      if (event.getCode() == KeyEvent::KEY_z) {
        current_fight.selectOption();
        UI_state = UIState::kClose;
      }
      //do fight things then reopen menu
    }
    if (event.getCode() == KeyEvent::KEY_z) {
      //displays text of each turn and continues when the user presses z
      current_fight.step();
      if (current_fight.isTurnsOver() && player.getHealth() > 0) {
        UI_state = UIState::kSelectingOption;
      }
      if (current_fight.isPlayerDead()) {
        UI_state = UIState::kClose;
        game_state = GameState::kGameOver;
      }
      if (current_fight.isEnemyDead()) {
        UI_state = UIState::kClose;
        game_state = GameState::kOverworld;
      }
    }
    if (current_fight.player_action == myLibrary::PlayerAction::kRun) {
      game_state = GameState::kOverworld;
    }
  } //end fight state

} //end keyboard input

  void MyApp::drawBg() {
    ci::gl::pushModelMatrix();
    ci::gl::translate( bg_loc );
    ci::gl::draw(mTex);
    ci::gl::popModelMatrix();
  }

  void MyApp::drawObjects() {
    for (auto & game_object : game_objects) {
      game_object.draw();
    }
    for (auto & NPC : NPC_list) {
      if (NPC.getHealth() > 0) {
        NPC.draw();
      }
    }
  }

  void MyApp::updateObjects(int x_change, int y_change) {
    //scrolls all objects and NPCs
    for (auto & game_object : game_objects) {
      //change the location of each object to scroll with background
      game_object.setLoc(ci::vec2(game_object.getLoc().x +
      x_change, game_object.getLoc().y + y_change));
    }
    for (auto & NPC : NPC_list) {
      //change the location of each NPC to scroll with background
      NPC.setLoc(ci::vec2(NPC.getLoc().x +
                                  x_change, NPC.getLoc().y + y_change));
    }
  }

  void MyApp::drawTextInput() {
    PrintText(player_name, ci::ColorA(1,1,1,1), ci::ColorA(0,0,0,1),
        cinder::ivec2(800, cinder::TextBox::GROW), cinder::vec2(400, 50));
    //use a for loop to draw all the chars
    cinder::vec2 center = cinder::vec2(240,150);
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 7; col++) {
        if (text_input.current_row == row && text_input.current_col == col) {
          //the current index matches the index the player is on, so the text is yellow
          PrintText(text_input.text_options[row][col],
                    ci::ColorA(1,1,0,1),
                    ci::ColorA(0,0,0,0),
                    cinder::ivec2(140,140), cinder::vec2(center.x + col *60.0,center.y + row *60.0));
        } else {
          PrintText(text_input.text_options[row][col],
                    ci::ColorA(1,1,1,1),
                    ci::ColorA(0,0,0,0),
                    cinder::ivec2(140,140), cinder::vec2(center.x + col *60.0,center.y + row *60.0));
        }
      }
    }

  }

  //TAKEN FROM SNAKE GAME
  void MyApp::PrintText(const std::string& text, const ci::ColorA& color, const ci::ColorA& bg_color, const cinder::ivec2& size,
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

  //draw a textbox at the bottom of the screen, used when no customizaiton is needed
  void MyApp::drawTextbox(const std::string& text) {
    auto box = cinder::TextBox()
        .alignment(cinder::TextBox::LEFT)
        .font(cinder::Font("Comic Sans MS", 25))
        .size(ci::ivec2(800, cinder::TextBox::GROW))
        .color(ci::ColorA(1,1,1,1))
        .backgroundColor(ci::ColorA(0,0,0,1))
        .text(text);
    const auto texture = cinder::gl::Texture::create(box.render());
    cinder::gl::draw(texture, ci::ivec2(0,540));
  }

  //returns a set up sprite
  po::SpritesheetAnimationRef MyApp::SetUpSprite(const std::string& tex_file, const std::string& json_file) {
    auto chicken_tex = cinder::gl::Texture::create(loadImage(loadAsset(tex_file)));
    auto json = cinder::JsonTree(loadAsset(json_file));
    auto mSpritesheet = po::Spritesheet::create(chicken_tex, json);
    po::SpritesheetAnimationRef sprite = po::SpritesheetAnimation::create(mSpritesheet);
    sprite->setIsLoopingEnabled(true);
    sprite->setFrameRate(2.0 * kSpeed);
    return sprite;
  }

  bool MyApp::canInteract() {
    ci::vec2 updated_loc;
    //creates a potential new location for the player based on the direction
    //and makes sure that point is not inside another sprite
    switch(current_direction) {
      case Direction::kRight:
        //32x32 is the size of the chicken sprite
        updated_loc =  ci::vec2(player.getLoc().x + kSpeed + 32, player.getLoc().y + 16);
        break;
      case Direction::kLeft:
        updated_loc =  ci::vec2(player.getLoc().x - kSpeed, player.getLoc().y + 16);
        break;
      case Direction::kUp:
        updated_loc =  ci::vec2(player.getLoc().x + 16, player.getLoc().y - kSpeed);
        break;
      case Direction::kDown:
        updated_loc =  ci::vec2(player.getLoc().x + 16, player.getLoc().y + 32 + kSpeed);
        break;
    }

    for(int i = 0; i < game_objects.size(); i++) {
      auto size = game_objects.at(i).getTex()->getSize();
      auto obj_loc = game_objects.at(i).getLoc();
      //add the size to the location because location is top right corner of image.
      auto area = ci::Area(obj_loc, ci::ivec2(obj_loc.x + size.x, obj_loc.y + size.y));
      if (area.contains(updated_loc)) {
        object_facing_index = i;
        is_NPC = false;
        return true;
      }
    }
    for(int i = 0; i < NPC_list.size(); i++) {
      auto size = NPC_list.at(i).getTex()->getSize();
      auto obj_loc = NPC_list.at(i).getLoc();
      //add the size to the location because location is top right corner of image.
      auto area = ci::Area(obj_loc, ci::ivec2(obj_loc.x + size.x, obj_loc.y + size.y));
      if (area.contains(updated_loc) && NPC_list.at(i).getHealth() > 0) {
        object_facing_index = i;
        is_NPC = true;
        return true;
      }
    }
    object_facing_index = -1;
    return false;
  }


}  // namespace myapp
