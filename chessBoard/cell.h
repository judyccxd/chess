#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <memory>
#include "piece.h"

class Cell {
  int r, c;
  bool colour;
  std::shared_ptr<Piece> p;

 public:
  Cell();
  ~Cell();

  void setCell(int r,int c,bool colour);
  std::shared_ptr<Piece> getPiece();
  bool getColour();
  void clearPiece();

  //bool movePiece(bool player, int row, int col);
  void setPiece(std::string s, bool colour);    // Place a piece of given colour here.
  void attackPiece(std::string s, bool colour);
  //void attackPiece(Piece p);
  // void notify(bool player, int r, int c, std::string type, std::vector<std::pair<int, int>> &v) override;// My neighbours will call this
                                                // when they've changed state
  friend std::ostream &operator<<(std::ostream &out, const Cell &c);
};
#endif
