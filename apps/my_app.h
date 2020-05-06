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




private:
  //current game state, ie the player is in a fight or exploring the map
  GameState game_state;
  //sets the UI_state to input text at the begining
  UIState UI_state = UIState::kInputText;
  //text_input that contains alphabet
  myLibrary::Text_input text_input;
  //the direction the player is facing
  Direction current_direction;
  //whether the player is facing an NPC or an object
  bool is_NPC = false;
  //the player object
  myLibrary::player player;
  //the fight the player is in, passed an NPC and a player
  myLibrary::fight current_fight;
  //the string displayed above the text_input
  std::string player_name = "input name";
  //location of the background
  ci::vec2 bg_loc = ci::vec2(0,0);
  //list of all the objects in the overworld
  std::vector<myLibrary::game_object> game_objects;
  //list of NPCs in the overworld
  std::vector<myLibrary::NPC> NPC_list;
  //index of what the player is facing, defaults to -1 when not facing anything
  int object_facing_index = -1;

  //returns a sprite animation based on the given sprite-sheet png and json sprite data
  po::SpritesheetAnimationRef SetUpSprite(const std::string& tex_file, const std::string& json_file);
  //updates the players location based on the direction they are facing and checks that
  //the point is not in an Object or NPC sprite frame
  bool canInteract();
  //draws the background image
  void drawBg();
  //draws all the object and NPC sprites on the screen
  void drawObjects();
  //iterates through the NPC and Object list and sets their locations based on the x_change and y_change
  void updateObjects(int x_change, int y_change);
  //draws a small text at the bottom of the screen. used when no customization is needed
  void drawTextbox(const std::string& text);
  //draws the alphabet from text_input and highlights the selected character
  void drawTextInput();
  //prints a custom textbox
  void PrintText(const std::string& text, const ci::ColorA& color, const ci::ColorA& bg_color, const cinder::ivec2& size,
                 const cinder::vec2& loc);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
