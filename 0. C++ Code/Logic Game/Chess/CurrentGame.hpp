//
//  CurrentGame.hpp
//  LearnChess
//
// 
//

#ifndef CurrentGame_hpp
#define CurrentGame_hpp

#include <stdio.h>
#include <string>
#include "GameInfo.h"
#include "MovementHistory.h"
#include "Chessboard.hpp" // hay que incluir un obj de la clase chessboard en la parte privada de CurrentGame


using namespace std;

class CurrentGame {

public:
    CurrentGame();
    
    void            init(GameMode mode, const string& intitialBoardFile, const string& movementsFile);
	bool			updateAndRender(int mousePosX, int mousePosY, bool mouseStatus);
    void            end();  
    void            caselles(const int& contadorFila,const  int& contadorColumna);
    void            renderPiece(const char& PieceColor, const  char& PieceType)const;
    void            conversor(string moviment);
   

private:
    Chessboard game;
    stackMovements m_moviments;
    GameMode modeGame;
    string nomFitxer;
    ChessPosition newPositionToRender, positionHelper;
    Piece colorHelp;
    int lines, contadorColor = 0;
    bool m_inicialitzat;
    bool enrere; //variable que ens diu si el jugador vol desfer el ultim moviment, true si ho vol fer, una vegada ha desfet el moviment torna a false
    
};
#endif /* CurrentGame_hpp */
