#include "king.h"
#include <iostream>

King::King(std::string s, bool colour, int row, int col): Piece{s, colour, row, col}, first{1} {}


King::~King() {}

bool King::legalMove(bool player, int row, int col) {
  int hdist = col - c;
  int vdist = row - r;
  if (player == colour) {
    if ((hdist == 1 || hdist == -1 || hdist == 0) && (vdist == 1 || vdist == -1 || vdist == 0)) {
      return true;
    } else if (((vdist == 0)&&(hdist == 2 || hdist == -2)) ||
      ((hdist == 0)&&(vdist == 2 || vdist == -2)) ||
      ((hdist == -2 || hdist == 2)&&(vdist == 2 || vdist == -2))) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool King::getFirst() {
  return this->first;
}

void King::setFirst(bool first) {
  this->first = first;
}
