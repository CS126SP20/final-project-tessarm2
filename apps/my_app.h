// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/text_input.h>
#include <mylibrary/game_object.h>
#include <cinder/Text.h>
#include <cinder/Font.h>
#include <poSpritesheet.h>
#include <poSpritesheetAnimation.h>
#include <cinder/Json.h>
#include <mylibrary/NPC.h>
#include <mylibrary/player.h>
#include <mylibrary/fight.h>


namespace myapp {

  enum class GameState {
    kOverworld,
    kOpener,
    kFight,
    kGameOver
  };

  enum class UIState {
    kInputText,
    kTextbox,
    kSelectingOption,
    kClose,
  };

  enum class Direction {
    kRight,
    kLeft,
    kUp,
    kDown,
  };

  const int kSpeed = 4;

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
  myLibrary::fight current_fight;



private:
  GameState game_state;
  UIState UI_state = UIState::kInputText;
  myLibrary::Text_input text_input;
  Direction current_direction;
  bool is_NPC = false;
  myLibrary::player player;

  std::string player_name = "Lonk";
  ci::vec2 bg_loc = ci::vec2(0,0);
  std::vector<myLibrary::game_object> game_objects;
  std::vector<myLibrary::NPC> NPC_list;
  int object_facing_index = -1;


  po::SpritesheetAnimationRef SetUpSprite(const std::string& tex_file, const std::string& json_file);
  bool canInteract();

  void drawBg();
  void drawObjects();
  void updateObjects(int x_change, int y_change);
  void MyApp::drawTextbox(const std::string& text);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
