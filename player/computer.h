#ifndef COMPUTER_H
#define COMPUTER_H
#include "player.h"

class Computer: public Player {
  std::string level;

 public:
  Computer(bool colour, std::string player);
  ~Computer();

  void setLevel(std::string l) override;
  std::string getLevel() override;

};
#endif
