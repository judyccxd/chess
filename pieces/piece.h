#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <memory>

struct Piece : public std::enable_shared_from_this<Piece>{
  std::string type;  // See above
  bool colour;   // What colour was the new piece?  (NOT what is my colour)
  int r, c;
  bool check;

  Piece(std::string t, bool colour, int row, int col);
  virtual ~Piece();

  virtual bool legalMove(bool player, int row, int col) = 0;
  virtual bool getPassant();
  virtual bool getFirst();
  virtual void setPassant(bool passant);
  virtual void setFirst(bool first);
};

#endif
