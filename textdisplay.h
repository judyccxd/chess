#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "cell.h"
class Cell;

class TextDisplay {
  std::vector<std::vector<char>> theDisplay;
  const int size = 8; //you may or may not need to use this

 public:
  TextDisplay();

  //void notify(Subject &whoNotified) override;

  ~TextDisplay();

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
