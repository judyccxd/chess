#ifndef CHESSG_H
#define ChessGame_H
#include <iostream>
#include <string>
#include <utility>
#include <cmath>
#include <memory>
#include "ChessBoard.h"
#include "GraphicsDisplay.h"
#include "player.h"
#include "computer.h"
#include "human.h"


class ChessGame {
  ChessBoard theBoard;
  std::shared_ptr<GraphicsDisplay> gd;
  std::shared_ptr<Player> p1;
  std::shared_ptr<Player> p2;

 public:
  ChessGame(Xwindow &xw);
  ~ChessGame();

  void startGame();
  void setPlayer(std::string player1, std::string player2);
  bool move(bool player, int r, int c, int row, int col, std::string promt);
  bool Promotion(bool player, int r, int c, int row, std::string t);
  void computerMove(bool player);
  void remove(bool player, std::string type, int r, int c);
  void updatePlayer(bool player, int r, int c, int row, int col, std::string t1, std::string t2);
  bool staleMate();

  bool checkMate(bool player);
  bool setUp(std::string command, std::string coordinate, std::string t);
  void add(bool player, std::string type, int row, int col);
  void addPiece();
  void updateOb(int row, int col);
  void updateBoard(int r, int c, int row, int col, std::string t2, bool player);
  std::vector<int> updatePiece(bool player);
  std::pair<int, int> getLocation(std::string location);

  void endGame(Xwindow &xw);

  friend std::ostream &operator<<(std::ostream &out, ChessGame &g);
};



#endif
