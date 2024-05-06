//
//  Piece.cpp
//  LearnChess
//
//
//

#include "Piece.hpp"
#include <string>
#include <iostream>
#include "../GraphicManager.h"
using namespace std;

const string Piece::ChessPieceConversorToTxt() { // convierte la pieza en un stirng para poderla guardar en un txt

	string piece; 
/*
	CPT_King, //rey
		CPT_Queen, // reina
		CPT_Rook, // torre
		CPT_Bishop, //Alfil
		CPT_Knight, //caballo
		CPT_Pawn, //peon
		CPT_EMPTY //vacío 
		*/

	if (m_color == CPC_Black) {

		switch (m_type)
		{
			case CPT_King:
				piece = "1. R";
				break;

			case CPT_Queen:
				piece = "1. D";
				break;

			case CPT_Rook:
				piece = "1. T";
				break;

			case CPT_Bishop:
				piece = "1. A";
				break;

			case CPT_Knight:
				piece = "1. C";
				break;

			case CPT_Pawn:
				piece = "1. P";
				break;

			case CPT_EMPTY:
				piece = "CPT_EMPTY";
				break;
		}
	}
	
	if (m_color == CPC_White) {

		switch (m_type)
		{
		case CPT_King:
			piece = "0. R";
			break;


		case CPT_Queen:
			piece = "0. D";
			break;

		case CPT_Rook:
			piece = "0. T";
			break;

		case CPT_Bishop:
			piece = "0. A";
			break;

		case CPT_Knight:
			piece = "0. C";
			break;

		case CPT_Pawn:
			piece = "0. P";
			break;

		case CPT_EMPTY:
			piece = "CPT_EMPTY";
			break;
		}
	}
	return piece;
}



 void Piece::ChessPieceConversorToCode(const string& PiezaTxt) { // construye las piezas a partir de un fichero de txt (Funciona como el chessConversor)
	/*
		CPT_King, //rey
			CPT_Queen, // reina
			CPT_Rook, // torre
			CPT_Bishop, //Alfil
			CPT_Knight, //caballo
			CPT_Pawn, //peon
			CPT_EMPTY //vacío
			*/

	if (PiezaTxt[0] == '1') 
		setColor(CPC_Black);
	else 
		setColor(CPC_White);


		switch (PiezaTxt[3])
		{
		case 'R':
			setType(CPT_King);
			break;

		case 'T':
			setType(CPT_Rook);
			break;

		case 'A':
			setType(CPT_Bishop);
			break;

		case 'C':
			setType(CPT_Knight);
			break;

		case 'P':
			setType(CPT_Pawn);
			break;

		case 'D':
			setType(CPT_Queen);
			break;
		}

	}





 void Piece::Render(ChessPieceType type, ChessPieceColor color, int posX, int posY) //RENDERIZA UNA PIEZA DEL TABLERO
 {
	 if (color == CPC_Black)
	 {
		 switch (type)
		 {
		 case CPT_King:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Queen:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Rook:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Bishop:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Knight:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Pawn:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_BLACK, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 default:
			 break;
		 }
	 }
	 else
	 {
		 switch (type)
		 {
		 case CPT_King:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KING_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Queen:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_QUEEN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Rook:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_ROOK_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Bishop:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_BISHOP_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Knight:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_KNIGHT_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 case CPT_Pawn:
			 GraphicManager::getInstance()->drawSprite(IMAGE_PIECE_PAWN_WHITE, CELL_INIT_X + (posX * CELL_W), CELL_INIT_Y + (posY * CELL_H));
			 break;
		 default:
			 break;
		 }
	 }
 }

