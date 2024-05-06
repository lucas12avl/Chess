//
//  ChessPosition.cpp
//  LearnChess
//
//
//

#include "ChessPosition.hpp"
#include "GameInfo.h"

/* Coordinate system:
    Y (rows)
  . ^
  . |  ***Black***
  4 |
  3 |
  2 |
  1 |  ***White***
 (0,0)----------> X (cols)
      a b c ...
*/

void ChessPosition::BoardTxtToGame(const string& PiezaTxt) { // a partir de un string de una ficha, genera la posicion relativa en el array de esa ficha


	switch (PiezaTxt[4])// da la columna
	{
	case 'a':
		setPosY(0);
		break;
	case 'b':
		setPosY(1);
		break;
	case 'c':
		setPosY(2);
		break;
	case 'd':
		setPosY(3);
		break;
	case 'e':
		setPosY(4);
		break;
	case 'f':
		setPosY(5);
		break;
	case 'g':
		setPosY(6);
		break;
	case 'h':
		setPosY(7);
		break;
	}

	switch (PiezaTxt[5])// da la fila
	{
	case '8':
		setPosX(0);
		break;
	case '7':
		setPosX(1);
		break;
	case '6':
		setPosX(2);
		break;
	case '5':
		setPosX(3);
		break;
	case '4':
		setPosX(4);
		break;
	case '3':
		setPosX(5);
		break;
	case '2':
		setPosX(6);
		break;
	case '1':
		setPosX(7);
		break;
	}

}

const string ChessPosition::BoardGameToTxt() { // crea un string con la posicion de la ficha a guardar

	string PosPiezaX;
	string PosPiezaY;
	string PosR;

	switch (m_posY)// da la columna
	{
	case 0:
		PosPiezaY = 'a';
		break;
	case 1:
		PosPiezaY = 'b';
		break;
	case 2:
		PosPiezaY = 'c';
		break;
	case 3:
		PosPiezaY = 'd';
		break;
	case 4:
		PosPiezaY = 'e';
		break;
	case 5:
		PosPiezaY = 'f';
		break;
	case 6:
		PosPiezaY = 'g';
		break;
	case 7:
		PosPiezaY = 'h';
		break;
	}

	switch (m_posX)// da la fila
	{
	case 0:
		PosPiezaX = '8';
		break;
	case 1:
		PosPiezaX = '7';
		break;
	case 2:
		PosPiezaX = '6';
		break;
	case 3:
		PosPiezaX = '5';
		break;
	case 4:
		PosPiezaX = '4';
		break;
	case 5:
		PosPiezaX = '3';
		break;
	case 6:
		PosPiezaX = '2';
		break;
	case 7:
		PosPiezaX = '1';
		break;
	}

	PosR = PosPiezaY + PosPiezaX;

	return PosR;

}

bool ChessPosition::operator==(const ChessPosition& p1) const
{
	return ((m_posX == p1.m_posX) && (m_posY == p1.m_posY));
}


ChessPosition::ChessPosition(string& pos) {


	switch (pos[0])// da la columna
	{
	case 'a':
		setPosY(0);
		break;
	case 'b':
		setPosY(1);
		break;
	case 'c':
		setPosY(2);
		break;
	case 'd':
		setPosY(3);
		break;
	case 'e':
		setPosY(4);
		break;
	case 'f':
		setPosY(5);
		break;
	case 'g':
		setPosY(6);
		break;
	case 'h':
		setPosY(7);
		break;
	}

	switch (pos[1])// da la fila
	{
	case '8':
		setPosX(0);
		break;
	case '7':
		setPosX(1);
		break;
	case '6':
		setPosX(2);
		break;
	case '5':
		setPosX(3);
		break;
	case '4':
		setPosX(4);
		break;
	case '3':
		setPosX(5);
		break;
	case '2':
		setPosX(6);
		break;
	case '1':
		setPosX(7);
		break;
	}


}