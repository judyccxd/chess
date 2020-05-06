#include "rook.h"

Rook::Rook(std::string s, bool colour, int row, int col): Piece{s, colour, row, col}, first{1} {}

//, check{false} {}

Rook::~Rook() {}

bool Rook::legalMove(bool player, int row, int col) {
  if (player == colour) {
    // std::cout << "Pawn r " << r << " c " << c << std::endl;
    // std::cout << "Pawn row " << row << " col " << col << std::endl;
    if ((r == row && c != col) || (r != row && c == col)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool Rook::getFirst() {
  return this->first;
}

void Rook::setFirst(bool first) {
  this->first = first;
}
