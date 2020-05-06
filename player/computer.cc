#include "computer.h"

Computer::Computer(bool colour, std::string player): Player{colour, player}
, level{""} {}


Computer::~Computer() {}

void Computer::setLevel(std::string l) {
  this->level = l;
}

std::string Computer::getLevel() {
  return this->level;
}
