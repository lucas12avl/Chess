//
//  Chessboard.cpp
//  LearnChess
//
//
//

#include "Chessboard.hpp"
#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include "../GraphicManager.h"

using namespace std;

void Chessboard::LoadBoardFromFile(const string& path) { // A partir de un fichero, te carga una partida

	ifstream tauler;
	tauler.open(path);
	ChessPosition PosicionPieza;

	if (tauler.is_open()) {

		string Pieza;
		getline(tauler, Pieza); // Pilla la primera linea del fichero



		while (!tauler.eof())
		{
			PosicionPieza.BoardTxtToGame(Pieza); // nos da la posicion real (del tablero piece) en la que va la pieza 

			m_board[PosicionPieza.getPosX()][PosicionPieza.getPosY()].ChessPieceConversorToCode(Pieza);  // cambia del estado vacio a una pieza cocreta en una determinada posicin del tablero


			getline(tauler, Pieza); // nos pilla la siguinte pieza a analizar


		}

		PosicionPieza.BoardTxtToGame(Pieza); // nos da la posicion real (del tablero piece) en la que va la pieza 

		m_board[PosicionPieza.getPosX()][PosicionPieza.getPosY()].ChessPieceConversorToCode(Pieza);

	}


	// ya hemos acabdo de cargar el tablero con la partida

}




string Chessboard::conversor(int fila, int columna) const { // se usa en el ToString para hacer la chessboard de forma 'grafica'

	string resultado;
	m_board[fila][columna].getColor();
	m_board[fila][columna].getType();


	if (m_board[fila][columna].getColor() == CPC_NONE)
		resultado = "__";
	else {

		if (m_board[fila][columna].getColor() == CPC_Black)
			resultado = "b";
		else
			resultado = "w";

		switch (m_board[fila][columna].getType())
		{
		case CPT_King:
			resultado += "R";
			break;

		case CPT_Queen:
			resultado += "D";
			break;

		case CPT_Rook:
			resultado += "T";
			break;

		case CPT_Bishop:
			resultado += "A";
			break;

		case CPT_Knight:
			resultado += "C";
			break;

		case CPT_Pawn:
			resultado += "P";
			break;
		}
	}

	return resultado;

}

string Chessboard::ToString() const { // crea la chessboard de forma 'grafica'

	string chess;
	string aux;
	string numeros = "87654321";
	string letras = "  a  b  c  d  e  f  g  h";

	for (int i = 0; i < NUM_ROWS; i++)
	{
		chess += numeros[i];
		chess += " ";

		for (int j = 0; j < NUM_COLS; j++)
		{
			aux = conversor(i, j);
			chess += aux;

			if (j < NUM_COLS - 1) // para que no ponga el espacio al final de la fila
				chess += " ";
		}

		chess += '\n';

	}
	chess += letras;

	return chess;

}

void Chessboard::ColumnMovementForward(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int y = actualPositionY;
	y++;
	if ((m_board[actualPositionX][y].getType() == CPT_EMPTY || color != m_board[actualPositionX][y].getColor()) && y <= 7)
	{
		validPositions.setPosX(actualPositionX);
		validPositions.setPosY(y);
		if (color != m_board[actualPositionX][y].getColor() && m_board[actualPositionX][y].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}

void Chessboard::RowMovementForward(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int x = actualPositionX;
	x++;
	if ((m_board[x][actualPositionY].getType() == CPT_EMPTY || color != m_board[x][actualPositionY].getColor()) && x <= 7)
	{
		validPositions.setPosX(x);
		validPositions.setPosY(actualPositionY);
		if (color != m_board[x][actualPositionY].getColor() && m_board[x][actualPositionY].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}

void Chessboard::ColumnMovementBack(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int y = actualPositionY;
	y--;
	if ((m_board[actualPositionX][y].getType() == CPT_EMPTY || color != m_board[actualPositionX][y].getColor()) && y >= 0)
	{
		validPositions.setPosX(actualPositionX);
		validPositions.setPosY(y);
		if (color != m_board[actualPositionX][y].getColor() && m_board[actualPositionX][y].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}

void Chessboard::RowMovementBack(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int x = actualPositionX;
	x--;
	if ((m_board[x][actualPositionY].getType() == CPT_EMPTY || color != m_board[x][actualPositionY].getColor()) && x >= 0)
	{
		validPositions.setPosX(x);
		validPositions.setPosY(actualPositionY);
		if (color != m_board[x][actualPositionY].getColor() && m_board[x][actualPositionY].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}

void Chessboard::DiagonalLeftBack(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int x = actualPositionX, y = actualPositionY;
	x--;
	y--;
	if ((m_board[x][y].getType() == CPT_EMPTY || color != m_board[x][y].getColor()) && x >= 0 && y >= 0)
	{
		validPositions.setPosX(x);
		validPositions.setPosY(y);
		if (color != m_board[x][y].getColor() && m_board[x][y].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}
void Chessboard::DiagonalLeftUp(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int x = actualPositionX, y = actualPositionY;
	y++;
	x--;
	if ((m_board[x][y].getType() == CPT_EMPTY || color != m_board[x][y].getColor()) && x >= 0 && y <= 7)
	{
		validPositions.setPosX(x);
		validPositions.setPosY(y);
		if (color != m_board[x][y].getColor() && m_board[x][y].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}
void Chessboard::DiagonalRightBack(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int x = actualPositionX, y = actualPositionY;
	x++;
	y--;
	if ((m_board[x][y].getType() == CPT_EMPTY || color != m_board[x][y].getColor()) && x <= 7 && y >= 0)
	{
		validPositions.setPosX(x);
		validPositions.setPosY(y);
		if (color != m_board[x][y].getColor() && m_board[x][y].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}
void Chessboard::DiagonalRightUp(const int& actualPositionY, const int& actualPositionX, ChessPosition& validPositions, ChessPieceColor color, bool& difColor)const
{
	int x = actualPositionX, y = actualPositionY;
	x++;
	y++;
	if ((m_board[x][y].getType() == CPT_EMPTY || color != m_board[x][y].getColor()) && x <= 7 && y <= 7)
	{
		validPositions.setPosX(x);
		validPositions.setPosY(y);
		if (color != m_board[x][y].getColor() && m_board[x][y].getColor() != CPC_NONE)
		{
			difColor = true;
		}
	}
	else
	{
		validPositions.setPosX(-1);
	}

}








VecOfPositions Chessboard::GetValidMoves(const ChessPosition& pos)const
{
	// hay que coger el tipo de ficha ( con el getter)  y su posicion para saber hacia donde se puede mover.

	int actualPositionX = pos.getPosX(); // estas variables son las que se ponen en los metodos y cuando hay un bucle se editan 
	int actualPositionY = pos.getPosY();
	int newPositionX = actualPositionX; // estas dos variables conservan los valores originales de x e y
	int newPositionY = actualPositionY;
	bool differentColor = false; // booleano que devuelve true cuando hay ua casilla valida donde se encuentra una pieza del color contrario
	bool finish = false; // booleano que comprueba que no se sale del tablero la posición
	ChessPieceType pieceType = getPieceType(actualPositionX, actualPositionY);
	ChessPieceColor pieceColor = getPieceColor(actualPositionX, actualPositionY);
	ChessPosition validPositions;// se pone en los procedimientos para que devuela las posiciones ( si tiene el vaor -1 en la x significa que la casilla no era valida porque se salía del tablero.
	validPositions.setPosX(-1);
	validPositions.setPosY(-1);
	VecOfPositions vectorPositions; // vector que devolverá las posiciones validas


	//solo un switch case porque el color de la pieza no es relevante para los movimientos hasta el final


	switch (pieceType)
	{
	case CPT_King: //king (8 direcciones)
	{
		ColumnMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla arriba
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		ColumnMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor);// casilla abajo
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //casilla izquierda
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // casilla derecha
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		DiagonalLeftBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal  abajo izquierda
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		DiagonalLeftUp(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // diagonal arriba izquierda
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		DiagonalRightBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // diagonal abajo derecha
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}

		DiagonalRightUp(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // diagonal arriba derecha
		if (validPositions.getPosX() != -1)
		{
			vectorPositions.push_back(validPositions);
		}
	}
	break;
	case CPT_Queen: // Queen
		do
		{

			ColumnMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			ColumnMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla atras (columna)
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla izquierda
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla derecha
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalLeftBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal izquierda abajo
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalLeftUp(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal izquierda arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalRightBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal derecha abajo
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalRightUp(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal derecha arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		differentColor = false;
		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		break;
	case CPT_Rook: // rook
		do
		{

			ColumnMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			ColumnMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //una casilla arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		break;
	case CPT_Bishop: // bishop 
		do
		{

			DiagonalLeftBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal izquierda abajo
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalLeftUp(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal izquierda arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalRightBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal derecha abajo
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		do
		{

			DiagonalRightUp(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); //diagonal derecha arriba
			if (validPositions.getPosX() != -1)
			{
				vectorPositions.push_back(validPositions);
				actualPositionX = validPositions.getPosX();
				actualPositionY = validPositions.getPosY();
			}
			else
			{
				finish = true;
			}

		} while (finish == false && differentColor == false);

		finish = false;
		actualPositionX = newPositionX;
		actualPositionY = newPositionY;
		break;

	case CPT_Knight: // knight 

		// hacia abajo las dos casillas 
		actualPositionY = actualPositionY - 2;
		validPositions.setPosX(actualPositionX);
		validPositions.setPosY(actualPositionY);
		if (validPositions.getPosX() >= 0 && validPositions.getPosX() <= 8 && validPositions.getPosY() >= 0 && validPositions.getPosY() <= 8)
		{
			RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la izquierda
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);
			RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la derecha 
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);

		}

		actualPositionX = newPositionX;
		actualPositionY = newPositionY;
		// hacia arriba las dos casillas

		actualPositionY = actualPositionY + 2;
		validPositions.setPosX(actualPositionX);
		validPositions.setPosY(actualPositionY);

		if (validPositions.getPosX() >= 0 && validPositions.getPosX() <= 8 && validPositions.getPosY() >= 0 && validPositions.getPosY() <= 8)
		{
			RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la izquierda
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);
			RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la derecha 
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);

		}

		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		// hacia la derecha las dos casillas 
		actualPositionX = actualPositionX - 2;
		validPositions.setPosX(actualPositionX);
		validPositions.setPosY(actualPositionY);

		if (validPositions.getPosX() >= 0 && validPositions.getPosX() <= 8 && validPositions.getPosY() >= 0 && validPositions.getPosY() <= 8)
		{
			ColumnMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la izquierda
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);
			ColumnMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la derecha 
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);

		}

		actualPositionX = newPositionX;
		actualPositionY = newPositionY;

		//hacia la izquierda las dos casillas
		actualPositionX = actualPositionX + 2;
		validPositions.setPosX(actualPositionX);
		validPositions.setPosY(actualPositionY);

		if (validPositions.getPosX() >= 0 && validPositions.getPosX() < 8 && validPositions.getPosY() >= 0 && validPositions.getPosY() < 8)
		{
			ColumnMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la izquierda
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);
			ColumnMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // L hacia la derecha 
			if (validPositions.getPosX() != -1)
				vectorPositions.push_back(validPositions);
		}
		break;
	case CPT_Pawn: // pawn

		if (pieceColor == CPC_Black)
		{
			if (actualPositionX == 1)// casilla de inicio de los peones negros
			{
				RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // utilizamos el back ya que las negras van hacia abajo
				if (differentColor == false && validPositions.getPosX() > 0) // los peones no comen en recto por tanto tiene que estar en false 
				{
					vectorPositions.push_back(validPositions);
					actualPositionX = validPositions.getPosX(); // editamos las X e Y para poder calcular las dos casillas ya que 
					actualPositionY = validPositions.getPosY();

					RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor);
					if (differentColor == false && validPositions.getPosX() > 0)
					{
						vectorPositions.push_back(validPositions);
					}
				}
			}
			else
			{
				RowMovementForward(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor);
				if (differentColor == false && validPositions.getPosX() > 0)
				{
					vectorPositions.push_back(validPositions);
				}
				else
				{
					differentColor = false;
				}
			}
			DiagonalRightBack(newPositionY, newPositionX, validPositions, pieceColor, differentColor);
			if (differentColor == true && validPositions.getPosX() > 0) // si está en true es que si hay una pieza de otro color y por tanto se la puede comer
			{
				vectorPositions.push_back(validPositions);
			}

			differentColor = false;

			DiagonalRightUp(newPositionY, newPositionX, validPositions, pieceColor, differentColor);
			if (differentColor == true && validPositions.getPosX() > 0) // si está en true es que si hay una pieza de otro color y por tanto se la puede comer
			{
				vectorPositions.push_back(validPositions);
			}
		}
		else
		{
			if (actualPositionX == 6) // casilla de inicio de los peones blancos
			{
				RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor); // utilizamos el forward ya que las negras van hacia arriba
				if (differentColor == false && validPositions.getPosX() > 0) // los peones no comen en recto por tanto tiene que estar en false 
				{
					vectorPositions.push_back(validPositions);
					actualPositionX = validPositions.getPosX(); // editamos las X e Y para poder calcular las dos casillas ya que 
					actualPositionY = validPositions.getPosY();

					RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor);
					if (differentColor == false && validPositions.getPosX() > 0)
					{
						vectorPositions.push_back(validPositions);
					}
				}

			}
			else
			{
				RowMovementBack(actualPositionY, actualPositionX, validPositions, pieceColor, differentColor);
				if (differentColor == false && validPositions.getPosX() > 0)
				{
					vectorPositions.push_back(validPositions);
				}
				else
				{
					differentColor = false;
				}
			}

			DiagonalLeftBack(newPositionY, newPositionX, validPositions, pieceColor, differentColor); // miramos las diagonales para saber si se puede comer
			if (differentColor == true && validPositions.getPosX() > 0) // si está en true es que si hay una pieza de otro color y por tanto se la puede comer
			{
				vectorPositions.push_back(validPositions);
			}

			differentColor = false; // reestablecemos el false para ver la otra diagonal

			DiagonalLeftUp(newPositionY, newPositionX, validPositions, pieceColor, differentColor);
			if (differentColor == true && validPositions.getPosX() > 0) // si está en true es que si hay una pieza de otro color y por tanto se la puede comer
			{
				vectorPositions.push_back(validPositions);
			}
		}
		break;
	default:
		vectorPositions.push_back(validPositions);
		break;
	}

	return vectorPositions;
}

bool Chessboard::MovePiece(const ChessPosition& posFrom, const ChessPosition& posTo)
{


	//LAS COORDENADAS ESTAN DADAS AL REVES DE LA MATRIZ, POR TANTO HAY QUE INTERCANVIAR LA POS X CON LA Y, (la x del posfrom es nuestra y)
	int positionX = posFrom.getPosY(), positionY = posFrom.getPosX(); // adopta las diferentes posciones validas para mirar si la deseada está entre ellas
	int finalPositionX = posTo.getPosY(), finalPositionY = posTo.getPosX(); // posiciones para comparar


	bool findedPosition = false; // si encontramos la posicion válida entonces el booleano para el bucle
	// tenemos que movernos primero entre filas [hacia abajo en el eje y] y luego entre columnas[hacia la derecha en nuestro eje x]

	ChessPieceColor color = m_board[positionY][positionX].getColor(); //cogemos el color de la pieza para despues setearlo en la nueva posicion
	ChessPieceType type = m_board[positionY][positionX].getType(); //cogemos el tipo de pieza para setearlo en la nueva posicion


	VecOfPositions validPositions;
	validPositions = GetValidMoves(posFrom); // pasamos las posiciones válidas a un vector para comparar


	vector<ChessPosition>::iterator start, end;
	start = validPositions.begin(); //iterador que va apuntando a las diferentes casillas
	end = validPositions.end();	//iterador que apunta al final del vectorç



	while (findedPosition == false && start != end)
	{

		//en el vector de posiciones validas, estan estructuradas de forma (x,y) por tanto, no hay que hacer ningun cambio
		positionX = start->getPosX();
		positionY = start->getPosY();



		if (ChessPosition(positionX, positionY) == posTo)
		{
			findedPosition = true;
		}
		else
		{
			start++;
		}



	}

	positionX = posFrom.getPosX(); // cogemos las iniciales para poder vaciar la posicion de la  pieza que se mueve 
	positionY = posFrom.getPosY();



	if (findedPosition == true)
	{
		//como ya hicmos el cambio de posciones x e y no hace falta volverlo hacer, por eso, en esta parte, podemos dejar la X y la Y en su forma convencional
		m_board[positionX][positionY].setColor(CPC_NONE);//vaciamos la anterior posicion
		m_board[positionX][positionY].setType(CPT_EMPTY);

		m_board[finalPositionY][finalPositionX].setColor(color); // modificamos la nueva posicion
		m_board[finalPositionY][finalPositionX].setType(type);

		return true;

	}
	else
	{
		return false;
	}
}

ChessPieceColor Chessboard::GetPieceColorAtPos(const ChessPosition& pos) const {

	ChessPieceColor color = m_board[pos.getPosX()][pos.getPosY()].getColor();

	return color;
}

ChessPieceType Chessboard::GetPieceTypeAtPos(const ChessPosition& pos) const {

	ChessPieceType type;
	type = m_board[pos.getPosX()][pos.getPosY()].getType();

	return type;

}

ostream& operator<<(ostream& output, ChessPosition& p1)
{
	output << p1.getPosX() << p1.getPosY();
	return output;
}


void Chessboard::Render_InitialBoard() //RENDERIZA EL TABLERO INICIAL
{
	Piece Renderizar;
	ChessPieceColor color = CPC_Black;
	int cols;

	for (int j = 0; j < 2; j++)
	{
		if (color == CPC_Black)
			cols = 0;
		else
			cols = 7;

		Renderizar.Render(CPT_King, color, 4, cols);
		Renderizar.Render(CPT_Queen, color, 3, cols);
		Renderizar.Render(CPT_Rook, color, 0, cols);
		Renderizar.Render(CPT_Rook, color, 7, cols);
		Renderizar.Render(CPT_Bishop, color, 2, cols);
		Renderizar.Render(CPT_Bishop, color, 5, cols);
		Renderizar.Render(CPT_Knight, color, 1, cols);
		Renderizar.Render(CPT_Knight, color, 6, cols);

		for (int i = 0; i < NUM_COLS; i++)
		{
			if (color == CPC_Black)
				Renderizar.Render(CPT_Pawn, color, i, cols + 1);
			else
				Renderizar.Render(CPT_Pawn, color, i, cols - 1);

		}
		color = CPC_White;
	}
}

