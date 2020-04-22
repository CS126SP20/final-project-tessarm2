//
// Created by tessa on 4/21/2020.
//

#ifndef FINALPROJECT_TEXT_INPUT_H
#define FINALPROJECT_TEXT_INPUT_H

namespace myLibrary {

  class Text_input {
  public:
    std::string text_options[4][7] {
      "a","b","c","d","e","f","g",
          "h","i","j","k","l","m","n",
          "o","p","q","r","s","t","u",
          "v","w","x","y","z","OK","DEL"
    };
    int current_row = 0;
    int current_col = 0;
  };

} //namespace myLibrary

#endif //FINALPROJECT_TEXT_INPUT_H
