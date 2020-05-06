#ifndef QUEEN_H
#define QUEEN_H
#include "piece.h"
#include <string>

class Queen: public Piece {
  //bool check;

 public:
  Queen(std::string s, bool colour, int row, int col);
  ~Queen();

  bool legalMove(bool player, int row, int col) override;
};
#endif
