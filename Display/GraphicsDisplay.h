#ifndef __GRAPHICSISPLAY_H__
#define __GRAPHICSISPLAY_H__
#include <iostream>
#include <vector>
#include <string>
#include "window.h"

class Cell;

class GraphicsDisplay {
  Xwindow &xw;
  std::vector<std::vector<std::pair <int, int>>> theDisplay;
  // cell's coordinates
  std::vector<std::vector<std::string>> board; // false is balck and true is white
  int length; // the width/height of each cell
  int boardSize;

 public:
  GraphicsDisplay(Xwindow &xw);

  void cellColour(int r, int c);

  void setPiece(int r, int c, int row, int col, std::string type, bool passant, std::pair<int, int> k);

  ~GraphicsDisplay();

  friend std::ostream &operator<<(std::ostream &out, GraphicsDisplay &gd);
};

#endif
