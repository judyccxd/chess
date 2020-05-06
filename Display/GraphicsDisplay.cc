#include "GraphicsDisplay.h"

// ctor
GraphicsDisplay::GraphicsDisplay(Xwindow &xw):
xw{xw}, theDisplay{}, board{}, length{500 / 9}, boardSize{9} {
  int x = 0;
  int y = 0;
  for(int i = 0; i < boardSize; i++) {
    std::vector<std::pair <int, int>>sub;
    std::vector<std::string> s;
    theDisplay.push_back(sub);
    board.push_back(s);
    x = 0;
    if (i < 8) {
      for(int j = 0; j < boardSize; j++) {
        theDisplay[i].emplace_back(x, y);
        if (j == 0) {
          int row = 8 - i;
          std::string r = std::to_string(row);
          board[i].push_back(r);
        } else {
          board[i].push_back("colour");
        }
        x += length + 1;
      }
    } else {
      for(int j = 0; j < boardSize; j++) {
        theDisplay[i].emplace_back(x, y);
        x += length + 1;
      }
      board[i].push_back("");
      board[i].push_back("a");
      board[i].push_back("b");
      board[i].push_back("c");
      board[i].push_back("d");
      board[i].push_back("e");
      board[i].push_back("f");
      board[i].push_back("g");
      board[i].push_back("h");
    }
    y += length + 1;
  }
}

// dtor
GraphicsDisplay::~GraphicsDisplay() {
  for(int i = 0; i < boardSize; ++i) {
    theDisplay[i].clear();
    board[i].clear();
  }
  theDisplay.clear();
  board.clear();
}

void GraphicsDisplay::cellColour(int r, int c) {
    board[r][c] = "";
}

void GraphicsDisplay::setPiece(int r, int c, int row, int col, std::string type, bool passant, std::pair<int, int> k) {
  if (row >= 0 && col >= 0) board[row][col] = type;
  if (r >= 0 && c >= 0) cellColour(r, c);
  if (passant == true) cellColour(r, col);
  if (k.first >= 0) {
    cellColour(k.first, k.second);
    int hdist = col - c;
    if (type == "K") {
      if (hdist > 0) {
        board[r][col - 1] = "R";
      } else {
        board[r][col + 1] = "R";
      }
    } else {
      if (hdist > 0) {
        board[r][col - 1] = "r";
      } else {
        board[r][col + 1] = "r";
      }
    }
  }
}

// operator<<(out, gd) prints gd
std::ostream &operator<<(std::ostream &out, GraphicsDisplay &gd) {
  for(int i = 0; i < gd.boardSize; i++) {
    for(int j = 0; j < gd.boardSize; j++) {
      int x = gd.theDisplay[i][j].first;
      int y = gd.theDisplay[i][j].second;
      if (j > 0 && i < 8) {
        if ((i % 2 == 1 && j % 2 == 1) || (i % 2 == 0 && j % 2 == 0)) {
          (gd.xw).fillRectangle(x, y, gd.length, gd.length, 0);
        }
        if ((i % 2 == 1 && j % 2 == 0) || (i % 2 == 0 && j % 2 == 1)) {
          (gd.xw).fillRectangle(x, y, gd.length, gd.length, 3);
        }
      }
      if (gd.board[i][j] != "colour") {
        x += (500/16);
        y += (500/16);
        (gd.xw).drawString(x, y, gd.board[i][j]);
      }
    }
  }
  return out;
}
