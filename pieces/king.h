#ifndef King_H
#define King_H
#include "piece.h"
#include <string>

class King: public Piece {
  bool first;

 public:
  King(std::string s, bool colour, int row, int col);
  ~King();

  bool legalMove(bool player, int row, int col) override;
  bool getFirst() override;
  void setFirst(bool first) override;
};
#endif
