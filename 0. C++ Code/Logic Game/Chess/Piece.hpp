//
//  Piece.hpp
//  LearnChess
//
//
//

#ifndef Piece_hpp
#define Piece_hpp

#include <stdio.h>
#include <vector>
#include "GameInfo.h"

using namespace std;

typedef enum {
    CPT_King, //rey
    CPT_Queen, // reina
    CPT_Rook, // torre
    CPT_Bishop, //Alfil
    CPT_Knight, //caballo
    CPT_Pawn, //peon
    CPT_EMPTY //vacío
} ChessPieceType;

typedef enum {
    CPC_Black, // piezas negras
    CPC_White, // piezas blancas
    CPC_NONE // sin color
} ChessPieceColor;





class Piece { // contiene el tipo de pieza y su color

public:
    //CONSTRUCTORES
    Piece(): m_type(CPT_EMPTY), m_color(CPC_NONE) {} // pieza vacía
    Piece(ChessPieceType type, ChessPieceColor color) : m_type(type), m_color(color) {} // pieza con algo
    
    //DESTRUCTORES
   
    //GETTERS
    const ChessPieceType& getType() const { return m_type; }
    const ChessPieceColor& getColor() const { return m_color;  }

    //SETTERS
    void setType(const ChessPieceType& type) { m_type = type; }
    void setColor(const ChessPieceColor& color) { m_color = color; }

    //METODOS
    const string ChessPieceConversorToTxt(); // convierte la pieza en un stirng para poderla guardar en un txt
    void ChessPieceConversorToCode(const string& PiezaTxt); // construye las piezas a partir de un fichero de txt (Funciona como el chessConversor)
    //valid positions
  
    void Render(ChessPieceType type, ChessPieceColor color, int posX, int posY);



private:
    ChessPieceType  m_type;
    ChessPieceColor m_color;

};


#endif /* Piece_hpp */
