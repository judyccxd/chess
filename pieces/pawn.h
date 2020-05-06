#ifndef PAWN_H
#define PAWN_H
#include "piece.h"
#include <iostream>
#include <string>

class Pawn: public Piece {
  bool first;
  bool passant;

 public:
  Pawn(std::string s, bool colour, int row, int col);
  ~Pawn();

  bool legalMove(bool player, int row, int col) override;
  bool getPassant() override;
  bool getFirst() override;
  void setPassant(bool passant) override;
  void setFirst(bool first) override;
};
#endif
