#ifndef ROOK_H
#define ROOK_H
#include "piece.h"
#include <string>

class Rook: public Piece {
  bool first;

 public:
  Rook(std::string s, bool colour, int row, int col);
  ~Rook();

  bool legalMove(bool player, int row, int col) override;
  bool getFirst() override;
  void setFirst(bool first) override;
};
#endif
