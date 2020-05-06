#include "bishop.h"

Bishop::Bishop(std::string s, bool colour, int row, int col): Piece{s, colour, row, col} {}

//, check{false} {}

Bishop::~Bishop() {}

bool Bishop::legalMove(bool player, int row, int col) {
  if (player == colour) {
    // std::cout << "Pawn r " << r << " c " << c << std::endl;
    // std::cout << "Pawn row " << row << " col " << col << std::endl;
    if (r != row && c != col) {
      if ((row - r == c - col) || (row - r == col - c)) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}
