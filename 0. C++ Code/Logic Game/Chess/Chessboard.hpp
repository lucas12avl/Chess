//
//  Chessboard.hpp
//  LearnChess
//
//  
//

#ifndef Chessboard_hpp
#define Chessboard_hpp

#include <stdio.h>
#include "Piece.hpp"
#include "GameInfo.h"
#include "ChessPosition.hpp"



class Chessboard {

public:
    Chessboard() {};


    //getters --> Necesarios para determinar las posiciones en las que se pueden mover.

    const ChessPieceType& getPieceType (int x, int y) const  { return m_board[x][y].getType(); }
    const ChessPieceColor& getPieceColor(int x, int y) const { return m_board[x][y].getColor(); }

    //setters --> Necesarios para mover la pieza
    void setPieceType(const ChessPieceType type, int x, int y){ m_board[x][y].setType(type); }
    void setPieceColor(const ChessPieceColor color, int x, int y) { m_board[x][y].setColor(color); }



    void            LoadBoardFromFile(const string& path);
    VecOfPositions  GetValidMoves(const ChessPosition& pos)const;
    bool            MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo);
    string          ToString() const;

    //procedimientos
    void    ColumnMovementForward(const int& y, const int& actualPositionX, ChessPosition& validMoves, ChessPieceColor color, bool& differentColor)const;
    void    RowMovementForward(const int& x, const int& actualPositionY, ChessPosition& validMoves, ChessPieceColor color, bool& differentColor)const;
    void    ColumnMovementBack(const int& y, const int& actualPositionX, ChessPosition& validMoves, ChessPieceColor color, bool& differenetColor)const;
    void    RowMovementBack(const int& x, const int& actualPositionY, ChessPosition& validMoves, ChessPieceColor color, bool& differentColor)const;
    void    DiagonalLeftBack(const int& x, const int& actualPositionY, ChessPosition& validMoves, ChessPieceColor color, bool& differentColor)const;
    void    DiagonalLeftUp(const int& x, const int& actualPositionY, ChessPosition& validMoves, ChessPieceColor color, bool& differentColor)const;
    void    DiagonalRightBack(const int& x, const int& actualPositionY, ChessPosition& validMoves, ChessPieceColor color, bool& differentColor)const;
    void    DiagonalRightUp(const int& x, const int& actualPositionY, ChessPosition& validMoves, ChessPieceColor color, bool&  differentColor)const;
    string conversor(int fila, int columna)const;

    ChessPieceColor GetPieceColorAtPos(const ChessPosition& pos)const;
    ChessPieceType GetPieceTypeAtPos(const ChessPosition& pos)const;
    void Render_InitialBoard();
   


private:
    Piece m_board[NUM_COLS][NUM_ROWS]; // 8 x 8 
};

ostream& operator<<(ostream& output, ChessPosition& p1);
#endif /* Chessboard_hpp */
