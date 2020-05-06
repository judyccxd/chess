#include "pawn.h"

Pawn::Pawn(std::string s, bool colour, int row, int col): Piece{s, colour, row, col},
first{1}, passant{0} {}

//, check{false} {}

Pawn::~Pawn() {}


bool Pawn::legalMove(bool player, int row, int col) {
  if (player == colour) {
    // std::cout << "Pawn r " << r << " c " << c << std::endl;
    // std::cout << "Pawn row " << row << " col " << col << std::endl;
    int vdist;
    if (player == 1) {
      vdist = r - row;
    } else {
      vdist = row - r;
    }
    int hdist = col - c;
    if (first == true) { // first step
      if (((vdist == 1) || (vdist == 2)) && col == c) { //first step move 1 or 2 forward
        if (vdist == 2) {
          this->passant = 1;
        }
        return true;
      } else if ((vdist == 1) && ((hdist == 1) || (hdist == -1))) { //otherwise captures on forward square
        return true;
      }
    } else {
      if ((vdist == 1) && (col == c || (hdist == 1) || (hdist == -1))) {
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

bool Pawn::getPassant() {
  return this->passant;
}

bool Pawn::getFirst() {
  return this->first;
}

void Pawn::setPassant(bool passant) {
  this->passant = passant;
}

void Pawn::setFirst(bool first) {
  this->first = first;
}
