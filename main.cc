#include <iostream>
#include <sstream>
// You may include other allowed headers, as needed
#include "ChessGame.h"
using namespace std;


int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  bool turn = 1;
  bool h1 = true;
  bool h2 = true;
  bool goodSetup = true;
  bool inSetup = false;
  bool ifSetup = false;
  bool staleMate = false;
  bool checkMate = false;
  bool wIncheck = false;
  bool bIncheck = false;
  int wScore = 0;
  int bScore = 0;
  string cmd;
  Xwindow xw;
  ChessGame game{xw};
  string p1;
  string p2;
  try {
    while (cin >> cmd) {
      if (cin.eof()) {
        cout << "Final Scores" << endl;
        cout << "White: " << wScore << endl;
        cout << "Black: " << bScore << endl;
        break;
      } else if (cmd == "setup") {
        inSetup = true;
        cout << game;
      } else if (cmd == "+" && inSetup ==  true) {
        string t;
        string coordinate;
        cin >> t >> coordinate;
        game.setUp(cmd, coordinate, t);
        cout << game;
      } else if (cmd == "-" && inSetup ==  true) {
        string coordinate;
        cin >> coordinate;
        game.setUp(cmd, coordinate, "");
        cout << game;
      } else if (cmd == "done" && inSetup ==  true) {
        goodSetup = game.setUp(cmd, "", "");
        if (goodSetup == false) {
          cout << "Illegal Setup" << endl;
          cout << "Do some changes" << endl;
        } else {
          cout << game;
          ifSetup = true;
          inSetup = false;
        }
      } else if (cmd == "=") {
        string colour;
        cin >> colour;
        if (colour == "white") {
          turn = true;
        } else {
          turn = false;
        }
      } else if (cmd == "game") {
        cin >> p1 >> p2;
        if(p1 != "human") h1 = false;
        if(p2 != "human") h2 = false;
        game.setPlayer(p1, p2);
        if (ifSetup ==  false) {
          game.startGame();
        } else {
          game.addPiece();
        }
        cout << game;
      }  else if (cmd == "move") {
        if(turn == 1 && !h1) {
          game.computerMove(turn);
        }
        if(turn == 0 && !h2) {
          game.computerMove(turn);
        }
        if((turn == 1 && h1) || (turn == 0 && h2)) { //human
          std::string line;
          getline(cin, line);
          istringstream iss{line};
          bool invalid = true;
          while(invalid) {
            string from;
            string dest;
            string promt = "";
            iss >> from;
            iss >> dest;
            iss >> promt;
            std::pair<int, int> f = game.getLocation(from);
            std::pair<int, int> d = game.getLocation(dest);
            int r = f.first;
            int c = f.second;
            int row = d.first;
            int col = d.second;
            if (!game.move(turn, r, c, row, col, promt)) {
              cout << "Illegal Move" << endl;
              cout << "Please Try Again" << endl;
              while(cin >> cmd) {
                if(cmd == "move") {
                  break;
                } else {
                  cout << "Illegal Commend" << endl;
                  cout << "Please Try Again" << endl;
                }
              }
            } else {
              invalid = false;
            }
          }
        }
        staleMate = game.staleMate();
        checkMate = game.checkMate(turn);
        if (staleMate ==  true) {
          cout << "Draw" << endl;
          wScore += 0.5;
          bScore += 0.5;
        } else if (checkMate ==  true) {
          if (turn == true) {
            wScore += 1;
            cout << "Checkmate! White Wins!" << endl;
          } else {
            bScore += 1;
            cout << "Checkmate! Black Wins!" << endl;
          }
        }
        if (turn == 1) {
          turn = 0;
        } else {
          turn = 1;
        }
        cout << game;
      } else if (cmd == "resign") {
        game.endGame(xw);
        if (turn == true) {
          bScore += 1;
          cout << "Black Wins!" << endl;
        } else {
          wScore += 1;
          cout << "White Wins!" << endl;
        }
      }
    }
    cout << "Final Scores" << endl;
    cout << "White: " << wScore << endl;
    cout << "Black: " << bScore << endl;
  }
  catch (ios::failure &) {}  // Any I/O failure quits

}
