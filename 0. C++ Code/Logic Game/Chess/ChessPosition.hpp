//
//  ChessPosition.hpp
//  LearnChess
//
// 
//

#ifndef ChessPosition_hpp
#define ChessPosition_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class ChessPosition { // sirve para convertir las posiciones de la matriz en posiciones del tipo abc123 y viceversa (fila, columna), 

public:
    //constructors

    ChessPosition() : m_posX(0), m_posY(0) {}
    ChessPosition(string& pos);
    ChessPosition(int x , int y) : m_posX(x), m_posY(y) {}

    // getters
    const int& getPosX() const { return m_posX; }
    const int& getPosY() const { return m_posY; }
   
    // setters
    void setPosX(int posicioX) { m_posX = posicioX; }
    void setPosY(int posicioY) { m_posY = posicioY; }


    // metodos

    void BoardTxtToGame(const string& PiezaTxt); // hay que hacer lo mismo a la inversa
    const string BoardGameToTxt();
    bool operator==(const ChessPosition& p1) const;
    

private:
    int m_posX; //Column
    int m_posY; //Row


};
typedef vector<ChessPosition> VecOfPositions;



#endif /* ChessPosition_hpp */
