#ifndef BISHOP_H
#define BISHOP_H
#include "piece.h"
#include <string>

class Bishop: public Piece {
  //bool check;

 public:
  Bishop(std::string s, bool colour, int row, int col);
  ~Bishop();

  bool legalMove(bool player, int row, int col) override;
};
#endif
