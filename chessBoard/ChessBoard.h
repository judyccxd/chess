#ifndef CHESSB_H
#define CHESSB_H
#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include "cell.h"
#include <string>

class Observer;

class ChessBoard {
  std::vector<std::vector<Cell>> board;  // The actual
  int size;

 public:
  ChessBoard();
  ~ChessBoard();

  void clearBoard();
  std::vector<std::vector<Cell>> &getBoard();

  void init(); // Sets up an n x n grid.  Clears old grid, if necessary.
  void addPiece(int r, int c, std::string type, bool colour);
  void removePiece(int r, int c);
  void setUpOb();
  void addOb(int r, int c);
  void removeOb(int r, int c);
  bool checkBoard();

  bool move(bool player, int r, int c, int row, int col);

  bool moveRight(int r, int c, int col);
  bool moveLeft(int r, int c, int col);
  bool moveUp(int r, int c, int col);
  bool moveDown(int r, int c, int col);
  bool movePiece(bool player, int r, int c, int row, int col);

  bool moveKnight(bool player, int r, int c, int row, int col);
  bool movePawn(bool player, int r, int c, int row, int col);

  bool kingRight(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingLeft(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingDown(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingUp(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingRightDown(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingRightUp(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingLeftUp(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool kingLeftDown(int r, int c, int row, int col, std::pair<int, int> k, bool player);
  bool moveKing(bool player, int r, int c, int row, int col);

  bool legalMove(int r, int c, int row, int col, std::string type, bool player);
  bool check(bool player, int row, int col, std::string type);
  bool incheck(bool player, int row, int col);
  bool checkMate(bool player);
  bool saveKing(bool player, int row, int col);
  bool staleMate();
  std::pair<int, int> findKing(bool colour);
  std::pair<int, int> findRook(bool colour, int row, int col, int h, int v);

  std::vector<std::pair<int, int>> oneLegalMove(bool player, int r,int c, std::string type);
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> computerMove(bool player, std::string level);
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> computerL1(bool player);
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> computerL2(bool player);
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> computerL3(bool player);

  std::vector<std::pair<int, int>> legal(int r, int c, std::string type, bool player);
  std::vector<std::pair<int, int>> legalN(int r, int c, std::string type, bool player);
  std::vector<std::pair<int, int>> legalK(int r, int c, std::string type, bool player);
  std::vector<std::pair<int, int>> legalP(int r, int c, std::string type, bool player);
  std::vector<std::pair<int, int>> legalRange(int r, int c, std::string type, bool player);


  friend std::ostream &operator<<(std::ostream &out, ChessBoard &b);
};

#endif
