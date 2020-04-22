// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/gl.h>


namespace myapp {

using cinder::app::KeyEvent;


MyApp::MyApp() { }

void MyApp::setup() { }

void MyApp::update() {



}

void MyApp::draw() {
  if (UI_state == UIState::kInputText) {
    drawTextInput();
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
      } else if (text_input.text_options[text_input.current_row][text_input.current_col] == "DEL") {
        if (player_name.size() > 0) {
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
    cinder::TextBox tbox = cinder::TextBox().alignment(cinder::TextBox::LEFT).
        font(cinder::Font("Arial", 30)).text(player_name).size(cinder::ivec2(800, cinder::TextBox::GROW));
    tbox.setColor(ci::ColorA(0,0,0,1));
    tbox.setBackgroundColor(ci::ColorA(1.0f, 1.0f, 1.0f, 1.0f));
    tbox.setPremultiplied(true);
    tbox.setLigate(true);
    auto mTextTexture = ci::gl::Texture2d::create(tbox.render());
    cinder::gl::ScopedBlendPremult blend;
    cinder::gl::draw( mTextTexture );

  }



}  // namespace myapp
