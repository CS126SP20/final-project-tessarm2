// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/text_input.h>
#include <cinder/Text.h>
#include <cinder/Font.h>


namespace myapp {

  enum class GameState {
    kOverworld,
    kCutscene,
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
  std::string player_name = "Lonk";


private:
  GameState game_state;
  UIState UI_state = UIState::kInputText;
  myLibrary::Text_input text_input;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
