#include "piece.h"
#include <iostream>

Piece::Piece(std::string t, bool colour, int row, int col): type{t}, colour{colour},
 r{row}, c{col}, check {0} {}

 bool Piece::getPassant() {
   return 0;
 }

 bool Piece::getFirst() {
   return 0;
 }

 void Piece::setFirst(bool first) {
   return;
 }

 void Piece::setPassant(bool passant) {
   return;
 }

Piece::~Piece() {}
