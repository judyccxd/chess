#ifndef Knight_H
#define Knight_H
#include "piece.h"
#include <string>

class Knight: public Piece {
  //bool check;

 public:
  Knight(std::string s, bool colour, int row, int col);
  ~Knight();

  bool legalMove(bool player, int row, int col) override;
};
#endif
