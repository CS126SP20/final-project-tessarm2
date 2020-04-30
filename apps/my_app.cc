// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>
#include <cinder/Json.h>


namespace myapp {

using cinder::app::KeyEvent;

  cinder::gl::Texture2dRef		mTex;
  po::SpritesheetAnimationRef chick_right_sprite;
  po::SpritesheetAnimationRef chick_left_sprite;
  po::SpritesheetAnimationRef chick_forward_sprite;
  po::SpritesheetAnimationRef chick_backward_sprite;

  MyApp::MyApp() { }

void MyApp::setup() {
  auto img = loadImage( loadAsset( "basic_bg.png" ) );
  mTex = cinder::gl::Texture2d::create( img );

  chick_right_sprite = SetUpSprite("chicken_right.png", "chicken_right.json");
  chick_left_sprite = SetUpSprite("chicken_left.png", "chicken_left.json");
  chick_forward_sprite = SetUpSprite("chicken_forward.png", "chicken_forward.json");
  chick_backward_sprite = SetUpSprite("chicken_backward.png", "chicken_backward.json");
  current_sprite = chick_forward_sprite;
  current_sprite->play();

  //set up objects
  auto yellow_img = loadImage( loadAsset( "yellow_block.png" ) );
  auto yellow_tex = cinder::gl::Texture2d::create( yellow_img );
  game_objects.push_back(myLibrary::game_object(yellow_tex, ci::vec2(200,200), "It's a yellow block!"));
  auto blue_img = loadImage( loadAsset( "blue_block.png" ) );
  auto blue_tex = cinder::gl::Texture2d::create( blue_img );
  game_objects.push_back(myLibrary::game_object(blue_tex, ci::vec2(400,400), "It's a blue block!"));

  //set up npcs
}

void MyApp::update() {
    if (current_sprite) {
      current_sprite->update();
    }
}

void MyApp::draw() {
  if (UI_state == UIState::kInputText) {
    cinder::gl::clear();
    drawTextInput();
  }
  if (game_state == GameState::kOpener){
    cinder::gl::clear();
    //make a new player object?
    PrintText("hello, " + player_name + "\n welcome to _____",
        ci::ColorA(1,1,1,1),
        ci::ColorA(0,0,0,1),
        cinder::ivec2(cinder::TextBox::GROW, cinder::TextBox::GROW),
        cinder::vec2(getWindowCenter()));
  }
  if (game_state == GameState::kOverworld) {
    cinder::gl::clear();
    drawBg();
    drawPlayer();
    drawObjects();
    if (UI_state == UIState::kTextbox) {
      drawTextbox(game_objects.at(object_facing_index).getDesc());
    }
  }
}

void MyApp::keyDown(KeyEvent event) {

  if (UI_state == UIState::kInputText) {
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
      if (text_input.text_options[text_input.current_row][text_input.current_col] == "OK") {
        cinder::gl::clear();
        UI_state = UIState::kClose;
        game_state = GameState::kOpener;
        return;
      } else if (text_input.text_options[text_input.current_row][text_input.current_col] == "DEL") {
        if (!player_name.empty()) {
          player_name.pop_back();
        }
      } else {
        if (player_name.size() < 9) {
          player_name += text_input.text_options[text_input.current_row][text_input.current_col];
        }
      }
    }
  } //end input text state

  if (game_state == GameState::kOpener) {
    if (event.getCode() == KeyEvent::KEY_z) {
      game_state = GameState::kOverworld;
      return;
    }
  } //end opener state

  if (game_state == GameState::kOverworld) {
    if (event.getCode() == KeyEvent::KEY_z) {
      if (UI_state == UIState::kTextbox) {
        UI_state = UIState::kClose;
      }
      if (canInteract()) {
        //update the UI with a lil text box!!
        UI_state = UIState::kTextbox;
      }
    }
    if (event.getCode() == KeyEvent::KEY_RIGHT) {
      current_direction = Direction::kRight;
      if (current_sprite != chick_right_sprite) {
        current_sprite = chick_right_sprite;
        current_sprite->play();
      }
      if (!(willColide(kSpeed, 0))) {
        if (player_loc.x < 700) {
          player_loc.x += kSpeed;
        } else {
          bg_loc.x += -kSpeed;
          updateObjects(-kSpeed,0);
        }
      }

    } else if (event.getCode() == KeyEvent::KEY_LEFT) {
      current_direction = Direction::kLeft;
      if (current_sprite != chick_left_sprite) {
        current_sprite = chick_left_sprite;
        current_sprite->play();
      }
      if (!(willColide(-kSpeed, 0))) {
        if (player_loc.x > 100) {
          player_loc.x += -kSpeed;
        } else {
          bg_loc.x += kSpeed;
          updateObjects(kSpeed,0);
        }
      }


    } else if (event.getCode() == KeyEvent::KEY_UP) {
      current_direction = Direction::kUp;
      if (current_sprite != chick_backward_sprite) {
        current_sprite = chick_backward_sprite;
        current_sprite->play();
      }
      if ((!willColide(0, -kSpeed))) {
        if (player_loc.y > 100) {
          player_loc.y += -kSpeed;
        } else {
          bg_loc.y += kSpeed;
          updateObjects(0, kSpeed);
        }
      }

    } else if (event.getCode() == KeyEvent::KEY_DOWN) {

      current_direction = Direction::kDown;
      if (current_sprite != chick_forward_sprite) {
        current_sprite = chick_forward_sprite;
        current_sprite->play();
      }
      if (!(willColide(0, kSpeed))) {
        if (player_loc.y < 540) {
          player_loc.y += kSpeed;
        } else {
          bg_loc.y += -kSpeed;
          updateObjects(0, -kSpeed);
        }
      }
    }
  } //end overworld state

}

void MyApp::drawPlayer() {
    ci::gl::pushModelMatrix();
    ci::gl::translate( player_loc );
    current_sprite->draw();
    ci::gl::popModelMatrix();
  }
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
  }

  void MyApp::updateObjects(int x_change, int y_change) {
    for (auto & game_object : game_objects) {
      //change the location of each object to scroll with background
      game_object.setLoc(ci::vec2(game_object.getLoc().x +
      x_change, game_object.getLoc().y + y_change));
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

  void MyApp::drawTextbox(const std::string& text) {
    auto box = cinder::TextBox()
        .alignment(cinder::TextBox::LEFT)
        .font(cinder::Font("Comic Sans MS", 25))
        .size(ci::ivec2(800, 40))
        .color(ci::ColorA(1,1,1,1))
        .backgroundColor(ci::ColorA(0,0,0,1))
        .text(text);
    const auto texture = cinder::gl::Texture::create(box.render());
    cinder::gl::draw(texture, ci::ivec2(0,540));
  }

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
    //add 16 because the location is the top right corner of the sprite.
    ci::vec2 updated_loc;
    if (current_direction == Direction::kRight) {
      updated_loc =  ci::vec2(player_loc.x + 4 + 32, player_loc.y + 16);
    } else if (current_direction == Direction::kLeft){
      updated_loc =  ci::vec2(player_loc.x - 4, player_loc.y + 16);
    } else if (current_direction == Direction::kUp) {
      updated_loc =  ci::vec2(player_loc.x + 16, player_loc.y - 4);
    } else {
      updated_loc =  ci::vec2(player_loc.x + 16, player_loc.y + 32 + 4);
    }
    for(int i = 0; i < game_objects.size(); i++) {
      auto size = game_objects.at(i).getTex()->getSize();
      auto obj_loc = game_objects.at(i).getLoc();
      //add the size to the location because location is top right corner of image.
      auto area = ci::Area(obj_loc, ci::ivec2(obj_loc.x + size.x, obj_loc.y + size.y));
      if (area.contains(updated_loc)) {
        object_facing_index = i;
        return true;
      }
    }
    object_facing_index = -1;
    return false;
  }

  bool MyApp::willColide(int x_change, int y_change) {
    //add 16 because the location is the top right corner of the sprite.
    ci::vec2 updated_loc = ci::vec2(player_loc.x + x_change + 16, player_loc.y + y_change + 16);
    for(int i = 0; i < game_objects.size(); i++) {
      auto size = game_objects.at(i).getTex()->getSize();
      auto obj_loc = game_objects.at(i).getLoc();
      //add the size to the location because location is top right corner of image.
      auto area = ci::Area(obj_loc, ci::ivec2(obj_loc.x + size.x, obj_loc.y + size.y));
      if (area.contains(updated_loc)) {
        return true;
      }
    }
    return false;
  }

}  // namespace myapp
