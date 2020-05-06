# chess is a game that is coded using c++. 
# Display:
  8 rnbqkbnr<br />
  7 pppppppp<br />
  6 _ _ _ _<br />
  5 _ _ _ _<br />
  4 _ _ _ _<br />
  3 _ _ _ _<br />
  2 PPPPPPPP<br />
  1 RNBQKBNR<br />
  abcdefgh
# The rules are:
There are 2 kinds of player human and computer. Player can choose human vs. human, human vs. computer, and computer vs. computer.
Computer players should operate at one of several difficulty levels:
  Level 1: random legal moves.
  Level 2: prefers capturing moves and checks over other moves.#
  Level 3: prefers avoiding capture, capturing moves, and checks.
  Levels 4+: something more sophisticated.
# Command:
  1. game white-player black-player starts a new game. The parameters white-player and black-player can be either human or 
  computer[1-4].
  2. resign concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.
  3. A move consists of the command move, followed by the starting and ending coordinates of the piece to be moved, for
     example: move e2 e4. 
  4. Castling would specified by the two-square move for the king: move e1 g1 or move e1 c1 for white.
  5. Pawn promotion would additionally specify the piece type to which the pawn is promoted: move e7 e8 Q.
  6. In the case of a computer player, the command move (without arguments) makes the computer player make a move.
  7. setup enters setup mode:
     - using + K e1 places the piece K (i.e., white king in this case) on the square e1. If a piece is already on that square,        it is replaced. The board should be redisplayed.
     - using - e1 removes the piece from the square e1 and then redisplays the board. If there is no piece at that square,  
       take no action.
     - = colour makes it colour's turn to go next.
     - done leaves setup mode.
# Scoring:
  A win awards one point to the winner and zero points to the loser. A draw awards half a point to each team. When the program 
  ends (ctrl-D is pressed), it should print the nal score to the screen. 
  For example:
  Final Score:
  White: 2
  Black: 1
