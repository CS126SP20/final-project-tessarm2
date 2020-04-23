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
  cinder::gl::Texture2dRef		chicken_tex;
  cinder::JsonTree json;
  po::SpritesheetRef mSpritesheet;
  po::SpritesheetAnimationRef mSpritesheetAnimation;


  MyApp::MyApp() { }

void MyApp::setup() {
  auto img = loadImage( loadAsset( "test_bg.jpg" ) );
  mTex = cinder::gl::Texture2d::create( img );
  chicken_tex = cinder::gl::Texture::create(loadImage(loadAsset("chicken_forward.png")));
  json = cinder::JsonTree(loadAsset("chicken_forward.json"));
   mSpritesheet = po::Spritesheet::create(chicken_tex, json);
   mSpritesheetAnimation = po::SpritesheetAnimation::create(mSpritesheet);
  mSpritesheetAnimation->setIsLoopingEnabled(true);
  mSpritesheetAnimation->setFrameRate(4.0);
  mSpritesheetAnimation->play();
}

void MyApp::update() {
  mSpritesheetAnimation->update();
}

void MyApp::draw() {
  if (UI_state == UIState::kInputText) {
    //cinder::gl::draw( chicken_tex );
    cinder::gl::clear();
    mSpritesheetAnimation->draw();

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
}

  void MyApp::drawTextInput() {
  //bug where last letter deleted remains
    PrintText(player_name, ci::ColorA(1,1,1,1), ci::ColorA(0,0,0,1),
        cinder::ivec2(800, cinder::TextBox::GROW), cinder::vec2(400, 50));
    //use a for loop to draw all the chars
    cinder::vec2 center = cinder::vec2(240,150);
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 7; col++) {
        if (text_input.current_row == row && text_input.current_col == col) {
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


}  // namespace myapp
