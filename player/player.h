#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <vector>
#include "piece.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "rook.h"


class Player {
  std::string player;
  bool colour;

  std::vector<std::pair<int, int>> queen;
  std::vector<std::pair<int, int>> king;
  std::vector<std::pair<int, int>> knights;
  std::vector<std::pair<int, int>> bishops;
  std::vector<std::pair<int, int>> rooks;
  std::vector<std::pair<int, int>> pawns;

  public:
  Player(bool colour, std::string player);
  virtual ~Player();
  std::vector<std::pair<int, int>> &getRooks();
  std::vector<std::pair<int, int>> &getBishops();
  std::vector<std::pair<int, int>> &getKnights();
  std::vector<std::pair<int, int>> &getPawns();
  std::vector<std::pair<int, int>> &getKing();
  std::vector<std::pair<int, int>> &getQueen();
  std::vector<std::pair<int, int>> getPiece();
  virtual void setLevel(std::string l);
  virtual std::string getLevel();
  bool getColour();
};

#endif
