#include "ChessGame.h"

ChessGame::ChessGame(Xwindow &xw):
  theBoard{ChessBoard{}}, gd{std::shared_ptr<GraphicsDisplay>(new GraphicsDisplay{xw})},
  p1{nullptr}, p2{nullptr} {}

ChessGame::~ChessGame() {

}

std::pair<int, int> ChessGame::getLocation(std::string location) {
  char row = location[1];
  char col = location[0];
  int r;
  int c;
  r = 8 - (row - '0');
  c = col - 'a';
  return std::pair<int, int>(r, c);
}

void ChessGame::setPlayer(std::string player1, std::string player2) {
  if (player1 != "human") {

    std::shared_ptr<Player> np1{new Computer{true, player1}};
    std::swap(p1, np1);
    char c = player1[8];
    if (c == '1') {
      this->p1->setLevel("1");
    } else if (c == '2') {
      this->p1->setLevel("2");
    } else if (c == '3') {
      this->p1->setLevel("3");
    } else if (c == '4') {
      this->p1->setLevel("4");
    }
  } else {
    std::shared_ptr<Player> np1{new Computer{true, player1}};
    std::swap(p1, np1);
  }
  if (player2 != "human") {
    std::shared_ptr<Player> np2{new Computer{false, player2}};
    std::swap(p2, np2);
    char c = player2[8];
    if (c == '1') {
      this->p2->setLevel("1");
    } else if (c == '2') {
      this->p2->setLevel("2");
    } else if (c == '3') {
      this->p2->setLevel("3");
    } else if (c == '4') {
      this->p2->setLevel("4");
    }
  } else {
    std::shared_ptr<Player> np2{new Computer{false, player2}};
    std::swap(p2, np2);
  }
}

void ChessGame::startGame() {
  theBoard.init();
  int len = 8;
  p1->getRooks().push_back(std::pair<int,int>(7, 0));
  p1->getRooks().push_back(std::pair<int,int>(7, 7));
  p1->getKnights().push_back(std::pair<int,int>(7, 1));
  p1->getKnights().push_back(std::pair<int,int>(7, 6));
  p1->getBishops().push_back(std::pair<int,int>(7, 2));
  p1->getBishops().push_back(std::pair<int,int>(7, 5));
  p1->getQueen().push_back(std::pair<int,int>(7, 3));
  p1->getKing().push_back(std::pair<int,int>(7, 4));
  // GraphicsDisplay
  gd->setPiece(-1, -1, 7, 1, "R", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 8, "R", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 2, "N", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 7, "N", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 3, "B", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 6, "B", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 4, "Q", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 7, 5, "K", false, std::pair<int, int> (-1, -1));

  gd->setPiece(-1, -1, 0, 1, "r", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 8, "r", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 2, "n", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 7, "n", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 3, "b", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 6, "b", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 4, "q", false, std::pair<int, int> (-1, -1));
  gd->setPiece(-1, -1, 0, 5, "k", false, std::pair<int, int> (-1, -1));
  for (int i = 0; i < len; i++) {
    p1->getPawns().push_back(std::pair<int,int>(6, i));
    int col = i + 1;
    gd->setPiece(-1, -1, 6, col, "P", false, std::pair<int, int> (-1, -1));
    gd->setPiece(-1, -1, 1, col, "p", false, std::pair<int, int> (-1, -1));
  }
  p2->getRooks().push_back(std::pair<int,int>(0, 1));
  p2->getRooks().push_back(std::pair<int,int>(0, 7));
  p2->getKnights().push_back(std::pair<int,int>(0, 1));
  p2->getKnights().push_back(std::pair<int,int>(0, 6));
  p2->getBishops().push_back(std::pair<int,int>(0, 2));
  p2->getBishops().push_back(std::pair<int,int>(0, 5));
  p2->getQueen().push_back(std::pair<int,int>(0, 3));
  p2->getKing().push_back(std::pair<int,int>(0, 4));
  for (int i = 0; i < len; i++) {
    p2->getPawns().push_back(std::pair<int,int>(1, i));
  }
}

void ChessGame::endGame(Xwindow &xw) {
  theBoard.clearBoard();
}

void ChessGame::add(bool player, std::string type, int row, int col) {
  std::shared_ptr<Player> p = player ? p1: p2;
  std::pair<int, int> k = std::pair<int, int>(row, col);
  if (type == "P" || type == "p") {
    p->getPawns().push_back(k);
  } else if (type == "B" || type == "b") {
    p->getBishops().push_back(k);
  } else if (type == "N" || type == "n") {
    p->getKnights().push_back(k);
  } else if (type == "R" || type == "r") {
    p->getRooks().push_back(k);
  } else if (type == "Q" || type == "q") {
    p->getQueen().push_back(k);
  } else if (type == "K" || type == "k") {
    p->getKing().push_back(k);
  }
  p = nullptr;
}

// used for updatePlayer
void ChessGame::remove(bool player, std::string type, int r, int c) {
  std::shared_ptr<Player> p = player ? p1: p2;
  int len = 0;
  if (type == "P" || type == "p") {
    len = p->getPawns().size();
    for (int i = 0; i < len; i++) {
      if (p->getPawns()[i].first == r && p->getPawns()[i].second == c){
        p->getPawns().erase(p->getPawns().begin() + i);
      }
    }
  } else if (type == "B" || type == "b") {
    len = p->getBishops().size();
    for (int i = 0; i < len; i++) {
      if (p->getBishops()[i].first == r && p->getBishops()[i].second == c){
        p->getBishops().erase(p->getBishops().begin() + i);
      }
    }
  } else if (type == "N" || type == "n") {
    len = p->getKnights().size();
    for (int i = 0; i < len; i++) {
      if (p->getKnights()[i].first == r && p->getKnights()[i].second == c){
        p->getKnights().erase(p->getKnights().begin() + i);
      }
    }
  } else if (type == "R" || type == "r") {
    len = p->getRooks().size();
    for (int i = 0; i < len; i++) {
      if (p->getRooks()[i].first == r && p->getRooks()[i].second == c){
        p->getRooks().erase(p->getRooks().begin() + i);
      }
    }
  } else if (type == "Q" || type == "q") {
    len = p->getQueen().size();
    for (int i = 0; i < len; i++) {
      if (p->getQueen()[i].first == r && p->getQueen()[i].second == c){
        p->getQueen().erase(p->getQueen().begin() + i);
      }
    }
  } else if (type == "K" || type == "k") {
    len = p->getKing().size();
    for (int i = 0; i < len; i++) {
      if (p->getKing()[i].first == r && p->getKing()[i].second == c){
        p->getKing().erase(p->getKing().begin() + i);
      }
    }
  }
  p = nullptr;
} //

void ChessGame::addPiece() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if(theBoard.getBoard()[i][j].getPiece() != nullptr) {
        bool colour = theBoard.getBoard()[i][j].getPiece()->colour;
        std::string type = theBoard.getBoard()[i][j].getPiece()->type;
        this->add(colour, type, i, j);
      }
    }
  }
}

void ChessGame::updatePlayer(bool player, int r, int c, int row, int col, std::string t1, std::string t2) {
  bool opponent = !player;
  if (t2 != "") {
    this->remove(player,t1, r, c); // moves my previous  piece
    this->remove(opponent, t2, row, col); // moves opponent's piece at my destination
    this->add(player, t1, row, col);
  } else {
    if (t1 == "P" || t1 == "p") {
      int hdist = col - c;
      if (hdist == 1) {
        if (opponent == true) {
          this->remove(opponent, "P", r, c + 1);
        } else {
          this->remove(opponent, "p", r, c + 1);
        }
      } else if (hdist == -1) {
        if (opponent == true) {
          this->remove(opponent, "P", r, c - 1);
        } else {
          this->remove(opponent, "p", r, c - 1);
        }
      }
    }
    this->remove(player, t1, r, c);
    this->add(player, t1, row, col);
  }
}

bool ChessGame::setUp(std::string command, std::string coordinate, std::string t) {
  std::pair<int, int> c = getLocation(coordinate);
  bool result = true;
  bool colour = true;
  if(t != "") {
    char type = t[0];
    if (type >= 'a' && type <= 'z') {
      colour = false;
    }
  }
  if (command == "+") {
    theBoard.addPiece(c.first, c.second, t, colour);
    int col = c.second + 1;
    gd->setPiece(-1, -1, c.first, col, t, false, std::pair<int, int>(-1, -1));
  } else if (command == "-") {
    theBoard.removePiece(c.first, c.second);
    int col = c.second + 1;
    gd->setPiece(c.first, col, -1, -1, t, false, std::pair<int, int>(-1, -1));
  } else if (command == "done") {
    result = theBoard.checkBoard();
  }
  return result;
}

bool ChessGame::staleMate() {
  return theBoard.staleMate();
}

bool ChessGame::checkMate(bool player) {
  return theBoard.checkMate(player);
}

bool ChessGame::Promotion(bool player, int r, int c, int row, std::string t) {
  std::string type = theBoard.getBoard()[r][c].getPiece()->type;
  if (t == "K" || t == "k" || t == "P" || t == "p") {
    return false;
  }
  if (type != "P" && type != "p") return false;
  if (row != 0 && row != 7) return false;
  return true;
}

bool ChessGame::move(bool player, int r, int c, int row, int col, std::string promt) {

  if (r < 0 || r > 7 || c < 0 || c > 7 || row < 0 || row > 7 || col < 0 || col > 7) {
    return false;
  }
  if (theBoard.getBoard()[r][c].getPiece() == nullptr || (row == r && col == c)) {
    return false;
  }
  if (theBoard.getBoard()[r][c].getPiece()->colour != player) {
    return false;
  }
  if (promt != "") {
    if (this->Promotion(player, r, c, row, promt) == false) {
      return false;
    }
  }
  std::string t1 = theBoard.getBoard()[r][c].getPiece()->type;
  std::string t2 = "";
  if (theBoard.getBoard()[row][col].getPiece() != nullptr) {
    t2 = theBoard.getBoard()[row][col].getPiece()->type;
  }
  bool result = theBoard.move(player, r, c, row, col);
  if (result == true) {
    bool check = theBoard.check(player, row, col, t1);
    bool opponent = !player;
    if (check ==  true) {
      if (player == 1) {
        std::cout << "Black is in check" << std::endl;
      } else {
        std::cout << "White is in check" << std::endl;
      }
    }
    this->updatePlayer(player, r, c, row, col, t1, t2);
    if (p1->getColour() == opponent) {
      int len = p1->getPawns().size();
      for (int i = 0; i < len; i++) {
        std::pair<int, int> pawn = p1->getPawns()[i];
        theBoard.getBoard()[pawn.first][pawn.second].getPiece()->setPassant(0);
      }
    } else {
      int len = p2->getPawns().size();
      for (int i = 0; i < len; i++) {
        std::pair<int, int> pawn = p2->getPawns()[i];
        theBoard.getBoard()[pawn.first][pawn.second].getPiece()->setPassant(0);
      }
    }
    if (promt != "") {
      theBoard.getBoard()[row][col].clearPiece();
      theBoard.getBoard()[row][col].setPiece(promt, player);
    }
    updateBoard(r, c, row, col, t2, player);
  }
  return result;
}


// computerMove
void ChessGame::computerMove(bool player) {
  std::shared_ptr<Player> p = player ? p1: p2;
  std::string level = p->getLevel();
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> range = theBoard.computerMove(player, level);
  int size = range.size();
  int times = 64;
  while (times >= 0) {
    srand (clock());
    int i = rand() % size;
    int count = 0;
    for (auto it : range) {
      int rangeSize = it.second.size();
      if (count == i && rangeSize >= 0) {
        srand (clock());
        int j = rand() % rangeSize;
        int r = it.first.first;
        int c = it.first.second;
        int row = it.second[j].first;
        int col = it.second[j].second;
        if (this->move(player, r, c, row, col, "") == true) {
          return;
        } else {
          it.second.erase(it.second.begin() + j);
          continue;
        }
      }
      if (rangeSize <= 0) {
        break;
      }
      ++count;
    }
    --times;
  }
  p = nullptr;
}

// update the GraphicsDisplay of the board
void ChessGame::updateBoard(int r, int c, int row, int col, std::string t2, bool player) {
  int hdist = col - c;
  int vdist = row - r;
  bool passant = false;
  std::string type = theBoard.getBoard()[row][col].getPiece()->type;
  std::pair<int, int> rook = std::pair<int, int>(-1, -1);
  if (t2 == "") {
    if (type == "P" || type == "p") {
      if (hdist != 0) {
        passant = true;
      }
    }
    if (type == "K" || type == "k") {
      if (hdist == 2 || hdist == -2 || vdist == 2 || vdist == -2) {
        rook = theBoard.findRook(player, row, col, hdist, vdist);
      }
    }
  }
  int nc = c + 1;
  int ncol = col + 1;
  gd->setPiece(r, nc, row, ncol, type, passant, rook);
}

std::ostream &operator<<(std::ostream &out, ChessGame &g) {
  out << g.theBoard;
  out << *g.gd;
  return out;
}
