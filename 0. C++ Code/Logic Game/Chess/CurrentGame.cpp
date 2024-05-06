//
//  CurrentGame.cpp
//  LearnChess
//
//
//

#include "CurrentGame.hpp"
#include "GameInfo.h"
#include "../GraphicManager.h"
#include "MovementHistory.h"
#include "Chessboard.hpp"
#include <iostream>
#include <fstream>
#include<string>
#include <windows.h>
#include <vector>
extern bool m_partidaEmpezada = false;



CurrentGame::CurrentGame()
{

    m_inicialitzat = false;
    lines = 0;
    enrere = false;
  
    modeGame = GM_NONE;
    nomFitxer = "";
    
    
    
}




void eliminarMovimentTxt(const char* file_name, int n) // funcio per a eliminar una linea (es a dir, un moviment que ja hem fet)
{
    ifstream inicial(file_name);
    ofstream fitxeNou;
    fitxeNou.open("temp.txt", ios::out);

    char ch;
    int line = 1;
    while (inicial.get(ch))
    {
        if (ch == '\n')
            line++;

        if (line != n)      // si no hem pogut eliminar
            fitxeNou << ch;
    }
    fitxeNou.close();
    inicial.close();
    remove(file_name);
    rename("temp.txt", file_name);
}



void CurrentGame::init(GameMode mode, const string& intitialBoardFile, const string& movementsFile) //HECHO, (FUNCIONAL?)
{
    int contador = 0;
    
    if (mode == GM_NORMAL) {
        
        modeGame = mode;
        nomFitxer = movementsFile;

        if (m_partidaEmpezada == false) { // si es una partida normal
            
            if (intitialBoardFile != "") { // si tenemos un fixero inicial
                if (contador == 0) // inicializa el color una vez
                {
                    colorHelp.setColor(CPC_Black);
                    contador++;
                }

                game.LoadBoardFromFile(intitialBoardFile);
                string gameTXT = game.ToString();
                m_partidaEmpezada = true;


                ofstream fitxer; // al inicializar la partida, el txt de movimientos debe estar vacio para que no se mezcle con otras partidas ya jugadas
                fitxer.open(movementsFile);
                fitxer.close();
            }
            else { // si no lo tenemos, inicializamos con el tablero de juego por defecto

                game.LoadBoardFromFile("boardInitial.txt");
                string gameTXT = game.ToString();
                m_inicialitzat = true;

                ofstream fitxer; // al inicializar la partida, el txt de movimientos debe estar vacio para que no se mezcle con otras partidas ya jugadas
                fitxer.open(movementsFile);
                fitxer.close();

            }

        }
        else { // si pasamos por aqui, ya hemos inicializado la partida y queremos ir guardando los movimientos en el txt , en caso de que queramos guaradar la partida sin haber acabado
            
            if (!m_moviments.empty()) {

                ofstream fitxer;
                fitxer.open(movementsFile, ofstream::app); // d'aqeusta forma no esborra el contingut
                if (fitxer.is_open())
                {
                    if (!enrere) {
                        //op1 escriure un nou moviment que hem fet
                        string movement;
                        movement = (m_moviments.getUltimMoviment())->getMov();
                        fitxer << movement;
                        fitxer << endl;
                        lines++;
                        fitxer.close();
                    }
                    else {//op2 anar enrere ja que hem desfet el ultim moviment

                        fitxer.close();
                        eliminarMovimentTxt(movementsFile.c_str(), lines); //el c_str convierte el string en un char
                        enrere = false;

                    }
                }
            }
        }
    }

    else { // si estamos en replay debe crear la lista de movimientos entera, usando el NodeMoves  y luego ir represntando y eliminado de la lista cada vez que hacemos click con el raton (update and render)
        // solo pasamos para inicializar
        modeGame = mode;
        ifstream fitxer; //1. llenmos nuestra pila
        stackMovements movimentsInvertits; //al llenar la pila, esta tendra los movimientos al reves




        if (m_partidaEmpezada == false) { // inicializamos el tablero

            if (intitialBoardFile != "") { // si no tenemos un fixero inicial
                if (contador == 0) // inicializa el color una vez
                {
                    colorHelp.setColor(CPC_White);
                    contador++;
                }

                game.LoadBoardFromFile(intitialBoardFile);
                string gameTXT = game.ToString();
                m_partidaEmpezada = true;
                
            }
            colorHelp.setColor(CPC_White);
        }


        fitxer.open(movementsFile); // si solo es un replay, no necesitamos saber cuales han muerto

        if (fitxer.is_open())
        {
            int lines = 0;
            string movement;
            string aux;

            fitxer >> movement;
            movement += " ";
            fitxer >> aux;
            movement += aux; //guardem el moviment sencer

            getline(fitxer, movement); // Pilla la primera linea del fichero
            movimentsInvertits.pushMov(movement, "");
            lines++;

            while (!fitxer.eof())
            {
                fitxer >> movement;
                movement += " ";
                fitxer >> aux;
                movement += aux;
                movimentsInvertits.pushMov(movement, "");
                lines++;
            }
            fitxer.close();

            
            while (lines !=0) { // invetimos la pila para tener los movimientos ordenados de forma que a cada pop avancemos al siguiente 


                    m_moviments.pushMov(movimentsInvertits.top()->getMov(), "");
                    movimentsInvertits.popMov();

                    lines--;

            }
        }
    }


}


void CurrentGame::end() 
{
 
}


void CurrentGame::caselles(const int& contadorFila, const  int& contadorColumna)
{
    switch (contadorFila) // letra
    {
    case 1:
    {
        newPositionToRender.setPosX(0);
    }break;
    case 2:
    {
        newPositionToRender.setPosX(1);
    }break;
    case 3:
    {
        newPositionToRender.setPosX(2);
    }break;
    case 4:
    {
        newPositionToRender.setPosX(3);
    }break;
    case 5:
    {
        newPositionToRender.setPosX(4);
    }break;
    case 6:
    {
        newPositionToRender.setPosX(5);
    }break;
    case 7:
    {
        newPositionToRender.setPosX(6);
    }break;
    case 8:
    {
        newPositionToRender.setPosX(7);
    }break;
    }



    switch (contadorColumna) // numero
    {
    case 1:
    {
        newPositionToRender.setPosY(0);
    }break;
    case 2:
    {
        newPositionToRender.setPosY(1);
    }break;
    case 3:
    {
        newPositionToRender.setPosY(2);
    }break;
    case 4:
    {
        newPositionToRender.setPosY(3);
    }break;
    case 5:
    {
        newPositionToRender.setPosY(4);
    }break;
    case 6:
    {
        newPositionToRender.setPosY(5);
    }break;
    case 7:
    {
        newPositionToRender.setPosY(6);
    }break;
    case 8:
    {
        newPositionToRender.setPosY(7);
    }break;
    }
}


void   CurrentGame::renderPiece(const char& PieceColor, const  char& PieceType)const
{
    Piece p;
    ChessPieceColor color;
    if (PieceColor == 'b')
    {
        color = CPC_Black;
        switch (PieceType)
        {
        case 'T':
        {
            p.Render(CPT_Rook, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'C':
        {
            p.Render(CPT_Knight, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'A':
        {
            p.Render(CPT_Bishop, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'D':
        {
            p.Render(CPT_Queen, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'R':
        {
            p.Render(CPT_King, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'P':
        {
            p.Render(CPT_Pawn, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        default:
            break;
        }
    }
    else
    {
        color = CPC_White;
        switch (PieceType)
        {
        case 'T':
        {
            p.Render(CPT_Rook, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'C':
        {
            p.Render(CPT_Knight, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'A':
        {
            p.Render(CPT_Bishop, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'D':
        {
            p.Render(CPT_Queen, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'R':
        {
            p.Render(CPT_King, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        case 'P':
        {
            p.Render(CPT_Pawn, color, newPositionToRender.getPosX(), newPositionToRender.getPosY());
        }break;
        default:
            break;
        }

    }
   

}

void guardarPartida(ChessPosition From, ChessPosition To, string& moviment) // crea el string que irá en el fichero de movimientos
{
    //posx son las filas que nos movemos hacia abajo (el numero)
    //pos y son las columnas que nos movemos (las letras)

    char  letraFrom, letraTo;
    int FromY = From.getPosX();
    int ToY = To.getPosX();

    char froomY, TooY; //pasamos las filas a un char legible por el string moviments



    switch (From.getPosY()) //nos da la letra de dnd venimos
    {
    case 0:
        letraFrom = 'a';
        break;
    case 1:
        letraFrom = 'b';
        break;
    case 2:
        letraFrom = 'c';
        break;
    case 3:
        letraFrom = 'd';
        break;
    case 4:
        letraFrom = 'e';
        break;
    case 5:
        letraFrom = 'f';
        break;
    case 6:
        letraFrom = 'g';
        break;
    case 7:
        letraFrom = 'h';
    default:
        break;
    }

    switch (To.getPosY())
    {
    case 0:
        letraTo = 'a';
        break;
    case 1:
        letraTo = 'b';
        break;
    case 2:
        letraTo = 'c';
        break;
    case 3:
        letraTo = 'd';
        break;
    case 4:
        letraTo = 'e';
        break;
    case 5:
        letraTo = 'f';
        break;
    case 6:
        letraTo = 'g';
        break;
    case 7:
        letraTo = 'h';
    default:
        break;
    }


    switch (From.getPosX()) //nos da el numero
    {
    case 0:
        froomY = '8';
        break;
    case 1:
        froomY = '7';
        break;
    case 2:
        froomY = '6';
        break;
    case 3:
        froomY = '5';
        break;
    case 4:
        froomY = '4';
        break;
    case 5:
        froomY = '3';
        break;
    case 6:
        froomY = '2';
        break;
    case 7:
        froomY = '1';
    default:
        break;
    }

    switch (To.getPosX()) //nos da el numero
    {
    case 0:
        TooY = '8';
        break;
    case 1:
        TooY = '7';
        break;
    case 2:
        TooY = '6';
        break;
    case 3:
        TooY = '5';
        break;
    case 4:
        TooY = '4';
        break;
    case 5:
        TooY = '3';
        break;
    case 6:
        TooY = '2';
        break;
    case 7:
        TooY = '1';
    default:
        break;
    }
    moviment += letraFrom; // la letra de dnd venimos
    moviment += froomY; // el num dnd venimos
    moviment += " ";
    moviment += letraTo; //letra a dnd vamos
    moviment += TooY; //num a dnd vamos
}

void  CurrentGame::conversor(string moviment)
{
    int posFromX, posFomY, posToX, posToY;
    switch (moviment[1])
    {
    case 'a':
        posFromX = 0 ;
        break;
    case 'b':
        posFromX = 1 ;
        break;
    case  'c':
        posFromX = 2;
        break;
    case  'd':
        posFromX = 3;
        break;
    case 'e':
        posFromX = 4 ;
        break;
    case 'f':
        posFromX = 5 ;
        break;
    case 'g':
        posFromX = 6;
        break;
    case 'h':
        posFromX = 7;
    default:
        break;
    }

    switch (moviment[4])
    {
    case 'a':
        posToX = 0;
        break;
    case 'b':
        posToX = 1;
        break;
    case  'c':
        posToX = 2;
        break;
    case  'd':
        posToX = 3;
        break;
    case 'e':
        posToX = 4;
        break;
    case 'f':
        posToX = 5;
        break;
    case 'g':
        posToX = 6;
        break;
    case 'h':
        posToX = 7;
    default:
        break;
    }

    newPositionToRender.setPosX(posToX);
    newPositionToRender.setPosY(moviment[5] - 1);
    positionHelper.setPosX(posFromX);
    positionHelper.setPosY(moviment[2] - 1);
    

}





bool CurrentGame::updateAndRender(int mousePosX, int mousePosY, bool mouseStatus)  //FALTA POR HACER
{
    if (modeGame == GM_NORMAL)
    {

        GraphicManager::getInstance()->drawSprite(IMAGE_WALLPAPER, 0, 0);
        GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);



        //situar el texto de la pantalla
        int TextoCordX = CELL_INIT_X;
        int TextoCordY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
        std::string gameMode = "Game Mode: Normal Play";
        string colorString;


        if (colorHelp.getColor() == 1)
            colorString = "Color: Negro";
        else
            colorString = "Color: Blanco";

        GraphicManager::getInstance()->drawFont(FONT_RED_30, TextoCordX, TextoCordY, 0.8, gameMode);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, TextoCordX, TextoCordY + 60, 0.8, colorString);



        int contadorFila = 1, contadorColumnas = 1;
        string Partida = game.ToString();
        int stringSize = game.ToString().size();

        for (int contador = 2; contador < stringSize; contador++) // coloca bien las piezas para cada iteración
        {
            char typePiece = Partida[contador + 1];
            char colorPiece = Partida[contador];
            caselles(contadorFila, contadorColumnas);
            renderPiece(colorPiece, typePiece);

            if (contadorFila == 8)
            {
                contadorFila = 0;
                contadorColumnas++;
                contador = contador + 2; //para que sume 3 en vez de dos cuando hay un salto de linea a la siguiente columna 
            }
            contadorFila++;
            contador = contador + 2;
        }


        if ((mouseStatus) && (mousePosX >= CELL_INIT_X) && (mousePosY >= CELL_INIT_Y) && (mousePosX <= (CELL_INIT_X + CELL_W * NUM_COLS)) & (mousePosY <= (CELL_INIT_Y + CELL_H * NUM_ROWS)))
        {
            int posY = (mousePosX - CELL_INIT_X) / CELL_W;
            int posX = (mousePosY - CELL_INIT_Y) / CELL_H;

            ChessPosition newPosition;
            newPosition.setPosX(posX);
            newPosition.setPosY(posY);

            if (m_inicialitzat) //aguatar los cuadrados verdes en una casilla si se clicka en la scondiciones optimas 
            {
                int colorLocker;
                if (colorHelp.getColor() == 1)
                    colorLocker = 0;
                else
                    colorLocker = 1;


                if (game.GetPieceColorAtPos(newPosition) == colorLocker) // si pertenece al mismo color entonces nocuenta como click el anterior

                {
                    positionHelper.setPosX(posX);
                    positionHelper.setPosY(posY);
                }
                else
                {
                    newPositionToRender.setPosX(posX);
                    newPositionToRender.setPosY(posY);
                    m_inicialitzat = false;
                }
            }
            else
            {
                if (game.GetPieceColorAtPos(newPosition) != colorHelp.getColor())
                {
                    positionHelper.setPosY(posY);
                    positionHelper.setPosX(posX);


                    if (game.GetPieceTypeAtPos(newPositionToRender) != CPT_EMPTY)
                    {
                        m_inicialitzat = true;
                    }
                }
            }
        }

        //dibuja los cuadrados verdes por pantalla con las posibles jugadas
        if (m_inicialitzat)
        {
            vector<ChessPosition> vec;
            vec = game.GetValidMoves(positionHelper);
            for (int contador = 0; contador < vec.size(); contador++)
            {
                GraphicManager::getInstance()->drawSprite(IMAGE_VALID_POS, CELL_INIT_X + (vec[contador].getPosY() * CELL_W), CELL_INIT_Y + (vec[contador].getPosX() * CELL_H));
            }
        }

        if (!m_inicialitzat && game.MovePiece(positionHelper, newPositionToRender))
        {
            //cambiar de color
            if (colorHelp.getColor() == 0)
                colorHelp.setColor(CPC_White);
            else
                colorHelp.setColor(CPC_Black);

            string moviment; // es el inici / desti dúna fitxa per a ser guardat al movements.txt

            guardarPartida(positionHelper, newPositionToRender, moviment);

            m_moviments.pushMov(moviment, game.ToString()); // el to string seria para guardar una instantanea de la partida antes de hacer un movimiento SIRVE POR SI QUEREMOS TIRAR HACIA ATRAS
            cout << moviment;

            init(modeGame, "", nomFitxer); // el init se encarga EL SOLO de guardar los movimentos NO HACE FALTA TOCAR NADA DE AQUI
        }
        return false;
    }
    else //modo replay
    {
        GraphicManager::getInstance()->drawSprite(IMAGE_WALLPAPER, 0, 0);
        GraphicManager::getInstance()->drawSprite(IMAGE_BOARD, 0, 0);

        int TextoCordX = CELL_INIT_X;
        int TextoCordY = CELL_INIT_Y + (CELL_H * NUM_ROWS) + 60;
        std::string gameMode = "Game Mode:  Replay";
        string colorString;

        if (colorHelp.getColor() == 0)
            colorString = "Color: Negro";
        else
            colorString = "Color: Blanco";


    
        GraphicManager::getInstance()->drawFont(FONT_RED_30, TextoCordX, TextoCordY, 0.8, gameMode);
        GraphicManager::getInstance()->drawFont(FONT_RED_30, TextoCordX, TextoCordY + 60, 0.8, colorString);


        if(mouseStatus) 
        {

           string movimentArepresentar =  m_moviments.top()->getMov(); // nos da el string del movimiento que tenemos que hacer
           conversor(movimentArepresentar);
           game.MovePiece(positionHelper, newPositionToRender);

           int contadorFila = 1, contadorColumnas = 1; // codigo    que mueve las piezas 
           string Partida = game.ToString();
           int stringSize = game.ToString().size();

           for (int contador = 2; contador < stringSize; contador++) // coloca bien las piezas para cada iteración
           {
               char typePiece = Partida[contador + 1];
               char colorPiece = Partida[contador];
               caselles(contadorFila, contadorColumnas);
               renderPiece(colorPiece, typePiece);

               if (contadorFila == 8)
               {
                   contadorFila = 0;
                   contadorColumnas++;
                   contador = contador + 2; //para que sume 3 en vez de dos cuando hay un salto de linea a la siguiente columna 
               }
               contadorFila++;
               contador = contador + 2;
           }

            m_moviments.popMov(); //nos quita el movimiento de la pila lo que ya hemos representado 
            if (colorHelp.getColor() == CPC_Black)
                colorHelp.setColor(CPC_White);
            else
                colorHelp.setColor(CPC_Black);
        }

    }
}
