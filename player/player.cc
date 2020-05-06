#include "player.h"

Player::Player(bool colour, std::string player): player{player}, colour{colour}, queen{}, king{}
 , knights{}, bishops{}, rooks{}, pawns{} {}

Player::~Player() {}

void Player::setLevel(std::string l) {
  return;
}

std::string Player::getLevel() {
  return "";
}

std::vector<std::pair<int, int>> &Player::getRooks() {
  return rooks;
}
std::vector<std::pair<int, int>> &Player::getBishops() {
  return bishops;
}
std::vector<std::pair<int, int>>&Player::getKnights() {
  return knights;
}
std::vector<std::pair<int, int>> &Player::getPawns() {
  return pawns;
}
std::vector<std::pair<int, int>> &Player::getKing() {
  return king;
}

std::vector<std::pair<int, int>> &Player::getQueen() {
  return queen;
}

std::vector<std::pair<int, int>> Player::getPiece() {
  std::vector<std::pair<int, int>> p;
  p.insert(std::end(p), std::begin(queen), std::end(queen));
  p.insert(std::end(p), std::begin(knights), std::end(knights));
  p.insert(std::end(p), std::begin(pawns), std::end(pawns));
  p.insert(std::end(p), std::begin(king), std::end(king));
  p.insert(std::end(p), std::begin(bishops), std::end(bishops));
  p.insert(std::end(p), std::begin(rooks), std::end(rooks));
  return p;
}

bool Player::getColour() {
  return colour;
}
