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


namespace myapp {

  enum class GameState {
    kOverworld,
    kOpener,
    kFight,
    kUI
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


private:
  GameState game_state;
  UIState UI_state = UIState::kInputText;
  myLibrary::Text_input text_input;
  Direction current_direction;
  bool is_NPC = false;

  std::string player_name = "Lonk";
  int player_health = 100;
  ci::vec2 player_loc = ci::vec2(400, 320);
  ci::vec2 bg_loc = ci::vec2(0,0);
  po::SpritesheetAnimationRef current_sprite;
  std::vector<myLibrary::game_object> game_objects;
  std::vector<myLibrary::NPC> NPC_list;
  int object_facing_index = -1;

  void drawPlayer();

  po::SpritesheetAnimationRef SetUpSprite(const std::string& tex_file, const std::string& json_file);
  bool canInteract();

  void drawBg();
  void drawObjects();
  void updateObjects(int x_change, int y_change);
  void MyApp::drawTextbox(const std::string& text);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
