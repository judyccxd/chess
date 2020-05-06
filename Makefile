CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
GRAPH = -lX11 -L/opt/X11/lib -I/opt/X11/include
EXEC = chess
OBJECTS = main.o cell.o ChessBoard.o ChessGame.o Subject.o piece.o queen.o king.o bishop.o pawn.o knight.o rook.o player.o human.o computer.o window.o GraphicsDisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${GRAPH}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
