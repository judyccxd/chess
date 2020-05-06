#include "cell.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include <string>

Cell::Cell(): r{0}, c{0}, colour{0}, p{nullptr} {}

Cell::~Cell() {
  delete p;
}

void Cell::setCell(int r,int c,bool colour) {
  this->r = r;
  this->c = c;
  this->colour = colour;
}

Piece *&Cell::getPiece() {
  return p;
}

bool Cell::getColour() {
  return colour;
}

void Cell::clearPiece() {
  delete p;
  p = nullptr;
}

void Cell::setPiece(std::string s, bool colour) {
  if(p != nullptr) {
    return;
  }
  if (s == "q" || s == "Q") {
    p = new Queen{s, colour, r, c};
  } else if (s == "k" || s == "K") {
    p = new King{s, colour, r, c};
  } else if (s == "n" || s == "N") {
    p = new Knight{s, colour, r, c};
  } else if (s == "r" || s == "R") {
    p = new Rook{s, colour, r, c};
  } else if (s == "b" || s == "B") {
    p = new Bishop{s, colour, r, c};
  } else if (s == "P" || s == "p") {
    p = new Pawn{s, colour, r, c};
  }
}

void Cell::attackPiece(std::string s, bool colour) {
  delete p;
  if (s == "q" || s == "Q") {
    p = new Queen{s, colour, r, c};
  } else if (s == "k" || s == "K") {
    p = new King{s, colour, r, c};
  } else if (s == "n" || s == "N") {
    p = new Knight{s, colour, r, c};
  } else if (s == "r" || s == "R") {
    p = new Rook{s, colour, r, c};
  } else if (s == "b" || s == "B") {
    p = new Bishop{s, colour, r, c};
  } else {
    p = new Pawn{s, colour, r, c};
  }
}

std::ostream &operator<<(std::ostream &out, const Cell &c) {
  if (c.p != nullptr) {
    out << c.p->type;
  } else {
    if (c.colour == 1) {
      out << " ";
    } else {
      out << "_";
    }
  }
  return out;
}
