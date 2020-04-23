// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/text_input.h>
#include <cinder/Text.h>
#include <cinder/Font.h>
#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>
#include <cinder/Json.h>


namespace myapp {

  enum class GameState {
    kOverworld,
    kOpener,
    kFight,
    kUI
  };

  enum class UIState {
    kInputText,
    kSelectingOption,
    kClose,
  };

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void drawTextInput();
  void PrintText(const std::string& text, const ci::ColorA& color, const ci::ColorA& bg_color, const cinder::ivec2& size,
                 const cinder::vec2& loc);

  std::string player_name = "Lonk";
  ci::vec2 player_loc = ci::vec2(400, 320);
  po::SpritesheetAnimationRef current_sprite;



private:
  GameState game_state;
  UIState UI_state = UIState::kInputText;
  myLibrary::Text_input text_input;

  void drawPlayer();

  po::SpritesheetAnimationRef SetUpSprite(const std::string& tex_file, const std::string& json_file);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
