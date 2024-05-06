#pragma once
#ifndef MovementHistory_h
#define MovementHistory_h
#include <vector>
#include <string>
using namespace std;




class NodeMoves { // d'aquesta forma podem reproduir una aprtida (GM_REPLAY) o desfer un canvi (GM_NORMAL)

public:

    NodeMoves();
    ~NodeMoves();
    NodeMoves(const string& valor) : m_moviment(valor), m_next(nullptr), m_prev(nullptr) {}

    NodeMoves* getNext() { return m_next; }
    string getMov() { return m_moviment; }
    NodeMoves* getPrev() { return m_prev; }
    string getEpiece() { return eliminatedPiece; }



    void setNext(NodeMoves* next) { m_next = next; }
    void setPrev(NodeMoves* prev) { m_prev = prev; }
    void setMov(const string& moviment) { m_moviment = moviment; }
    void setEpiece(const string& piece) { eliminatedPiece = piece; }


private:

    string m_moviment;
    string eliminatedPiece; // por si queremos ir hacia atras, debemos poner la pieza que fue eliminada en la jugada
    NodeMoves* m_next;
    NodeMoves* m_prev;


};


class stackMovements {

public:

    //constructor 
    stackMovements() : ultimMoviment(nullptr) {}

    //getters
    NodeMoves* getUltimMoviment() { return ultimMoviment; }

    //setters
    void       setUltimMoviment(NodeMoves*& ultim) { ultimMoviment = ultim; }

    //metodes            //solo añadimos y elimnamos nodos al final de la lista

    void pushMov(const string& moviment, const string& erasedPiece); // crea un nou node i l'afegeix, retorna un apuntador al node afegit
    void popMov(); // elimina el node al que apunta un apuntador, y retorna un apuntador al seguent node 
    NodeMoves* top() { return ultimMoviment; }
    bool empty();


private:

    NodeMoves* ultimMoviment; // apunta al ultim node
};



#endif
