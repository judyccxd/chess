#ifndef HUMAN_H
#define HUMAN_H
#include "player.h"

class Human: public Player {

 public:
  Human(bool colour, std::string player);
  ~Human();

};
#endif
