#include "ChessBoard.h"

ChessBoard::ChessBoard(): board{}, size{8} {
  for(int i = 0; i < size; ++i) {
    std::vector<Cell> c;
    board.push_back(c);
    for(int j = 0; j < size; ++j) {
      if (i % 2 == 0) {
        if (j % 2 == 0) {
          board[i].push_back(Cell{});
          board[i][j].setCell(i, j, 1);
        } else {
          board[i].push_back(Cell{});
          board[i][j].setCell(i, j, 0);
        }
      } else {
        if (j % 2 == 0) {
          board[i].push_back(Cell{});
          board[i][j].setCell(i, j, 0);
        } else {
          board[i].push_back(Cell{});
          board[i][j].setCell(i, j, 1);
        }
      }
    }
  }
}

ChessBoard::~ChessBoard() {
}

void ChessBoard::clearBoard() {
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if(board[i][j].getPiece() != nullptr) {
        board[i][j].clearPiece();
      }
    }
  }
}

void ChessBoard::addPiece(int r, int c, std::string type, bool colour) {
  if (board[r][c].getPiece() != nullptr) {
    board[r][c].attackPiece(type, colour);
  } else {
    board[r][c].setPiece(type, colour);
  }
}

void ChessBoard::removePiece(int r, int c) {
  if (board[r][c].getPiece() != nullptr) {
    board[r][c].clearPiece();
  }
}

bool ChessBoard::checkBoard() {
  int wKing = 0;
  int bKing = 0;
  bool bIncheck = 0;
  bool wIncheck = 0;
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if (board[i][j].getPiece() != nullptr) {
        std::string type = board[i][j].getPiece()->type;
        if (type == "K") {
          ++wKing;
          wIncheck = incheck(true, i, j);
        } else if (type == "k") {
          ++bKing;
          bIncheck = incheck(false, i, j);
        }
        if (wIncheck == true || bIncheck == true){
          std::cout << "King in Check" << std::endl;
          return false;
        }
        if (i == 0 || i == 7) {
          if (type == "P" || type == "p") {
            std::cout << "Pawn in end or first row" << std::endl;
            return false;
          }
        }
      }
    }
  }
  if (wKing != 1 || bKing != 1) {
    std::cout << "Wrong Number Of Kings" << std::endl;
    return false;
  }
  return true;
}

std::vector<std::vector<Cell>> &ChessBoard::getBoard() {
  return board;
}

void ChessBoard::init() {
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if ((i >= 0 && i <=1) || (i >= 6 && i <=7)) {
        if (j == 0 || j == 7) { // set  rooks
          if (i == 0) board[i][j].setPiece("r", 0);
          if (i == 1) board[i][j].setPiece("p", 0);
          if (i == 6) board[i][j].setPiece("P", 1);
          if (i == 7) board[i][j].setPiece("R", 1);
        } else if (j == 1 || j == 6) { // set  knights
          if (i == 0) board[i][j].setPiece("n", 0);
          if (i == 1) board[i][j].setPiece("p", 0);
          if (i == 6) board[i][j].setPiece("P", 1);
          if (i == 7) board[i][j].setPiece("N", 1);
        }  else if (j == 2 || j == 5) { // set  bishops
          if (i == 0) board[i][j].setPiece("b", 0);
          if (i == 1) board[i][j].setPiece("p", 0);
          if (i == 6) board[i][j].setPiece("P", 1);
          if (i == 7) board[i][j].setPiece("B", 1);
        } else if (j == 3) { // set queens
          if (i == 0) board[i][j].setPiece("q", 0);
          if (i == 1) board[i][j].setPiece("p", 0);
          if (i == 6) board[i][j].setPiece("P", 1);
          if (i == 7) board[i][j].setPiece("Q", 1);
        } else if (j == 4) {  // set kings
          if (i == 0) board[i][j].setPiece("k", 0);
          if (i == 1) board[i][j].setPiece("p", 0);
          if (i == 6) board[i][j].setPiece("P", 1);
          if (i == 7) board[i][j].setPiece("K", 1);
        }
      }
    }
  }
}

std::pair<int, int> ChessBoard::findKing(bool colour) {
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if (board[i][j].getPiece() != nullptr) {
        std::string type = board[i][j].getPiece()->type;
        bool color = board[i][j].getPiece()->colour;
        if ((type == "K" || type == "k") && (color == colour)) {
          return  std::pair<int, int>(i, j);
        }
      }
    }
  }
  return  std::pair<int, int>(-1, -1);
}

bool ChessBoard::staleMate() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j].getPiece() != nullptr) {
        std::string type = board[i][j].getPiece()->type;
        bool player = board[i][j].getPiece()->colour;
        std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> range = computerL1(player);
        if (range.size() > 0) { // there is piece in the board still has legal move
          return false;
        }
      }
    }
  }
  return true;
}

bool ChessBoard::legalMove(int r, int c, int row, int col, std::string type, bool player) {
  int hdist = col - c;
  int vdist = row - r;
  if (type == "Q" || type == "q" || type == "R" || type == "r" || type == "B" || type == "b") {
    return movePiece(player, r, c, row, col);
  } else if (type == "N" || type == "n") {
    return moveKnight(player, r, c, row, col);
  } else if (type == "P" || type == "p") {
    if (hdist == 1 || hdist == -1) {
      if ((vdist == -1 && player == true)||(vdist == 1 && player == false)) {
        return true;
      }
    }
  }
  return false;
}

bool ChessBoard::check(bool player, int row, int col, std::string type) {
  bool opponent = !player;
  std::pair<int, int> k = findKing(opponent);
  bool check = false;
  if (k.first >= 0 && k.second >= 0) {
    check = legalMove(row, col, k.first, k.second, type, player);
  }
  return check;
}

bool ChessBoard::incheck(bool player, int row, int col) {
  bool opponent = !player;
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if (board[i][j].getPiece() != nullptr) {
        bool colour = board[i][j].getPiece()->colour;
        if (colour == opponent) {
          std::string type = board[i][j].getPiece()->type;
          bool incheck = legalMove(i, j, row, col, type, opponent);
          if (incheck == true){
            return true; //destination will be in check
          }
        }
      }
    }
  }
  return false;
}

bool ChessBoard::saveKing(bool player, int row, int col) {
  bool save = false;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) { // check if all my pieces can capture opponet's piece around my king
      std::string type = board[i][j].getPiece()->type;
      save = legalMove(i, j, row, col, type, player); // if one of my piece at (i, j) can capture opponet's piece at (row, col)
      if (save == true) {
        return true;
      }
    }
  }
  return false;
}

bool ChessBoard::checkMate(bool player) {
  bool opponent = !player;
  bool checkMate = false;
  std::pair<int, int> k = findKing(opponent);
  int r = k.first;
  int c = k.second;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int row = k.first + i;
      int col = k.second + j;
      if ((row != r || col != c) && row >= 0 && row <= 7 && col >= 0 && col <= 7) {
        checkMate = incheck(opponent, row, col);
        if (checkMate == false) { // opponent's king can escape in one move
          return false;
        } else { // if the cell around the opponet's king can be reached by my pieces
          if (saveKing(opponent, row, col) == true) { // see if any of opponent's pieces can save the King
            return false;
          }
        }
      }
    }
  }
  return true;
}



bool ChessBoard::move(bool player, int r, int c, int row, int col) {
  if (board[r][c].getPiece() == nullptr) {
    return false;
  }
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  if (type == "Q" || type == "q" || type == "R" || type == "r" || type == "B" || type == "b") {
    if (movePiece(player, r, c, row, col) ==  true) {
      if (board[row][col].getPiece() != nullptr
      && board[row][col].getPiece()->type != "k" && board[row][col].getPiece()->type != "K") {
        if (colour == board[row][col].getPiece()->colour) {
          return false;
        }
        board[row][col].attackPiece(type, colour);
        board[r][c].clearPiece();
        if (type == "R" || type == "r") {
          board[row][col].getPiece()->setFirst(0);
        }
        return true;
      } else if (board[row][col].getPiece() == nullptr) {
        board[row][col].setPiece(type, colour);
        board[r][c].clearPiece();
        if (type == "R" || type == "r") {
          board[row][col].getPiece()->setFirst(0);
        }
        return true;
      }
    }
    return false;
  } else if (type == "N" || type == "n") {
    if(moveKnight(player, r, c, row, col)) {
      if (board[row][col].getPiece() != nullptr
          && board[row][col].getPiece()->type != "k" && board[row][col].getPiece()->type != "K") {
        if (colour == board[row][col].getPiece()->colour) {
          return false;
        }
        board[row][col].attackPiece(type, colour);
        board[r][c].clearPiece();
        return true;
      } else if (board[row][col].getPiece() == nullptr) {
        board[row][col].setPiece(type, colour);
        board[r][c].clearPiece();
        return true;
      }
    }
    return false;
  } else if (type == "P" || type == "p"){
    return movePawn(player, r, c, row, col);
  } else {
    return moveKing(player, r, c, row, col);
  }
}

bool ChessBoard::moveRight(int r, int c, int col) {
  for (int i = c + 1; i < col; i++) {
    if(board[r][i].getPiece() != nullptr) {
      return false;
    }
  }
  return true;
}

bool ChessBoard::moveLeft(int r, int c, int col) {
  for (int i = c - 1; i > col; i++) {
    if(board[r][i].getPiece() != nullptr) {
      return false;
    }
  }
  return true;
}

bool ChessBoard::moveUp(int r, int c, int row) {
  for (int i = r - 1; i > row ; i--) {
    if (board[i][c].getPiece() != nullptr) {
       return false;
    }
  }
  return true;
}

bool ChessBoard::moveDown(int r, int c, int row) {
  for (int i = r + 1; i < row ; i++) {
    if(board[i][c].getPiece() != nullptr) {
       return false;
     }
  }
  return true;
}

// this method moves three type piece, queen, bishop, rook
bool ChessBoard::movePiece(bool player, int r, int c, int row, int col) {
  if (board[r][c].getPiece()->legalMove(player, row, col)) {
    std::string type = board[r][c].getPiece()->type;
    int hdist = col - c;
    int vdist = row - r;
    if (row == r && (type == "Q" || type == "q" || type == "R" || type == "r")) {
      if (hdist > 0) { // moves right
        return this->moveRight(r, c, col);
      } else { // moves left
        return this->moveLeft(r, c, col);
      }
    } else if (col == c && (type == "Q" || type == "q" || type == "R" || type == "r")) {
      if (vdist > 0) { // moves down
        return this->moveDown(r, c, row);
      } else { // moves up
        return this->moveUp(r, c, row);
      }
    } else {
      if (type == "Q" || type == "q" || type == "B" || type == "b") {
        if (vdist < 0 && hdist > 0) { // up right
          for (int i = r - 1, j = c + 1; i > row && j < col; i--, j++) {
            if(board[i][j].getPiece() != nullptr) return false;
          }
          return true;
        } else if (vdist < 0 && hdist < 0) { //up left
          for (int i = r - 1, j = c - 1; i > row && j > col; i--, j--) {
            if(board[i][j].getPiece() != nullptr) return false;
          }
          return true;
        } else if (vdist > 0 && hdist > 0) {
          for (int i = r + 1, j = c + 1; i < row && j < col; i++, j++) {
            if(board[i][j].getPiece() != nullptr) return false;
          }
          return true;
        } else {
          for (int i = r + 1, j = c - 1; i < row && j > col; i++, j--) {
            if(board[i][j].getPiece() != nullptr) {
              return false;
            }
          }
          return true;
        }
      }
    }
  }
  return false;
}

bool ChessBoard::moveKnight(bool player, int r, int c, int row, int col) {
  return board[r][c].getPiece()->legalMove(player, row, col);
}

bool ChessBoard::movePawn(bool player, int r, int c, int row, int col) {
  int hdist = col - c;
  int vdist;
  if (player == 1) {
    vdist = r - row;
  } else {
    vdist = row - r;
  }
  if (board[r][c].getPiece()->legalMove(player, row, col)) {
    std::string type = board[r][c].getPiece()->type;
    bool colour = board[r][c].getPiece()->colour;
    if ((hdist == 1 || hdist == -1) && vdist == 1) { //capture
      if (board[row][col].getPiece() != nullptr
      && colour != board[row][col].getPiece()->colour) { // normal capture
        if (board[row][col].getPiece()->type != "k" && board[row][col].getPiece()->type != "K") {
          board[row][col].attackPiece(type, colour);
          board[r][c].clearPiece();
        }
        return true;
      } else if (board[r][col].getPiece() != nullptr
        && board[row][col].getPiece() == nullptr
        && colour != board[r][col].getPiece()->colour) { // en passant
        int passant = board[r][col].getPiece()->getPassant();
        if (passant == 1) {
          board[row][col].setPiece(type, colour);
          board[r][c].clearPiece();
          board[r][col].clearPiece();
          return true;
        }
      }
    }
    // move without capture
    int first = board[r][c].getPiece()->getFirst();
    if (first == true) { // first move
      if (hdist == 0) {
        if ((vdist == 2 || vdist ==  1) && board[row][col].getPiece() == nullptr) {
          // move 1 or 2 step forward and no piece at destination
          board[row][col].setPiece(type, colour);
          board[r][c].clearPiece();
          board[row][col].getPiece()->setFirst(0); // first move has been done
          if (vdist == 2) {
            board[row][col].getPiece()->setPassant(1); // pawn is now a passant
          }
          return true;
        }
      }
    } else {
      if (hdist == 0) {
        if (vdist == 1 && board[row][col].getPiece() == nullptr) {
          // move 1 step forward and no piece at destination
          board[row][col].setPiece(type, colour);
          board[r][c].clearPiece();
          return true;
        }
      }
    }
  }
  return false;
}

std::pair<int, int> ChessBoard::findRook(bool colour, int row, int col, int h, int v) {
  for(int i = 0; i < size; ++i) {
    for(int j = 0; j < size; ++j) {
      if (board[i][j].getPiece() != nullptr) {
        std::string type = board[i][j].getPiece()->type;
        bool color = board[i][j].getPiece()->colour;
        if ((type == "R" || type == "r") && (color == colour)) {
          int hdist = j - col;
          int vdist = i - row;
          if (h == 0) {
            if ((v > 0 && vdist > 0) || (v < 0 && vdist < 0)) {
              return  std::pair<int, int>(i, j);
            }
          } else if (v == 0) {
            if ((h > 0 && hdist > 0) || (h < 0 && hdist < 0)) {
              return  std::pair<int, int>(i, j);
            }
          } else {
            if (((v > 0 && vdist > 0) || (v < 0 && vdist < 0))
          && ((h > 0 && hdist > 0) || (h < 0 && hdist < 0))) {
              return  std::pair<int, int>(i, j);
            }
          }
        }
      }
    }
  }
  return  std::pair<int, int>(-1, -1);
}

bool ChessBoard::kingRight(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rcol = k.second;
  for (int i = c; i < rcol; i++) {
    if (i <= col && i > c) {
      if(incheck(player, r, i) == true || board[r][i].getPiece() != nullptr) {
        return false;
      }
    }
    if(i!= c && board[r][i].getPiece() != nullptr) {
      return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row][col - 1].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingLeft(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rcol = k.second;
  for (int i = c; i > rcol; i--) {
    if (i >= col && i < c) {
      if(incheck(player, r, i) == true || board[r][i].getPiece() != nullptr) {
        return false;
      }
    }
    if (i != c && board[r][i].getPiece() != nullptr) {
      return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row][col + 1].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingDown(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rrow = k.first;
  for (int i = r; i <= rrow; i++) {
    if (i <= row && i > r) {
      if(incheck(player, i, c) == true || board[i][c].getPiece() != nullptr) {
        return false;
      }
    }
    if(i != r && board[i][c].getPiece() != nullptr) {
        return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row - 1][col].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingUp(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rrow = k.first;
  for (int i = r; i >= rrow; i--) {
    if (i >= row && i < r) {
      if(incheck(player, i, c) == true || board[i][c].getPiece() != nullptr) {
        return false;
      }
    }
    if(i != r && board[i][c].getPiece() != nullptr) {
        return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row + 1][col].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingRightDown(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rrow = k.first;
  int rcol = k.second;
  for (int i = r, j = c; i <= rrow &&  j <= rcol; i++, j++) {
    if (i <= row && j <= col && i > r && j > c) {
      if(incheck(player, i, j) == true || board[i][j].getPiece() != nullptr) {
        return false;
      }
    }
    if(i != r && j != c && board[i][j].getPiece() != nullptr) {
        return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row - 1][col - 1].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingLeftDown(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rrow = k.first;
  int rcol = k.second;
  for (int i = r, j = c; i <= rrow &&  j >= rcol; i++, j--) { // moves left down
    if (i <= row && j >= col && i > r && j < c) {
      if(incheck(player, i, j) == true || board[i][j].getPiece() != nullptr) {
        return false;
      }
    }
    if(i != r && j != c && board[i][j].getPiece() != nullptr) {
        return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row - 1][col + 1].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingRightUp(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rrow = k.first;
  int rcol = k.second;
  for (int i = r, j = c; i >= rrow &&  j <= rcol; i--, j++) { // moves up right
    if (i >= row && j <= col && i < r && j > c) {
      if(incheck(player, i, j) == true || board[i][j].getPiece() != nullptr) {
        return false;
      }
    }
    if(i != r && j != c && board[i][j].getPiece() != nullptr) {
        return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row + 1][col - 1].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::kingLeftUp(int r, int c, int row, int col, std::pair<int, int> k, bool player) {
  std::string type = board[r][c].getPiece()->type;
  bool colour = board[r][c].getPiece()->colour;
  int rrow = k.first;
  int rcol = k.second;
  for (int i = r, j = c; i >= rrow &&  j >= rcol; i--, j--) {
    if (i >= row && j >= col && i < r && j < c) {
      if(incheck(player, i, j) == true || board[i][j].getPiece() != nullptr) {
        return false;
      }
    }
    if(i != r && j != c && board[i][j].getPiece() != nullptr) {
        return false;
    }
  }
  std::string rtype = board[k.first][k.second].getPiece()->type;
  bool rcolour = board[k.first][k.second].getPiece()->colour;
  board[row + 1][col + 1].setPiece(rtype, rcolour);
  board[row][col].setPiece(type, colour);
  board[k.first][k.second].clearPiece();
  board[r][c].clearPiece();
  return true;
}

bool ChessBoard::moveKing(bool player, int r, int c, int row, int col) {
  if (board[r][c].getPiece()->legalMove(player, row, col)) {
    std::string type = board[r][c].getPiece()->type;
    bool colour = board[r][c].getPiece()->colour;
    int hdist = col - c;
    int vdist = row - r;
    if (((vdist == 0)&&(hdist == 2 || hdist == -2)) ||
      ((hdist == 0)&&(vdist == 2 || vdist == -2)) ||
      ((hdist == -2 || hdist == 2)&&(vdist == 2 || vdist == -2))) { // castling
        std::pair<int, int> k = findRook(player, row, col, hdist, vdist);
         if (k.first >= 0) {
          if (board[r][c].getPiece()->getFirst() == true
          && board[k.first][k.second].getPiece()->getFirst() == true) {
            if (vdist == 0 && hdist == 2) { // moves right
              return kingRight(r, c,row, col, k, player);
            } else if (vdist == 0 && hdist == -2) { // moves left
              return kingLeft(r, c,row, col, k, player);
            } else if (hdist == 0 && vdist == 2) { // moves down
              return kingDown(r, c,row, col, k, player);
            } else if (hdist == 0 && vdist == -2) { // moves up
              return kingDown(r, c, row, col, k, player);
            } else if (hdist == 2 && vdist == 2) { // moves right and down
              return kingRightDown(r, c, row, col, k, player);
            } else if (hdist == 2 && vdist == -2) {
              return kingLeftDown(r, c, row, col, k, player);
            } else if (hdist == -2 && vdist == 2) {
              return kingRightUp(r, c, row, col, k, player);
            } else if (hdist == -2 && vdist == -2) {
              return kingLeftUp(r, c, row, col, k, player);
            }
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
    // normal move
    bool incheck = this->incheck(player, row, col);
    if (incheck ==  true) { // illegal move king will be in check
      return false;
    } else { // destination will not make king in check
      if (board[row][col].getPiece() == nullptr) {
        board[row][col].setPiece(type, colour);
        board[r][c].clearPiece();
        if (board[row][col].getPiece()->getFirst() == true) {
          board[row][col].getPiece()->setFirst(0);
        }
        return true;
      } else {
        return false;
      }
    }
  } else {
    return false;
  }
}

// Computer Part

// Used for find all possible coordinate for B Q R can reach
std::vector<std::pair<int, int>> ChessBoard::legal(int r, int c, std::string type, bool player) {
  std::vector<std::pair<int, int>> v;
  if (type == "Q" || type == "q" || type == "R" || type == "r") {
    if (r > 0) { // up
      int i = r - 1;  // starts at the cell up this piece
      while (i >= 0) {  // track along until the boundary of the board
        if (board[i][c].getPiece() != nullptr) { // if along the path there is a piece in one cell
          if (board[i][c].getPiece()->colour != player) { // if the piece belongs to my opponet push to v
            v.push_back(std::pair<int, int>(i, c));
          }
          break; // cannot jump a piece
        }
        v.push_back(std::pair<int, int>(i, c));
        i--;
      }
    }
    if (r < 7) { //down
      int i = r + 1;
      while (i <= 7) {
        if (board[i][c].getPiece() != nullptr) {
          if (board[i][c].getPiece()->colour == player) {
            v.push_back(std::pair<int, int>(i, c));
          }
          break;
        }
        v.push_back(std::pair<int, int>(i, c));
        i++;
      }
    }
    if (c > 0) { //left
      int i = c - 1;
      while (i >= 0) {
        if (board[r][i].getPiece() != nullptr) {
          if (board[r][i].getPiece()->colour == player) {
            v.push_back(std::pair<int, int>(r, i));
          }
          break;
        }
        v.push_back(std::pair<int, int>(r, i));
        i--;
      }
    }
    if (c < 7) { // right
      int i = c + 1;
      while (i <= 7) {
        if (board[r][i].getPiece() != nullptr) {
          if (board[r][i].getPiece()->colour == player) {
            v.push_back(std::pair<int, int>(r, i));
          }
          break;
        }
        v.push_back(std::pair<int, int>(r, i));
        i++;
      }
    }
  }
  if (type == "Q" || type == "q" || type == "B" || type == "b") {
    int index = 4;
    if (type == "B" || type == "b") index = 0;
    if (r > 0 && c > 0) {  // up left
      int i = r - 1;
      int j = c - 1;
      while (i >= 0 && j >= 0) {
        if (board[i][j].getPiece() != nullptr) {
          if (board[i][j].getPiece()->colour != player) {
            v.push_back(std::pair<int, int>(i, j));
          }
          break;
        }
        v.at(index) = std::pair<int, int>(i, j);
        i--;
        j--;
      }
    }
    ++index;
     if (r > 0 && c < 7) {  // up right
      int i = r - 1;
      int j = c + 1;
      while (i >= 0 && j <= 7) {
        if (board[i][j].getPiece() != nullptr) {
          if (board[i][j].getPiece()->colour != player) {
            v.push_back(std::pair<int, int>(i, j));
          }
          break;
        }
        v.at(index) = std::pair<int, int>(i, j);
        i--;
        j++;
      }
    }
    ++index;
     if (r < 7 && c > 0) {  // down left
      int i = r + 1;
      int j = c - 1;
      while (i <= 7 && j >= 0) {
        if (board[i][j].getPiece() != nullptr) {
          if (board[i][j].getPiece()->colour != player) {
            v.push_back(std::pair<int, int>(i, j));
          }
          break;
        }
        v.at(index) = std::pair<int, int>(i, j);
        i++;
        j--;
      }
    }
    ++index;
     if (r < 7 && c < 7) {  // down right
      int i = r + 1;
      int j = c + 1;
      while (i <= 7 && j <= 7) {
        if (board[i][j].getPiece() != nullptr) {
          if (board[i][j].getPiece()->colour != player) {
            v.push_back(std::pair<int, int>(i, j));
          }
          break;
        }
        v.at(index) = std::pair<int, int>(i, j);
        i++;
        j++;
      }
    }
  }
  return v;
}

std::vector<std::pair<int, int>> ChessBoard::legalN(int r, int c, std::string type, bool player) {
  std::vector<std::pair<int, int>> v;
  int r1 = r + 2;
  int r2 = r - 2;
  int r3 = r + 1;
  int r4 = r - 1;
  int c1 = c + 2;
  int c2 = c - 2;
  int c3 = c + 1;
  int c4 = c - 1;
  if (r1 <= 7 && c3 <= 7) {
    v.push_back(std::pair<int, int>(r1, c3));
  }
  if (r1 <= 7 && c4 >= 0) {
    v.push_back(std::pair<int, int>(r1, c4));
  }
  if (r2 >= 0 && c3 <= 7) {
    v.push_back(std::pair<int, int>(r2, c3));
  }
  if (r2 >= 0 && c4 >= 0) {
    v.push_back(std::pair<int, int>(r2, c4));
  }
  if (r3 <= 7 && c1 <= 7) {
    v.push_back(std::pair<int, int>(r3, c1));
  }
  if (r3 <= 7 && c2 >= 0) {
    v.push_back(std::pair<int, int>(r3, c2));
  }
  if (r4 >= 0 && c1 <= 7) {
    v.push_back(std::pair<int, int>(r4, c1));
  }
  if (r4 >= 0 && c2 >= 0) {
    v.push_back(std::pair<int, int>(r4, c2));
  }
  return v;
}

std::vector<std::pair<int, int>> ChessBoard::legalK(int r, int c, std::string type, bool player) {
  std::vector<std::pair<int, int>> v;
  int r1 = r + 1;
  int r2 = r - 1;
  int c1 = c + 1;
  int c2 = c - 1;
  if (r1 <= 7 && c1 <= 7) {
    if (incheck(player, r1, c1) == false) {
      v.push_back(std::pair<int, int>(r1, c1));
    }
  }
  if (r1 <= 7 && c2 >= 0) {
    if (incheck(player, r1, c2) == false) {
      v.push_back(std::pair<int, int>(r1, c2));
    }
  }
  if (r2 >= 0 && c1 <= 7) {
    if (incheck(player, r2, c1) == false) {
      v.push_back(std::pair<int, int>(r2, c1));
    }
  }
  if (r2 >= 0 && c2 >= 0) {
    if (incheck(player, r2, c2) == false) {
      v.push_back(std::pair<int, int>(r2, c2));
    }
  }
  if (r1 <= 7) {
    if (incheck(player, r1, c) == false) {
      v.push_back(std::pair<int, int>(r1, c));
    }
  }
  if (c1 <= 7) {
    if (incheck(player, r, c1) == false) {
      v.push_back(std::pair<int, int>(r, c1));
    }
  }
  if (r2 >= 0) {
    if (incheck(player, r2, c) == false) {
      v.push_back(std::pair<int, int>(r2, c));
    }
  }
  if (c2 >= 0) {
    if (incheck(player, r, c2) == false) {
      v.push_back(std::pair<int, int>(r, c2));
    }
  }
  return v;
}

std::vector<std::pair<int, int>> ChessBoard::legalP(int r, int c, std::string type, bool player) {
  std::vector<std::pair<int, int>> v;
  if (board[r][c].getPiece()->getFirst() == true) {
    if (player == true) {
      if (r - 1 >= 0 && board[r - 1][c].getPiece() == nullptr) v.push_back(std::pair<int, int>(r - 1, c));
      if (c - 1 >= 0 && board[r - 1][c - 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r - 1, c - 1));
      if (c + 1 <= 7 && board[r - 1][c + 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r - 1, c + 1));
      if (r - 2 >= 0 && board[r - 2][c].getPiece() == nullptr) v.push_back(std::pair<int, int>(r - 2, c));
    } else {
      if (r + 1 <= 7 &&board[r + 1][c].getPiece() == nullptr) v.push_back(std::pair<int, int>(r + 1, c));
      if (c - 1 >= 0 && board[r - 1][c - 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r + 1, c - 1));
      if (c + 1 <= 7 && board[r - 1][c + 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r + 1, c + 1));
      if (r + 2 <= 7 &&board[r + 2][c].getPiece() == nullptr) v.push_back(std::pair<int, int>(r + 2, c));
    }
  } else {
    if (player == true) {
      if (r - 1 >= 0 && board[r - 1][c].getPiece() == nullptr) v.push_back(std::pair<int, int>(r - 1, c));
      if (c - 1 >= 0 && board[r - 1][c - 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r - 1, c - 1));
      if (c + 1 <= 7 && board[r - 1][c + 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r - 1, c + 1));
    } else {
      if (r + 1 <= 7 &&board[r + 1][c].getPiece() == nullptr) v.push_back(std::pair<int, int>(r + 1, c));
      if (c - 1 >= 0 && board[r - 1][c - 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r + 1, c - 1));
      if (c + 1 <= 7 && board[r - 1][c + 1].getPiece() != nullptr) v.push_back(std::pair<int, int>(r + 1, c + 1));
    }
  }
  return v;
}

std::vector<std::pair<int, int>> ChessBoard::legalRange(int r, int c, std::string type, bool player) {
  if (type == "Q" || type == "q" || type == "R" || type == "r" || type == "B" || type == "b") { // 上0 下1 左2 右3 左上4 右上5 左下6 右下7
    return legal(r, c, type, player);
  } else if (type == "N" || type == "n") {
    return legalN(r, c, type, player);
  } else if (type == "K" || type == "k") {
    return legalK(r, c, type, player);
  }
  return legalP(r, c, type, player);
}

std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> ChessBoard::computerL3(bool player) {
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> m;
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> range = computerL1(player);
  for (auto it : range) {
    std::vector<std::pair<int, int>> moves;
    std::pair<int, int> p = it.first;
    int l = it.second.size();
    if (l > 0) {
      for (int j = 0; j < l; j++) {
        int row = it.second[j].first;
        int col = it.second[j].second;
        int r = it.first.first;
        int c = it.first.second;
        std::string type = board[r][c].getPiece()->type;
        // bool check = this->check(player, row, col, type);
        bool incheck = this->incheck(player, row, col);
        if (board[row][col].getPiece() != nullptr && board[row][col].getPiece()->colour != player) {
          if (type == "P" && type == "p") {
            int hdist = row - r;
            if (hdist == -1 || hdist == 1) moves.push_back(it.second[j]);
          } else {
            if (type != "K" && type != "k") moves.push_back(it.second[j]);
          }
        } else if (incheck == false) {
          moves.push_back(it.second[j]);
        }
      }
    }
    if (moves.size() > 0) {
      m.insert(std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>(p, moves));
    }
  }
  return m;
}

std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>ChessBoard::computerL2(bool player) {
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> captures;
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> range = computerL1(player);
  for (auto it : range) {
    std::vector<std::pair<int, int>> moves;
    std::pair<int, int> p = it.first;
    int l = it.second.size();
    if (l > 0) {
      for (int j = 0; j < l; j++) {
        int row = it.second[j].first;
        int col = it.second[j].second;
        int r = it.first.first;
        int c = it.first.second;
        std::string type = board[r][c].getPiece()->type;
        if (board[row][col].getPiece() != nullptr && board[row][col].getPiece()->colour != player) {
          if (type == "P" && type == "p") {
            int hdist = row - r;
            if (hdist == -1 || hdist == 1) moves.push_back(it.second[j]);
          } else {
            if (type != "K" && type != "k") moves.push_back(it.second[j]);
          }
        }
        if (board[row][col].getPiece() == nullptr) {
          board[row][col].setPiece(type, player);
          bool check = this->check(player, row, col, type);
          if (check == true) moves.push_back(it.second[j]);
          board[row][col].clearPiece();
        }
      }
    }
    if (moves.size() > 0) {
      captures.insert(std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>(p, moves));
    }
  }
  return captures;
}

std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> ChessBoard::computerL1(bool player) {
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> m;
  for (int i = 0; i < size; i++)  {
    for (int j = 0; j < size; j++) {
      if (board[i][j].getPiece() != nullptr && board[i][j].getPiece()->colour == player) {
        std::string type = board[i][j].getPiece()->type;
        std::vector<std::pair<int, int>> range = oneLegalMove(player, i, j, type);
        if (range.size() > 0) {
          std::pair<int, int> p = std::pair<int, int>(i , j);
          m.insert(std::pair<std::pair<int, int>, std::vector<std::pair<int, int>>>(p, range));
        }
      }
    }
  }
  return m;
}

std::vector<std::pair<int, int>> ChessBoard::oneLegalMove(bool player, int r, int c, std::string type) {
  std::vector<std::pair<int, int>> v = legalRange(r, c, type, player);
  for(auto it = v.begin(); it != v.end();) {
    if(it->first == -1) {
      it = v.erase(it);
    } else {
      it++;
    }
  }
  return v;
}

std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> ChessBoard::computerMove(bool player, std::string level) {
  std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> v = computerL1(player);
  if (level == "1") {
    return v;
  } else if (level == "2") {
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> range = computerL2(player);
    if (range.size() > 0) {
      return range;
    }
  } else if (level == "3") {
    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> range = computerL3(player);
    if (range.size() > 0) {
      return range;
    }
  }
  return v;
}


std::ostream &operator<<(std::ostream &out, ChessBoard &b) {
  for(int i = 0; i <= 8; ++i) {
    if (i < 8) {
      int n = 8 - i;
      out << n << " ";
      for(int j = 0; j < 8; ++j) {
        out << b.getBoard()[i][j];
      }
      out << std::endl;
    } else {
      out << "  abcdefgh" << std::endl;
    }
  }
  return out;
}
